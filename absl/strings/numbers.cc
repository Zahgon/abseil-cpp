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

// This file contains string processing functions related to
// numeric values.

#include "absl/strings/numbers.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cfloat>  // for DBL_DIG and FLT_DIG
#include <clocale>  // for localeconv
#include <cmath>   // for HUGE_VAL
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <limits>
#include <system_error>  // NOLINT(build/c++11)
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/endian.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/macros.h"
#include "absl/base/nullability.h"
#include "absl/base/optimization.h"
#include "absl/numeric/bits.h"
#include "absl/numeric/int128.h"
#include "absl/strings/ascii.h"
#include "absl/strings/charconv.h"
#include "absl/strings/match.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

bool SimpleAtof(absl::string_view str, float* absl_nonnull out) { __builtin_trap() /* STUB: not implemented */; }

bool SimpleAtod(absl::string_view str, double* absl_nonnull out) { __builtin_trap() /* STUB: not implemented */; }

bool SimpleAtob(absl::string_view str, bool* absl_nonnull out) { __builtin_trap() /* STUB: not implemented */; }

// ----------------------------------------------------------------------
// FastIntToBuffer() overloads
//
// Like the Fast*ToBuffer() functions above, these are intended for speed.
// Unlike the Fast*ToBuffer() functions, however, these functions write
// their output to the beginning of the buffer.  The caller is responsible
// for ensuring that the buffer has enough space to hold the output.
//
// Returns a pointer to the end of the string (i.e. the null character
// terminating the string).
// ----------------------------------------------------------------------

namespace {

// Various routines to encode integers to strings.

// We split data encodings into a group of 2 digits, 4 digits, 8 digits as
// it's easier to combine powers of two into scalar arithmetic.

// Previous implementation used a lookup table of 200 bytes for every 2 bytes
// and it was memory bound, any L1 cache miss would result in a much slower
// result. When benchmarking with a cache eviction rate of several percent,
// this implementation proved to be better.

// These constants represent '00', '0000' and '00000000' as ascii strings in
// integers. We can add these numbers if we encode to bytes from 0 to 9. as
// 'i' = '0' + i for 0 <= i <= 9.
constexpr uint32_t kTwoZeroBytes = 0x0101 * '0';
constexpr uint64_t kFourZeroBytes = 0x01010101 * '0';
constexpr uint64_t kEightZeroBytes = 0x0101010101010101ull * '0';

// * 103 / 1024 is a division by 10 for values from 0 to 99. It's also a
// division of a structure [k takes 2 bytes][m takes 2 bytes], then * 103 / 1024
// will be [k / 10][m / 10]. It allows parallel division.
constexpr uint64_t kDivisionBy10Mul = 103u;
constexpr uint64_t kDivisionBy10Div = 1 << 10;

// * 10486 / 1048576 is a division by 100 for values from 0 to 9999.
constexpr uint64_t kDivisionBy100Mul = 10486u;
constexpr uint64_t kDivisionBy100Div = 1 << 20;

// Encode functions write the ASCII output of input `n` to `out_str`.
inline char* EncodeHundred(uint32_t n, char* absl_nonnull out_str) { __builtin_trap() /* STUB: not implemented */; }

inline char* EncodeTenThousand(uint32_t n, char* absl_nonnull out_str) { __builtin_trap() /* STUB: not implemented */; }

// Helper function to produce an ASCII representation of `i`.
//
// Function returns an 8-byte integer which when summed with `kEightZeroBytes`,
// can be treated as a printable buffer with ascii representation of `i`,
// possibly with leading zeros.
//
// Example:
//
//  uint64_t buffer = PrepareEightDigits(102030) + kEightZeroBytes;
//  char* ascii = reinterpret_cast<char*>(&buffer);
//  // Note two leading zeros:
//  EXPECT_EQ(absl::string_view(ascii, 8), "00102030");
//
// Pre-condition: `i` must be less than 100000000.
inline uint64_t PrepareEightDigits(uint32_t i) { __builtin_trap() /* STUB: not implemented */; }


// Encodes v to buffer as 16 digits padded with leading zeros.
// Pre-condition: v must be < 10^16.
inline char* EncodePadded16(uint64_t v, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_ATTRIBUTE_ALWAYS_INLINE char* absl_nonnull EncodeFullU32(
    uint32_t n, char* absl_nonnull out_str) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_ATTRIBUTE_ALWAYS_INLINE char* absl_nonnull EncodeFullU64(
    uint64_t i, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_ATTRIBUTE_ALWAYS_INLINE char* absl_nonnull EncodeFullU128(
    uint128 i, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

void numbers_internal::PutTwoDigits(uint32_t i, char* absl_nonnull buf) { __builtin_trap() /* STUB: not implemented */; }

char* absl_nonnull numbers_internal::FastIntToBuffer(
    uint32_t n, char* absl_nonnull out_str) { __builtin_trap() /* STUB: not implemented */; }

char* absl_nonnull numbers_internal::FastIntToBuffer(
    int32_t i, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

char* absl_nonnull numbers_internal::FastIntToBuffer(
    uint64_t i, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

char* absl_nonnull numbers_internal::FastIntToBuffer(
    int64_t i, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

char* absl_nonnull numbers_internal::FastIntToBuffer(
    uint128 i, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

char* absl_nonnull numbers_internal::FastIntToBuffer(
    int128 i, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

// Although DBL_DIG is typically 15, DBL_MAX is normally represented with 17
// digits of precision. When converted to a string value with fewer digits
// of precision using strtod(), the result can be bigger than DBL_MAX due to
// a rounding error. Converting this value back to a double will produce an
// Inf which will trigger a SIGFPE if FP exceptions are enabled. We skip
// the precision check for sufficiently large values to avoid the SIGFPE.
static constexpr double kDoublePrecisionCheckMax =
    std::numeric_limits<double>::max() / 1.000000000000001;

char* absl_nonnull numbers_internal::RoundTripDoubleToBuffer(
    double d, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

namespace {

// This table is used to quickly calculate the base-ten exponent of a given
// float, and then to provide a multiplier to bring that number into the
// range 1-999,999,999, that is, into uint32_t range.  Finally, the exp
// string is made available so there is one less int-to-string conversion
// to be done.
struct Spec {
  double min_range;
  double multiplier;
  const char expstr[5];
};

// clang-format off
constexpr Spec kNegExpTable[] = {
    Spec{1.4e-45f, 1e+55, "e-45"},
    Spec{1e-44f, 1e+54, "e-44"},
    Spec{1e-43f, 1e+53, "e-43"},
    Spec{1e-42f, 1e+52, "e-42"},
    Spec{1e-41f, 1e+51, "e-41"},
    Spec{1e-40f, 1e+50, "e-40"},
    Spec{1e-39f, 1e+49, "e-39"},
    Spec{1e-38f, 1e+48, "e-38"},
    Spec{1e-37f, 1e+47, "e-37"},
    Spec{1e-36f, 1e+46, "e-36"},
    Spec{1e-35f, 1e+45, "e-35"},
    Spec{1e-34f, 1e+44, "e-34"},
    Spec{1e-33f, 1e+43, "e-33"},
    Spec{1e-32f, 1e+42, "e-32"},
    Spec{1e-31f, 1e+41, "e-31"},
    Spec{1e-30f, 1e+40, "e-30"},
    Spec{1e-29f, 1e+39, "e-29"},
    Spec{1e-28f, 1e+38, "e-28"},
    Spec{1e-27f, 1e+37, "e-27"},
    Spec{1e-26f, 1e+36, "e-26"},
    Spec{1e-25f, 1e+35, "e-25"},
    Spec{1e-24f, 1e+34, "e-24"},
    Spec{1e-23f, 1e+33, "e-23"},
    Spec{1e-22f, 1e+32, "e-22"},
    Spec{1e-21f, 1e+31, "e-21"},
    Spec{1e-20f, 1e+30, "e-20"},
    Spec{1e-19f, 1e+29, "e-19"},
    Spec{1e-18f, 1e+28, "e-18"},
    Spec{1e-17f, 1e+27, "e-17"},
    Spec{1e-16f, 1e+26, "e-16"},
    Spec{1e-15f, 1e+25, "e-15"},
    Spec{1e-14f, 1e+24, "e-14"},
    Spec{1e-13f, 1e+23, "e-13"},
    Spec{1e-12f, 1e+22, "e-12"},
    Spec{1e-11f, 1e+21, "e-11"},
    Spec{1e-10f, 1e+20, "e-10"},
    Spec{1e-09f, 1e+19, "e-09"},
    Spec{1e-08f, 1e+18, "e-08"},
    Spec{1e-07f, 1e+17, "e-07"},
    Spec{1e-06f, 1e+16, "e-06"},
    Spec{1e-05f, 1e+15, "e-05"},
    Spec{1e-04f, 1e+14, "e-04"},
};
// clang-format on

// clang-format off
constexpr Spec kPosExpTable[] = {
    Spec{1e+08f, 1e+02, "e+08"},
    Spec{1e+09f, 1e+01, "e+09"},
    Spec{1e+10f, 1e+00, "e+10"},
    Spec{1e+11f, 1e-01, "e+11"},
    Spec{1e+12f, 1e-02, "e+12"},
    Spec{1e+13f, 1e-03, "e+13"},
    Spec{1e+14f, 1e-04, "e+14"},
    Spec{1e+15f, 1e-05, "e+15"},
    Spec{1e+16f, 1e-06, "e+16"},
    Spec{1e+17f, 1e-07, "e+17"},
    Spec{1e+18f, 1e-08, "e+18"},
    Spec{1e+19f, 1e-09, "e+19"},
    Spec{1e+20f, 1e-10, "e+20"},
    Spec{1e+21f, 1e-11, "e+21"},
    Spec{1e+22f, 1e-12, "e+22"},
    Spec{1e+23f, 1e-13, "e+23"},
    Spec{1e+24f, 1e-14, "e+24"},
    Spec{1e+25f, 1e-15, "e+25"},
    Spec{1e+26f, 1e-16, "e+26"},
    Spec{1e+27f, 1e-17, "e+27"},
    Spec{1e+28f, 1e-18, "e+28"},
    Spec{1e+29f, 1e-19, "e+29"},
    Spec{1e+30f, 1e-20, "e+30"},
    Spec{1e+31f, 1e-21, "e+31"},
    Spec{1e+32f, 1e-22, "e+32"},
    Spec{1e+33f, 1e-23, "e+33"},
    Spec{1e+34f, 1e-24, "e+34"},
    Spec{1e+35f, 1e-25, "e+35"},
    Spec{1e+36f, 1e-26, "e+36"},
    Spec{1e+37f, 1e-27, "e+37"},
    Spec{1e+38f, 1e-28, "e+38"},
    Spec{1e+39,  1e-29, "e+39"},
};
// clang-format on

struct ExpCompare {
  bool operator()(const Spec& spec, double d) const { __builtin_trap() /* STUB: not implemented */; }
};

}  // namespace

// Utility routine(s) for RoundTripFloatToBuffer:
// OutputNecessaryDigits takes two 11-digit numbers, whose integer portion
// represents the fractional part of a floating-point number, and outputs a
// number that is in-between them, with the fewest digits possible. For
// instance, given 12345678900 and 12345876900, it would output "0123457".
// When there are multiple final digits that would satisfy this requirement,
// this routine attempts to use a digit that would represent the average of
// lower_double and upper_double.
//
// Although the routine works using integers, all callers use doubles, so
// for their convenience this routine accepts doubles.
static char* absl_nonnull OutputNecessaryDigits(double lower_double,
                                                double upper_double,
                                                char* absl_nonnull out) { __builtin_trap() /* STUB: not implemented */; }

// RoundTripFloatToBuffer converts the given float into a string which, if
// passed to strtof, will produce the exact same original float.  It does this
// by computing the range of possible doubles which map to the given float, and
// then examining the digits of the doubles in that range.  If all the doubles
// in the range start with "2.37", then clearly our float does, too.  As soon as
// they diverge, only one more digit is needed.
char* absl_nonnull numbers_internal::RoundTripFloatToBuffer(
    float f, char* absl_nonnull buffer) { __builtin_trap() /* STUB: not implemented */; }

// Given a 128-bit number expressed as a pair of uint64_t, high half first,
// return that number multiplied by the given 32-bit value.  If the result is
// too large to fit in a 128-bit number, divide it by 2 until it fits.
static std::pair<uint64_t, uint64_t> Mul32(std::pair<uint64_t, uint64_t> num,
                                           uint32_t mul) { __builtin_trap() /* STUB: not implemented */; }

// Compute num * 5 ^ expfive, and return the first 128 bits of the result,
// where the first bit is always a one.  So PowFive(1, 0) starts 0b100000,
// PowFive(1, 1) starts 0b101000, PowFive(1, 2) starts 0b110010, etc.
static std::pair<uint64_t, uint64_t> PowFive(uint64_t num, int expfive) { __builtin_trap() /* STUB: not implemented */; }

struct ExpDigits {
  int32_t exponent;
  char digits[6];
};

// SplitToSix converts value, a positive double-precision floating-point number,
// into a base-10 exponent and 6 ASCII digits, where the first digit is never
// zero.  For example, SplitToSix(1) returns an exponent of zero and a digits
// array of {'1', '0', '0', '0', '0', '0'}.  If value is exactly halfway between
// two possible representations, e.g. value = 100000.5, then "round to even" is
// performed.
static ExpDigits SplitToSix(const double value) { __builtin_trap() /* STUB: not implemented */; }

// Helper function for fast formatting of floating-point.
// The result is the same as "%g", a.k.a. "%.6g".
size_t numbers_internal::SixDigitsToBuffer(double d,
                                           char* absl_nonnull const buffer) { __builtin_trap() /* STUB: not implemented */; }

namespace {
// Represents integer values of digits.
// Uses 36 to indicate an invalid character since we support
// bases up to 36.
static constexpr std::array<int8_t, 256> kAsciiToInt = {
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,  // 16 36s.
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 0,  1,  2,  3,  4,  5,
    6,  7,  8,  9,  36, 36, 36, 36, 36, 36, 36, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
    36, 36, 36, 36, 36, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36};

// Parse the sign and optional hex or oct prefix in text.
inline bool safe_parse_sign_and_base(
    absl::string_view* absl_nonnull text /*inout*/,
    int* absl_nonnull base_ptr /*inout*/,
    bool* absl_nonnull negative_ptr /*output*/) { __builtin_trap() /* STUB: not implemented */; }

// Consume digits.
//
// The classic loop:
//
//   for each digit
//     value = value * base + digit
//   value *= sign
//
// The classic loop needs overflow checking.  It also fails on the most
// negative integer, -2147483648 in 32-bit two's complement representation.
//
// My improved loop:
//
//  if (!negative)
//    for each digit
//      value = value * base
//      value = value + digit
//  else
//    for each digit
//      value = value * base
//      value = value - digit
//
// Overflow checking becomes simple.

// Lookup tables per IntType:
// vmax/base and vmin/base are precomputed because division costs at least 8ns.
// TODO(junyer): Doing this per base instead (i.e. an array of structs, not a
// struct of arrays) would probably be better in terms of d-cache for the most
// commonly used bases.
template <typename IntType>
struct LookupTables {
  ABSL_CONST_INIT static const IntType kVmaxOverBase[];
  ABSL_CONST_INIT static const IntType kVminOverBase[];
};

// An array initializer macro for X/base where base in [0, 36].
// However, note that lookups for base in [0, 1] should never happen because
// base has been validated to be in [2, 36] by safe_parse_sign_and_base().
#define X_OVER_BASE_INITIALIZER(X)                                        \
  {                                                                       \
    0, 0, X / 2, X / 3, X / 4, X / 5, X / 6, X / 7, X / 8, X / 9, X / 10, \
        X / 11, X / 12, X / 13, X / 14, X / 15, X / 16, X / 17, X / 18,   \
        X / 19, X / 20, X / 21, X / 22, X / 23, X / 24, X / 25, X / 26,   \
        X / 27, X / 28, X / 29, X / 30, X / 31, X / 32, X / 33, X / 34,   \
        X / 35, X / 36,                                                   \
  }

// This kVmaxOverBase is generated with
//  for (int base = 2; base < 37; ++base) {
//    absl::uint128 max = std::numeric_limits<absl::uint128>::max();
//    auto result = max / base;
//    std::cout << "    MakeUint128(" << absl::Uint128High64(result) << "u, "
//              << absl::Uint128Low64(result) << "u),\n";
//  }
// See https://godbolt.org/z/aneYsb
//
// uint128& operator/=(uint128) is not constexpr, so hardcode the resulting
// array to avoid a static initializer.
template <>
ABSL_CONST_INIT const uint128 LookupTables<uint128>::kVmaxOverBase[] = {
    0,
    0,
    MakeUint128(9223372036854775807u, 18446744073709551615u),
    MakeUint128(6148914691236517205u, 6148914691236517205u),
    MakeUint128(4611686018427387903u, 18446744073709551615u),
    MakeUint128(3689348814741910323u, 3689348814741910323u),
    MakeUint128(3074457345618258602u, 12297829382473034410u),
    MakeUint128(2635249153387078802u, 5270498306774157604u),
    MakeUint128(2305843009213693951u, 18446744073709551615u),
    MakeUint128(2049638230412172401u, 14347467612885206812u),
    MakeUint128(1844674407370955161u, 11068046444225730969u),
    MakeUint128(1676976733973595601u, 8384883669867978007u),
    MakeUint128(1537228672809129301u, 6148914691236517205u),
    MakeUint128(1418980313362273201u, 4256940940086819603u),
    MakeUint128(1317624576693539401u, 2635249153387078802u),
    MakeUint128(1229782938247303441u, 1229782938247303441u),
    MakeUint128(1152921504606846975u, 18446744073709551615u),
    MakeUint128(1085102592571150095u, 1085102592571150095u),
    MakeUint128(1024819115206086200u, 16397105843297379214u),
    MakeUint128(970881267037344821u, 16504981539634861972u),
    MakeUint128(922337203685477580u, 14757395258967641292u),
    MakeUint128(878416384462359600u, 14054662151397753612u),
    MakeUint128(838488366986797800u, 13415813871788764811u),
    MakeUint128(802032351030850070u, 4812194106185100421u),
    MakeUint128(768614336404564650u, 12297829382473034410u),
    MakeUint128(737869762948382064u, 11805916207174113034u),
    MakeUint128(709490156681136600u, 11351842506898185609u),
    MakeUint128(683212743470724133u, 17080318586768103348u),
    MakeUint128(658812288346769700u, 10540996613548315209u),
    MakeUint128(636094623231363848u, 15266270957552732371u),
    MakeUint128(614891469123651720u, 9838263505978427528u),
    MakeUint128(595056260442243600u, 9520900167075897608u),
    MakeUint128(576460752303423487u, 18446744073709551615u),
    MakeUint128(558992244657865200u, 8943875914525843207u),
    MakeUint128(542551296285575047u, 9765923333140350855u),
    MakeUint128(527049830677415760u, 8432797290838652167u),
    MakeUint128(512409557603043100u, 8198552921648689607u),
};

// This kVmaxOverBase generated with
//   for (int base = 2; base < 37; ++base) {
//    absl::int128 max = std::numeric_limits<absl::int128>::max();
//    auto result = max / base;
//    std::cout << "\tMakeInt128(" << absl::Int128High64(result) << ", "
//              << absl::Int128Low64(result) << "u),\n";
//  }
// See https://godbolt.org/z/7djYWz
//
// int128& operator/=(int128) is not constexpr, so hardcode the resulting array
// to avoid a static initializer.
template <>
ABSL_CONST_INIT const int128 LookupTables<int128>::kVmaxOverBase[] = {
    0,
    0,
    MakeInt128(4611686018427387903, 18446744073709551615u),
    MakeInt128(3074457345618258602, 12297829382473034410u),
    MakeInt128(2305843009213693951, 18446744073709551615u),
    MakeInt128(1844674407370955161, 11068046444225730969u),
    MakeInt128(1537228672809129301, 6148914691236517205u),
    MakeInt128(1317624576693539401, 2635249153387078802u),
    MakeInt128(1152921504606846975, 18446744073709551615u),
    MakeInt128(1024819115206086200, 16397105843297379214u),
    MakeInt128(922337203685477580, 14757395258967641292u),
    MakeInt128(838488366986797800, 13415813871788764811u),
    MakeInt128(768614336404564650, 12297829382473034410u),
    MakeInt128(709490156681136600, 11351842506898185609u),
    MakeInt128(658812288346769700, 10540996613548315209u),
    MakeInt128(614891469123651720, 9838263505978427528u),
    MakeInt128(576460752303423487, 18446744073709551615u),
    MakeInt128(542551296285575047, 9765923333140350855u),
    MakeInt128(512409557603043100, 8198552921648689607u),
    MakeInt128(485440633518672410, 17475862806672206794u),
    MakeInt128(461168601842738790, 7378697629483820646u),
    MakeInt128(439208192231179800, 7027331075698876806u),
    MakeInt128(419244183493398900, 6707906935894382405u),
    MakeInt128(401016175515425035, 2406097053092550210u),
    MakeInt128(384307168202282325, 6148914691236517205u),
    MakeInt128(368934881474191032, 5902958103587056517u),
    MakeInt128(354745078340568300, 5675921253449092804u),
    MakeInt128(341606371735362066, 17763531330238827482u),
    MakeInt128(329406144173384850, 5270498306774157604u),
    MakeInt128(318047311615681924, 7633135478776366185u),
    MakeInt128(307445734561825860, 4919131752989213764u),
    MakeInt128(297528130221121800, 4760450083537948804u),
    MakeInt128(288230376151711743, 18446744073709551615u),
    MakeInt128(279496122328932600, 4471937957262921603u),
    MakeInt128(271275648142787523, 14106333703424951235u),
    MakeInt128(263524915338707880, 4216398645419326083u),
    MakeInt128(256204778801521550, 4099276460824344803u),
};

// This kVminOverBase generated with
//  for (int base = 2; base < 37; ++base) {
//    absl::int128 min = std::numeric_limits<absl::int128>::min();
//    auto result = min / base;
//    std::cout << "\tMakeInt128(" << absl::Int128High64(result) << ", "
//              << absl::Int128Low64(result) << "u),\n";
//  }
//
// See https://godbolt.org/z/7djYWz
//
// int128& operator/=(int128) is not constexpr, so hardcode the resulting array
// to avoid a static initializer.
template <>
ABSL_CONST_INIT const int128 LookupTables<int128>::kVminOverBase[] = {
    0,
    0,
    MakeInt128(-4611686018427387904, 0u),
    MakeInt128(-3074457345618258603, 6148914691236517206u),
    MakeInt128(-2305843009213693952, 0u),
    MakeInt128(-1844674407370955162, 7378697629483820647u),
    MakeInt128(-1537228672809129302, 12297829382473034411u),
    MakeInt128(-1317624576693539402, 15811494920322472814u),
    MakeInt128(-1152921504606846976, 0u),
    MakeInt128(-1024819115206086201, 2049638230412172402u),
    MakeInt128(-922337203685477581, 3689348814741910324u),
    MakeInt128(-838488366986797801, 5030930201920786805u),
    MakeInt128(-768614336404564651, 6148914691236517206u),
    MakeInt128(-709490156681136601, 7094901566811366007u),
    MakeInt128(-658812288346769701, 7905747460161236407u),
    MakeInt128(-614891469123651721, 8608480567731124088u),
    MakeInt128(-576460752303423488, 0u),
    MakeInt128(-542551296285575048, 8680820740569200761u),
    MakeInt128(-512409557603043101, 10248191152060862009u),
    MakeInt128(-485440633518672411, 970881267037344822u),
    MakeInt128(-461168601842738791, 11068046444225730970u),
    MakeInt128(-439208192231179801, 11419412998010674810u),
    MakeInt128(-419244183493398901, 11738837137815169211u),
    MakeInt128(-401016175515425036, 16040647020617001406u),
    MakeInt128(-384307168202282326, 12297829382473034411u),
    MakeInt128(-368934881474191033, 12543785970122495099u),
    MakeInt128(-354745078340568301, 12770822820260458812u),
    MakeInt128(-341606371735362067, 683212743470724134u),
    MakeInt128(-329406144173384851, 13176245766935394012u),
    MakeInt128(-318047311615681925, 10813608594933185431u),
    MakeInt128(-307445734561825861, 13527612320720337852u),
    MakeInt128(-297528130221121801, 13686293990171602812u),
    MakeInt128(-288230376151711744, 0u),
    MakeInt128(-279496122328932601, 13974806116446630013u),
    MakeInt128(-271275648142787524, 4340410370284600381u),
    MakeInt128(-263524915338707881, 14230345428290225533u),
    MakeInt128(-256204778801521551, 14347467612885206813u),
};

template <typename IntType>
ABSL_CONST_INIT const IntType LookupTables<IntType>::kVmaxOverBase[] =
    X_OVER_BASE_INITIALIZER(std::numeric_limits<IntType>::max());

template <typename IntType>
ABSL_CONST_INIT const IntType LookupTables<IntType>::kVminOverBase[] =
    X_OVER_BASE_INITIALIZER(std::numeric_limits<IntType>::min());

#undef X_OVER_BASE_INITIALIZER

template <typename IntType>
inline bool safe_parse_positive_int(absl::string_view text, int base,
                                    IntType* absl_nonnull value_p) { __builtin_trap() /* STUB: not implemented */; }

template <typename IntType>
inline bool safe_parse_negative_int(absl::string_view text, int base,
                                    IntType* absl_nonnull value_p) { __builtin_trap() /* STUB: not implemented */; }

// Input format based on POSIX.1-2008 strtol
// http://pubs.opengroup.org/onlinepubs/9699919799/functions/strtol.html
template <typename IntType>
inline bool safe_int_internal(absl::string_view text,
                              IntType* absl_nonnull value_p, int base) { __builtin_trap() /* STUB: not implemented */; }

template <typename IntType>
inline bool safe_uint_internal(absl::string_view text,
                               IntType* absl_nonnull value_p, int base) { __builtin_trap() /* STUB: not implemented */; }
}  // anonymous namespace

namespace numbers_internal {

// Digit conversion.
ABSL_CONST_INIT ABSL_DLL const char kHexChar[] =
    "0123456789abcdef";

ABSL_CONST_INIT ABSL_DLL const char kHexTable[513] =
    "000102030405060708090a0b0c0d0e0f"
    "101112131415161718191a1b1c1d1e1f"
    "202122232425262728292a2b2c2d2e2f"
    "303132333435363738393a3b3c3d3e3f"
    "404142434445464748494a4b4c4d4e4f"
    "505152535455565758595a5b5c5d5e5f"
    "606162636465666768696a6b6c6d6e6f"
    "707172737475767778797a7b7c7d7e7f"
    "808182838485868788898a8b8c8d8e8f"
    "909192939495969798999a9b9c9d9e9f"
    "a0a1a2a3a4a5a6a7a8a9aaabacadaeaf"
    "b0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
    "c0c1c2c3c4c5c6c7c8c9cacbcccdcecf"
    "d0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
    "e0e1e2e3e4e5e6e7e8e9eaebecedeeef"
    "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";

bool safe_strto8_base(absl::string_view text, int8_t* absl_nonnull value,
                      int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strto16_base(absl::string_view text, int16_t* absl_nonnull value,
                       int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strto32_base(absl::string_view text, int32_t* absl_nonnull value,
                       int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strto64_base(absl::string_view text, int64_t* absl_nonnull value,
                       int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strto128_base(absl::string_view text, int128* absl_nonnull value,
                        int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strtou8_base(absl::string_view text, uint8_t* absl_nonnull value,
                       int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strtou16_base(absl::string_view text, uint16_t* absl_nonnull value,
                        int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strtou32_base(absl::string_view text, uint32_t* absl_nonnull value,
                        int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strtou64_base(absl::string_view text, uint64_t* absl_nonnull value,
                        int base) { __builtin_trap() /* STUB: not implemented */; }

bool safe_strtou128_base(absl::string_view text, uint128* absl_nonnull value,
                         int base) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace numbers_internal
ABSL_NAMESPACE_END
}  // namespace absl
