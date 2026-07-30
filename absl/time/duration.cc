// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// The implementation of the absl::Duration class, which is declared in
// //absl/time.h.  This class behaves like a numeric type; it has no public
// methods and is used only through the operators defined here.
//
// Implementation notes:
//
// An absl::Duration is represented as
//
//   rep_hi_ : (int64_t)  Whole seconds
//   rep_lo_ : (uint32_t) Fractions of a second
//
// The seconds value (rep_hi_) may be positive or negative as appropriate.
// The fractional seconds (rep_lo_) is always a positive offset from rep_hi_.
// The API for Duration guarantees at least nanosecond resolution, which
// means rep_lo_ could have a max value of 1B - 1 if it stored nanoseconds.
// However, to utilize more of the available 32 bits of space in rep_lo_,
// we instead store quarters of a nanosecond in rep_lo_ resulting in a max
// value of 4B - 1.  This allows us to correctly handle calculations like
// 0.5 nanos + 0.5 nanos = 1 nano.  The following example shows the actual
// Duration rep using quarters of a nanosecond.
//
//    2.5 sec = {rep_hi_=2,  rep_lo_=2000000000}  // lo = 4 * 500000000
//   -2.5 sec = {rep_hi_=-3, rep_lo_=2000000000}
//
// Infinite durations are represented as Durations with the rep_lo_ field set
// to all 1s.
//
//   +InfiniteDuration:
//     rep_hi_ : kint64max
//     rep_lo_ : ~0U
//
//   -InfiniteDuration:
//     rep_hi_ : kint64min
//     rep_lo_ : ~0U
//
// Arithmetic overflows/underflows to +/- infinity and saturates.

#if defined(_MSC_VER)
#include <winsock2.h>  // for timeval
#endif

#include <algorithm>
#include <cassert>
#include <chrono>  // NOLINT(build/c++11)
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <limits>
#include <string>

#include "absl/base/attributes.h"
#include "absl/base/casts.h"
#include "absl/base/config.h"
#include "absl/numeric/int128.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/time/time.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

namespace {

using time_internal::kTicksPerNanosecond;
using time_internal::kTicksPerSecond;

constexpr int64_t kint64max = std::numeric_limits<int64_t>::max();
constexpr int64_t kint64min = std::numeric_limits<int64_t>::min();

// Can't use std::isinfinite() because it doesn't exist on windows.
inline bool IsFinite(double d) {
  if (std::isnan(d)) return false;
  return d != std::numeric_limits<double>::infinity() &&
         d != -std::numeric_limits<double>::infinity();
}

inline bool IsValidDivisor(double d) {
  if (std::isnan(d)) return false;
  return d != 0.0;
}

// *sec may be positive or negative.  *ticks must be in the range
// -kTicksPerSecond < *ticks < kTicksPerSecond.  If *ticks is negative it
// will be normalized to a positive value by adjusting *sec accordingly.
inline void NormalizeTicks(int64_t* sec, int64_t* ticks) {
  if (*ticks < 0) {
    --*sec;
    *ticks += kTicksPerSecond;
  }
}

// Makes a uint128 from the absolute value of the given scalar.
inline uint128 MakeU128(int64_t a) {
  uint128 u128 = 0;
  if (a < 0) {
    ++u128;
    ++a;  // Makes it safe to negate 'a'
    a = -a;
  }
  u128 += static_cast<uint64_t>(a);
  return u128;
}

// Makes a uint128 count of ticks out of the absolute value of the Duration.
inline uint128 MakeU128Ticks(Duration d) {
  int64_t rep_hi = time_internal::GetRepHi(d);
  uint32_t rep_lo = time_internal::GetRepLo(d);
  if (rep_hi < 0) {
    ++rep_hi;
    rep_hi = -rep_hi;
    rep_lo = kTicksPerSecond - rep_lo;
  }
  uint128 u128 = static_cast<uint64_t>(rep_hi);
  u128 *= static_cast<uint64_t>(kTicksPerSecond);
  u128 += rep_lo;
  return u128;
}

// Breaks a uint128 of ticks into a Duration.
inline Duration MakeDurationFromU128(uint128 u128, bool is_neg) {
  int64_t rep_hi;
  uint32_t rep_lo;
  const uint64_t h64 = Uint128High64(u128);
  const uint64_t l64 = Uint128Low64(u128);
  if (h64 == 0) {  // fastpath
    const uint64_t hi = l64 / kTicksPerSecond;
    rep_hi = static_cast<int64_t>(hi);
    rep_lo = static_cast<uint32_t>(l64 - hi * kTicksPerSecond);
  } else {
    // kMaxRepHi64 is the high 64 bits of (2^63 * kTicksPerSecond).
    // Any positive tick count whose high 64 bits are >= kMaxRepHi64
    // is not representable as a Duration.  A negative tick count can
    // have its high 64 bits == kMaxRepHi64 but only when the low 64
    // bits are all zero, otherwise it is not representable either.
    const uint64_t kMaxRepHi64 = 0x77359400UL;
    if (h64 >= kMaxRepHi64) {
      if (is_neg && h64 == kMaxRepHi64 && l64 == 0) {
        // Avoid trying to represent -kint64min below.
        return time_internal::MakeDuration(kint64min);
      }
      return is_neg ? -InfiniteDuration() : InfiniteDuration();
    }
    const uint128 kTicksPerSecond128 = static_cast<uint64_t>(kTicksPerSecond);
    const uint128 hi = u128 / kTicksPerSecond128;
    rep_hi = static_cast<int64_t>(Uint128Low64(hi));
    rep_lo =
        static_cast<uint32_t>(Uint128Low64(u128 - hi * kTicksPerSecond128));
  }
  if (is_neg) {
    rep_hi = -rep_hi;
    if (rep_lo != 0) {
      --rep_hi;
      rep_lo = kTicksPerSecond - rep_lo;
    }
  }
  return time_internal::MakeDuration(rep_hi, rep_lo);
}

// Convert between int64_t and uint64_t, preserving representation. This
// allows us to do arithmetic in the unsigned domain, where overflow has
// well-defined behavior. See operator+=() and operator-=().
//
// C99 7.20.1.1.1, as referenced by C++11 18.4.1.2, says, "The typedef
// name intN_t designates a signed integer type with width N, no padding
// bits, and a two's complement representation." So, we can convert to
// and from the corresponding uint64_t value using a bit cast.
inline uint64_t EncodeTwosComp(int64_t v) {
  return absl::bit_cast<uint64_t>(v);
}
inline int64_t DecodeTwosComp(uint64_t v) { return absl::bit_cast<int64_t>(v); }

// Note: The overflow detection in this function is done using greater/less *or
// equal* because kint64max/min is too large to be represented exactly in a
// double (which only has 53 bits of precision). In order to avoid assigning to
// rep->hi a double value that is too large for an int64_t (and therefore is
// undefined), we must consider computations that equal kint64max/min as a
// double as overflow cases.
inline bool SafeAddRepHi(double a_hi, double b_hi, Duration* d) {
  double c = a_hi + b_hi;
  if (c >= static_cast<double>(kint64max)) {
    *d = InfiniteDuration();
    return false;
  }
  if (c <= static_cast<double>(kint64min)) {
    *d = -InfiniteDuration();
    return false;
  }
  *d = time_internal::MakeDuration(static_cast<int64_t>(c),
                                   time_internal::GetRepLo(*d));
  return true;
}

// A functor that's similar to std::multiplies<T>, except this returns the max
// T value instead of overflowing. This is only defined for uint128.
template <typename Ignored>
struct SafeMultiply {
  uint128 operator()(uint128 a, uint128 b) const {
    // b hi is always zero because it originated as an int64_t.
    assert(Uint128High64(b) == 0);
    // Fastpath to avoid the expensive overflow check with division.
    if (Uint128High64(a) == 0) {
      return (((Uint128Low64(a) | Uint128Low64(b)) >> 32) == 0)
                 ? static_cast<uint128>(Uint128Low64(a) * Uint128Low64(b))
                 : a * b;
    }
    return b == 0 ? b : (a > Uint128Max() / b) ? Uint128Max() : a * b;
  }
};

// Scales (i.e., multiplies or divides, depending on the Operation template)
// the Duration d by the int64_t r.
template <template <typename> class Operation>
inline Duration ScaleFixed(Duration d, int64_t r) {
  const uint128 a = MakeU128Ticks(d);
  const uint128 b = MakeU128(r);
  const uint128 q = Operation<uint128>()(a, b);
  const bool is_neg = (time_internal::GetRepHi(d) < 0) != (r < 0);
  return MakeDurationFromU128(q, is_neg);
}

// Scales (i.e., multiplies or divides, depending on the Operation template)
// the Duration d by the double r.
template <template <typename> class Operation>
inline Duration ScaleDouble(Duration d, double r) {
  Operation<double> op;
  double hi_doub = op(static_cast<double>(time_internal::GetRepHi(d)), r);
  double lo_doub = op(static_cast<double>(time_internal::GetRepLo(d)), r);

  double hi_int = 0;
  double hi_frac = std::modf(hi_doub, &hi_int);

  // Moves hi's fractional bits to lo.
  lo_doub /= kTicksPerSecond;
  lo_doub += hi_frac;

  double lo_int = 0;
  double lo_frac = std::modf(lo_doub, &lo_int);

  // Rolls lo into hi if necessary.
  int64_t lo64 = static_cast<int64_t>(std::round(lo_frac * kTicksPerSecond));

  Duration ans;
  if (!SafeAddRepHi(hi_int, lo_int, &ans)) return ans;
  int64_t hi64 = time_internal::GetRepHi(ans);
  if (!SafeAddRepHi(static_cast<double>(hi64),
                    static_cast<double>(lo64 / kTicksPerSecond), &ans)) {
    return ans;
  }
  hi64 = time_internal::GetRepHi(ans);
  lo64 %= kTicksPerSecond;
  NormalizeTicks(&hi64, &lo64);
  return time_internal::MakeDuration(hi64, lo64);
}

// Tries to divide num by den as fast as possible by looking for common, easy
// cases. If the division was done, the quotient is in *q and the remainder is
// in *rem and true will be returned.
inline bool IDivFastPath(const Duration num, const Duration den, int64_t* q,
                         Duration* rem) {
  // Bail if num or den is an infinity.
  if (time_internal::IsInfiniteDuration(num) ||
      time_internal::IsInfiniteDuration(den))
    return false;

  int64_t num_hi = time_internal::GetRepHi(num);
  uint32_t num_lo = time_internal::GetRepLo(num);
  int64_t den_hi = time_internal::GetRepHi(den);
  uint32_t den_lo = time_internal::GetRepLo(den);

  if (den_hi == 0) {
    if (den_lo == kTicksPerNanosecond) {
      // Dividing by 1ns
      if (num_hi >= 0 && num_hi < (kint64max - kTicksPerSecond) / 1000000000) {
        *q = num_hi * 1000000000 + num_lo / kTicksPerNanosecond;
        *rem = time_internal::MakeDuration(0, num_lo % den_lo);
        return true;
      }
    } else if (den_lo == 100 * kTicksPerNanosecond) {
      // Dividing by 100ns (common when converting to Universal time)
      if (num_hi >= 0 && num_hi < (kint64max - kTicksPerSecond) / 10000000) {
        *q = num_hi * 10000000 + num_lo / (100 * kTicksPerNanosecond);
        *rem = time_internal::MakeDuration(0, num_lo % den_lo);
        return true;
      }
    } else if (den_lo == 1000 * kTicksPerNanosecond) {
      // Dividing by 1us
      if (num_hi >= 0 && num_hi < (kint64max - kTicksPerSecond) / 1000000) {
        *q = num_hi * 1000000 + num_lo / (1000 * kTicksPerNanosecond);
        *rem = time_internal::MakeDuration(0, num_lo % den_lo);
        return true;
      }
    } else if (den_lo == 1000000 * kTicksPerNanosecond) {
      // Dividing by 1ms
      if (num_hi >= 0 && num_hi < (kint64max - kTicksPerSecond) / 1000) {
        *q = num_hi * 1000 + num_lo / (1000000 * kTicksPerNanosecond);
        *rem = time_internal::MakeDuration(0, num_lo % den_lo);
        return true;
      }
    }
  } else if (den_hi > 0 && den_lo == 0) {
    // Dividing by positive multiple of 1s
    if (num_hi >= 0) {
      if (den_hi == 1) {
        *q = num_hi;
        *rem = time_internal::MakeDuration(0, num_lo);
        return true;
      }
      *q = num_hi / den_hi;
      *rem = time_internal::MakeDuration(num_hi % den_hi, num_lo);
      return true;
    }
    if (num_lo != 0) {
      num_hi += 1;
    }
    int64_t quotient = num_hi / den_hi;
    int64_t rem_sec = num_hi % den_hi;
    if (rem_sec > 0) {
      rem_sec -= den_hi;
      quotient += 1;
    }
    if (num_lo != 0) {
      rem_sec -= 1;
    }
    *q = quotient;
    *rem = time_internal::MakeDuration(rem_sec, num_lo);
    return true;
  }

  return false;
}

}  // namespace

namespace {

int64_t IDivSlowPath(bool satq, const Duration num, const Duration den,
                     Duration* rem) { __builtin_trap() /* STUB: not implemented */; }

// The 'satq' argument indicates whether the quotient should saturate at the
// bounds of int64_t.  If it does saturate, the difference will spill over to
// the remainder.  If it does not saturate, the remainder remain accurate,
// but the returned quotient will over/underflow int64_t and should not be used.
ABSL_ATTRIBUTE_ALWAYS_INLINE inline int64_t IDivDurationImpl(bool satq,
                                                             const Duration num,
                                                             const Duration den,
                                                             Duration* rem) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

int64_t IDivDuration(Duration num, Duration den, Duration* rem) { __builtin_trap() /* STUB: not implemented */; }

//
// Additive operators.
//

Duration& Duration::operator+=(Duration rhs) { __builtin_trap() /* STUB: not implemented */; }

Duration& Duration::operator-=(Duration rhs) { __builtin_trap() /* STUB: not implemented */; }

//
// Multiplicative operators.
//

Duration& Duration::operator*=(int64_t r) { __builtin_trap() /* STUB: not implemented */; }

Duration& Duration::operator*=(double r) { __builtin_trap() /* STUB: not implemented */; }

Duration& Duration::operator/=(int64_t r) { __builtin_trap() /* STUB: not implemented */; }

Duration& Duration::operator/=(double r) { __builtin_trap() /* STUB: not implemented */; }

Duration& Duration::operator%=(Duration rhs) { __builtin_trap() /* STUB: not implemented */; }

double FDivDuration(Duration num, Duration den) { __builtin_trap() /* STUB: not implemented */; }

//
// Trunc/Floor/Ceil.
//

Duration Trunc(Duration d, Duration unit) { __builtin_trap() /* STUB: not implemented */; }

Duration Floor(const Duration d, const Duration unit) { __builtin_trap() /* STUB: not implemented */; }

Duration Ceil(const Duration d, const Duration unit) { __builtin_trap() /* STUB: not implemented */; }

//
// Factory functions.
//

Duration DurationFromTimespec(timespec ts) { __builtin_trap() /* STUB: not implemented */; }

Duration DurationFromTimeval(timeval tv) { __builtin_trap() /* STUB: not implemented */; }

//
// Conversion to other duration types.
//
double ToDoubleNanoseconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
double ToDoubleMicroseconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
double ToDoubleMilliseconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
double ToDoubleSeconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
double ToDoubleMinutes(Duration d) { __builtin_trap() /* STUB: not implemented */; }
double ToDoubleHours(Duration d) { __builtin_trap() /* STUB: not implemented */; }

timespec ToTimespec(Duration d) { __builtin_trap() /* STUB: not implemented */; }

timeval ToTimeval(Duration d) { __builtin_trap() /* STUB: not implemented */; }

std::chrono::nanoseconds ToChronoNanoseconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
std::chrono::microseconds ToChronoMicroseconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
std::chrono::milliseconds ToChronoMilliseconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
std::chrono::seconds ToChronoSeconds(Duration d) { __builtin_trap() /* STUB: not implemented */; }
std::chrono::minutes ToChronoMinutes(Duration d) { __builtin_trap() /* STUB: not implemented */; }
std::chrono::hours ToChronoHours(Duration d) { __builtin_trap() /* STUB: not implemented */; }

//
// To/From string formatting.
//

namespace {

// Formats a positive 64-bit integer in the given field width.  Note that
// it is up to the caller of Format64() to ensure that there is sufficient
// space before ep to hold the conversion.
char* Format64(char* ep, int width, int64_t v) { __builtin_trap() /* STUB: not implemented */; }

// Helpers for FormatDuration() that format 'n' and append it to 'out'
// followed by the given 'unit'.  If 'n' formats to "0", nothing is
// appended (not even the unit).

// A type that encapsulates how to display a value of a particular unit. For
// values that are displayed with fractional parts, the precision indicates
// where to round the value. The precision varies with the display unit because
// a Duration can hold only quarters of a nanosecond, so displaying information
// beyond that is just noise.
//
// For example, a microsecond value of 42.00025xxxxx should not display beyond 5
// fractional digits, because it is in the noise of what a Duration can
// represent.
struct DisplayUnit {
  absl::string_view abbr;
  int prec;
  double pow10;
};
constexpr DisplayUnit kDisplayNano = {"ns", 2, 1e2};
constexpr DisplayUnit kDisplayMicro = {"us", 5, 1e5};
constexpr DisplayUnit kDisplayMilli = {"ms", 8, 1e8};
constexpr DisplayUnit kDisplaySec = {"s", 11, 1e11};
constexpr DisplayUnit kDisplayMin = {"m", -1, 0.0};   // prec ignored
constexpr DisplayUnit kDisplayHour = {"h", -1, 0.0};  // prec ignored

void AppendNumberUnit(std::string* out, int64_t n, DisplayUnit unit) { __builtin_trap() /* STUB: not implemented */; }

// Note: unit.prec is limited to double's digits10 value (typically 15) so it
// always fits in buf[].
void AppendNumberUnit(std::string* out, double n, DisplayUnit unit) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

// From Go's doc at https://golang.org/pkg/time/#Duration.String
//   [FormatDuration] returns a string representing the duration in the
//   form "72h3m0.5s". Leading zero units are omitted.  As a special
//   case, durations less than one second format use a smaller unit
//   (milli-, micro-, or nanoseconds) to ensure that the leading digit
//   is non-zero.
// Unlike Go, we format the zero duration as 0, with no unit.
std::string FormatDuration(Duration d) { __builtin_trap() /* STUB: not implemented */; }

namespace {

// A helper for ParseDuration() that parses a leading number from the given
// string and stores the result in *int_part/*frac_part/*frac_scale.  The
// given string pointer is modified to point to the first unconsumed char.
bool ConsumeDurationNumber(const char** dpp, const char* ep, int64_t* int_part,
                           int64_t* frac_part, int64_t* frac_scale) { __builtin_trap() /* STUB: not implemented */; }

// A helper for ParseDuration() that parses a leading unit designator (e.g.,
// ns, us, ms, s, m, h) from the given string and stores the resulting unit
// in "*unit".  The given string pointer is modified to point to the first
// unconsumed char.
bool ConsumeDurationUnit(const char** start, const char* end, Duration* unit) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

// From Go's doc at https://golang.org/pkg/time/#ParseDuration
//   [ParseDuration] parses a duration string. A duration string is
//   a possibly signed sequence of decimal numbers, each with optional
//   fraction and a unit suffix, such as "300ms", "-1.5h" or "2h45m".
//   Valid time units are "ns", "us" "ms", "s", "m", "h".
bool ParseDuration(absl::string_view dur_sv, Duration* d) { __builtin_trap() /* STUB: not implemented */; }

bool AbslParseFlag(absl::string_view text, Duration* dst, std::string*) { __builtin_trap() /* STUB: not implemented */; }

std::string AbslUnparseFlag(Duration d) { __builtin_trap() /* STUB: not implemented */; }
bool ParseFlag(const std::string& text, Duration* dst, std::string* ) { __builtin_trap() /* STUB: not implemented */; }

std::string UnparseFlag(Duration d) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
