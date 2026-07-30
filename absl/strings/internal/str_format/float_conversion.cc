// Copyright 2020 The Abseil Authors.
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

#include "absl/strings/internal/str_format/float_conversion.h"

#include <string.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <optional>
#include <string>
#include <type_traits>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/optimization.h"
#include "absl/functional/function_ref.h"
#include "absl/meta/type_traits.h"
#include "absl/numeric/bits.h"
#include "absl/numeric/int128.h"
#include "absl/numeric/internal/representation.h"
#include "absl/strings/internal/str_format/extension.h"
#include "absl/strings/numbers.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace str_format_internal {

namespace {

using ::absl::numeric_internal::IsDoubleDouble;

// The code below wants to avoid heap allocations.
// To do so it needs to allocate memory on the stack.
// `StackArray` will allocate memory on the stack in the form of a uint32_t
// array and call the provided callback with said memory.
// It will allocate memory in increments of 512 bytes. We could allocate the
// largest needed unconditionally, but that is more than we need in most of
// cases. This way we use less stack in the common cases.
class StackArray {
  using Func = absl::FunctionRef<void(absl::Span<uint32_t>)>;
  static constexpr size_t kStep = 512 / sizeof(uint32_t);
  // 5 steps is 2560 bytes, which is enough to hold a long double with the
  // largest/smallest exponents.
  // The operations below will static_assert their particular maximum.
  static constexpr size_t kNumSteps = 5;

  // We do not want this function to be inlined.
  // Otherwise the caller will allocate the stack space unnecessarily for all
  // the variants even though it only calls one.
  template <size_t steps>
  ABSL_ATTRIBUTE_NOINLINE static void RunWithCapacityImpl(Func f) { __builtin_trap() /* STUB: not implemented */; }

 public:
  static constexpr size_t kMaxCapacity = kStep * kNumSteps;

  static void RunWithCapacity(size_t capacity, Func f) { __builtin_trap() /* STUB: not implemented */; }
};

// Calculates `10 * (*v) + carry` and stores the result in `*v` and returns
// the carry.
// Requires: `0 <= carry <= 9`
template <typename Int>
inline char MultiplyBy10WithCarry(Int* v, char carry) { __builtin_trap() /* STUB: not implemented */; }

// Calculates `(2^64 * carry + *v) / 10`.
// Stores the quotient in `*v` and returns the remainder.
// Requires: `0 <= carry <= 9`
inline char DivideBy10WithCarry(uint64_t* v, char carry) { __builtin_trap() /* STUB: not implemented */; }

using MaxFloatType = std::conditional_t<IsDoubleDouble(), double, long double>;

// Generates the decimal representation for an integer of the form `v * 2^exp`,
// where `v` and `exp` are both positive integers.
// It generates the digits from the left (ie the most significant digit first)
// to allow for direct printing into the sink.
//
// Requires `0 <= exp` and `exp <= numeric_limits<MaxFloatType>::max_exponent`.
class BinaryToDecimal {
  static constexpr size_t ChunksNeeded(int exp) { return {}; }

 public:
  // Run the conversion for `v * 2^exp` and call `f(binary_to_decimal)`.
  // This function will allocate enough stack space to perform the conversion.
  static void RunConversion(uint128 v, int exp,
                            absl::FunctionRef<void(BinaryToDecimal)> f) { __builtin_trap() /* STUB: not implemented */; }

  size_t TotalDigits() const { __builtin_trap() /* STUB: not implemented */; }

  // See the current block of digits.
  absl::string_view CurrentDigits() const { __builtin_trap() /* STUB: not implemented */; }

  // Advance the current view of digits.
  // Returns `false` when no more digits are available.
  bool AdvanceDigits() { __builtin_trap() /* STUB: not implemented */; }

 private:
  BinaryToDecimal(absl::Span<uint32_t> data, uint128 v, int exp) : data_(data) { __builtin_trap() /* STUB: not implemented */; }

 private:
  static constexpr size_t kDigitsPerChunk = 9;

  size_t decimal_start_;
  size_t decimal_end_;

  std::array<char, kDigitsPerChunk> digits_;
  size_t size_ = 0;

  absl::Span<uint32_t> data_;
};

// Converts a value of the form `x * 2^-exp` into a sequence of decimal digits.
// Requires `-exp < 0` and
// `-exp >= limits<MaxFloatType>::min_exponent - limits<MaxFloatType>::digits`.
class FractionalDigitGenerator {
 private:
  static constexpr size_t ChunksNeeded(int exp) { return {}; }

 public:
  // Run the conversion for `v * 2^exp` and call `f(generator)`.
  // This function will allocate enough stack space to perform the conversion.
  static void RunConversion(
      uint128 v, int exp, absl::FunctionRef<void(FractionalDigitGenerator)> f) { __builtin_trap() /* STUB: not implemented */; }

  // Returns true if there are any more non-zero digits left.
  bool HasMoreDigits() const { __builtin_trap() /* STUB: not implemented */; }

  // Returns true if the remainder digits are greater than 5000...
  bool IsGreaterThanHalf() const { __builtin_trap() /* STUB: not implemented */; }
  // Returns true if the remainder digits are exactly 5000...
  bool IsExactlyHalf() const { __builtin_trap() /* STUB: not implemented */; }

  struct Digits {
    char digit_before_nine;
    size_t num_nines;
  };

  // Get the next set of digits.
  // They are composed by a non-9 digit followed by a runs of zero or more 9s.
  Digits GetDigits() { __builtin_trap() /* STUB: not implemented */; }

 private:
  // Return the next digit.
  char GetOneDigit() { __builtin_trap() /* STUB: not implemented */; }

  FractionalDigitGenerator(absl::Span<uint32_t> data, uint128 v, int exp)
      : after_chunk_index_(static_cast<size_t>(exp / 32 + 1)), data_(data) { __builtin_trap() /* STUB: not implemented */; }

  char next_digit_;
  size_t after_chunk_index_;
  absl::Span<uint32_t> data_;
};

// Count the number of leading zero bits.
int LeadingZeros(uint64_t v) { __builtin_trap() /* STUB: not implemented */; }
int LeadingZeros(uint128 v) { __builtin_trap() /* STUB: not implemented */; }

// Round up the text digits starting at `p`.
// The buffer must have an extra digit that is known to not need rounding.
// This is done below by having an extra '0' digit on the left.
void RoundUp(char *p) { __builtin_trap() /* STUB: not implemented */; }

// Check the previous digit and round up or down to follow the round-to-even
// policy.
void RoundToEven(char *p) { __builtin_trap() /* STUB: not implemented */; }

// Simple integral decimal digit printing for values that fit in 64-bits.
// Returns the pointer to the last written digit.
char *PrintIntegralDigitsFromRightFast(uint64_t v, char *p) { __builtin_trap() /* STUB: not implemented */; }

// Simple integral decimal digit printing for values that fit in 128-bits.
// Returns the pointer to the last written digit.
char *PrintIntegralDigitsFromRightFast(uint128 v, char *p) { __builtin_trap() /* STUB: not implemented */; }

// Simple fractional decimal digit printing for values that fir in 64-bits after
// shifting.
// Performs rounding if necessary to fit within `precision`.
// Returns the pointer to one after the last character written.
char* PrintFractionalDigitsFast(uint64_t v,
                                char* start,
                                int exp,
                                size_t precision) { __builtin_trap() /* STUB: not implemented */; }

// Simple fractional decimal digit printing for values that fir in 128-bits
// after shifting.
// Performs rounding if necessary to fit within `precision`.
// Returns the pointer to one after the last character written.
char* PrintFractionalDigitsFast(uint128 v,
                                char* start,
                                int exp,
                                size_t precision) { __builtin_trap() /* STUB: not implemented */; }

struct FractionalDigitPrinterResult {
  char* end;
  size_t skipped_zeros;
  bool nonzero_remainder;
};

FractionalDigitPrinterResult PrintFractionalDigitsScientific(
    uint64_t v, char* start, int exp, size_t precision, bool skip_zeros) { __builtin_trap() /* STUB: not implemented */; }

FractionalDigitPrinterResult PrintFractionalDigitsScientific(
    uint128 v, char* start, int exp, size_t precision, bool skip_zeros) { __builtin_trap() /* STUB: not implemented */; }

struct FormatState {
  char sign_char;
  size_t precision;
  const FormatConversionSpecImpl &conv;
  FormatSinkImpl *sink;

  // In `alt` mode (flag #) we keep the `.` even if there are no fractional
  // digits. In non-alt mode, we strip it.
  bool ShouldPrintDot() const { __builtin_trap() /* STUB: not implemented */; }
};

struct Padding {
  size_t left_spaces;
  size_t zeros;
  size_t right_spaces;
};

Padding ExtraWidthToPadding(size_t total_size, const FormatState &state) { __builtin_trap() /* STUB: not implemented */; }

void FinalPrint(const FormatState& state,
                absl::string_view data,
                size_t padding_offset,
                size_t trailing_zeros,
                absl::string_view data_postfix) { __builtin_trap() /* STUB: not implemented */; }

// Fastpath %f formatter for when the shifted value fits in a simple integral
// type.
// Prints `v*2^exp` with the options from `state`.
template <typename Int>
void FormatFFast(Int v, int exp, const FormatState &state) { __builtin_trap() /* STUB: not implemented */; }

// Slow %f formatter for when the shifted value does not fit in a uint128, and
// `exp > 0`.
// Prints `v*2^exp` with the options from `state`.
// This one is guaranteed to not have fractional digits, so we don't have to
// worry about anything after the `.`.
void FormatFPositiveExpSlow(uint128 v, int exp, const FormatState& state,
                            bool strip_trailing_zeros = false) { __builtin_trap() /* STUB: not implemented */; }

// Slow %f formatter for when the shifted value does not fit in a uint128, and
// `exp < 0`.
// Prints `v*2^exp` with the options from `state`.
// This one is guaranteed to be < 1.0, so we don't have to worry about integral
// digits.
void FormatFNegativeExpSlow(uint128 v, int exp, const FormatState& state,
                            size_t digits_to_trim = 0) { __builtin_trap() /* STUB: not implemented */; }

template <typename Int>
void FormatF(Int mantissa, int exp, const FormatState &state) { __builtin_trap() /* STUB: not implemented */; }

// Grab the group of four bits (nibble) from `n`. E.g., nibble 1 corresponds to
// bits 4-7.
template <typename Int>
uint8_t GetNibble(Int n, size_t nibble_index) { __builtin_trap() /* STUB: not implemented */; }

// Add one to the given nibble, applying carry to higher nibbles. Returns true
// if overflow, false otherwise.
template <typename Int>
bool IncrementNibble(size_t nibble_index, Int* n) { __builtin_trap() /* STUB: not implemented */; }

// Return a mask with 1's in the given nibble and all lower nibbles.
template <typename Int>
Int MaskUpToNibbleInclusive(size_t nibble_index) { __builtin_trap() /* STUB: not implemented */; }

// Return a mask with 1's below the given nibble.
template <typename Int>
Int MaskUpToNibbleExclusive(size_t nibble_index) { __builtin_trap() /* STUB: not implemented */; }

template <typename Int>
Int MoveToNibble(uint8_t nibble, size_t nibble_index) { __builtin_trap() /* STUB: not implemented */; }

// Given mantissa size, find optimal # of mantissa bits to put in initial digit.
//
// In the hex representation we keep a single hex digit to the left of the dot.
// However, the question as to how many bits of the mantissa should be put into
// that hex digit in theory is arbitrary, but in practice it is optimal to
// choose based on the size of the mantissa. E.g., for a `double`, there are 53
// mantissa bits, so that means that we should put 1 bit to the left of the dot,
// thereby leaving 52 bits to the right, which is evenly divisible by four and
// thus all fractional digits represent actual precision. For a `long double`,
// on the other hand, there are 64 bits of mantissa, thus we can use all four
// bits for the initial hex digit and still have a number left over (60) that is
// a multiple of four. Once again, the goal is to have all fractional digits
// represent real precision.
template <typename Float>
constexpr size_t HexFloatLeadingDigitSizeInBits() { return {}; }

// This function captures the rounding behavior of glibc for hex float
// representations. E.g. when rounding 0x1.ab800000 to a precision of .2
// ("%.2a") glibc will round up because it rounds toward the even number (since
// 0xb is an odd number, it will round up to 0xc). However, when rounding at a
// point that is not followed by 800000..., it disregards the parity and rounds
// up if > 8 and rounds down if < 8.
template <typename Int>
bool HexFloatNeedsRoundUp(Int mantissa,
                          size_t final_nibble_displayed,
                          uint8_t leading) { __builtin_trap() /* STUB: not implemented */; }

// Stores values associated with a Float type needed by the FormatA
// implementation in order to avoid templatizing that function by the Float
// type.
struct HexFloatTypeParams {
  template <typename Float>
  explicit HexFloatTypeParams(Float)
      : min_exponent(std::numeric_limits<Float>::min_exponent - 1),
        leading_digit_size_bits(HexFloatLeadingDigitSizeInBits<Float>()) { __builtin_trap() /* STUB: not implemented */; }

  int min_exponent;
  size_t leading_digit_size_bits;
};

// Hex Float Rounding. First check if we need to round; if so, then we do that
// by manipulating (incrementing) the mantissa, that way we can later print the
// mantissa digits by iterating through them in the same way regardless of
// whether a rounding happened.
template <typename Int>
void FormatARound(bool precision_specified, const FormatState &state,
                  uint8_t *leading, Int *mantissa, int *exp) { __builtin_trap() /* STUB: not implemented */; }

template <typename Int>
void FormatANormalize(const HexFloatTypeParams float_traits, uint8_t *leading,
                      Int *mantissa, int *exp) { __builtin_trap() /* STUB: not implemented */; }

template <typename Int>
void FormatA(const HexFloatTypeParams float_traits, Int mantissa, int exp,
             bool uppercase, const FormatState &state) { __builtin_trap() /* STUB: not implemented */; }

char *CopyStringTo(absl::string_view v, char *out) { __builtin_trap() /* STUB: not implemented */; }

template <typename Float>
bool FallbackToSnprintf(const Float v, const FormatConversionSpecImpl &conv,
                        FormatSinkImpl *sink) { __builtin_trap() /* STUB: not implemented */; }

// 128-bits in decimal: ceil(128*log(2)/log(10))
//   or std::numeric_limits<__uint128_t>::digits10
constexpr size_t kMaxFixedPrecision = 39;

constexpr size_t kBufferLength = /*sign*/ 1 +
                                 /*integer*/ kMaxFixedPrecision +
                                 /*point*/ 1 +
                                 /*fraction*/ kMaxFixedPrecision +
                                 /*exponent e+123*/ 5;

struct Buffer {
  void push_front(char c) { __builtin_trap() /* STUB: not implemented */; }
  void push_back(char c) { __builtin_trap() /* STUB: not implemented */; }
  void pop_back() { __builtin_trap() /* STUB: not implemented */; }

  char &back() const { __builtin_trap() /* STUB: not implemented */; }

  char last_digit() const { __builtin_trap() /* STUB: not implemented */; }

  size_t size() const { __builtin_trap() /* STUB: not implemented */; }

  char data[kBufferLength];
  char *begin;
  char *end;
};

enum class FormatStyle { Fixed, Precision };

// If the value is Inf or Nan, print it and return true.
// Otherwise, return false.
template <typename Float>
bool ConvertNonNumericFloats(char sign_char, Float v,
                             const FormatConversionSpecImpl &conv,
                             FormatSinkImpl *sink) { __builtin_trap() /* STUB: not implemented */; }

// Round up the last digit of the value.
// It will carry over and potentially overflow. 'exp' will be adjusted in that
// case.
template <FormatStyle mode>
void RoundUp(Buffer *buffer, int *exp) { __builtin_trap() /* STUB: not implemented */; }

template <typename Float, typename Int>
constexpr bool CanFitMantissa() { return {}; }

template <typename Float>
struct Decomposed {
  using MantissaType =
      std::conditional_t<std::is_same_v<long double, Float>, uint128, uint64_t>;
  static_assert(std::numeric_limits<Float>::digits <= sizeof(MantissaType) * 8,
                "");
  MantissaType mantissa;
  int exponent;
};

// Decompose the double into an integer mantissa and an exponent.
template <typename Float>
Decomposed<Float> Decompose(Float v) {
  int exp;
  Float m = std::frexp(v, &exp);
  m = std::ldexp(m, std::numeric_limits<Float>::digits);
  exp -= std::numeric_limits<Float>::digits;

  return {static_cast<typename Decomposed<Float>::MantissaType>(m), exp};
}

// Print 'digits' as decimal.
// In Fixed mode, we add a '.' at the end.
// In Precision mode, we add a '.' after the first digit.
template <FormatStyle mode, typename Int>
size_t PrintIntegralDigits(Int digits, Buffer* out) {
  size_t printed = 0;
  if (digits) {
    for (; digits; digits /= 10) out->push_front(digits % 10 + '0');
    printed = out->size();
    if (mode == FormatStyle::Precision) {
      out->push_front(*out->begin);
      out->begin[1] = '.';
    } else {
      out->push_back('.');
    }
  } else if (mode == FormatStyle::Fixed) {
    out->push_front('0');
    out->push_back('.');
    printed = 1;
  }
  return printed;
}

std::optional<int> GetOneDigit(BinaryToDecimal& btd,
                               absl::string_view& digits_view) {
  if (digits_view.empty() && !btd.AdvanceDigits()) {
    return std::nullopt;
  }
  char d = digits_view.front();
  digits_view.remove_prefix(1);
  return d - '0';
}

struct DigitRun {
  std::optional<int> digit;
  size_t nines;
};

DigitRun GetDigits(BinaryToDecimal& btd, absl::string_view& digits_view) {
  auto peek_digit = [&]() -> std::optional<int> {
    if (digits_view.empty()) {
      if (!btd.AdvanceDigits()) return std::nullopt;
      digits_view = btd.CurrentDigits();
    }
    return digits_view.front() - '0';
  };

  auto digit_before_nines = GetOneDigit(btd, digits_view);
  if (!digit_before_nines.has_value()) return {std::nullopt, 0};

  auto next_digit = peek_digit();
  size_t num_nines = 0;
  while (next_digit == 9) {
    // consume the 9
    GetOneDigit(btd, digits_view);
    ++num_nines;
    next_digit = peek_digit();
  }
  return digit_before_nines == 9 ? DigitRun{std::nullopt, num_nines + 1}
                                 : DigitRun{digit_before_nines, num_nines};
}

template <typename Int>
void FormatE(Int mantissa, int exp, bool uppercase, const FormatState& state) {
  if (exp > 0) {
    const int total_bits =
        static_cast<int>(sizeof(Int) * 8) - LeadingZeros(mantissa) + exp;
    if (total_bits > 128) {
      FormatEPositiveExpSlow(mantissa, exp, uppercase, state);
      return;
    }
  } else {
    if (ABSL_PREDICT_FALSE(exp < -128)) {
      FormatENegativeExpSlow(mantissa, exp, uppercase, state);
      return;
    }
  }
  FormatEFast(mantissa, exp, uppercase, state);
}

// Guaranteed to fit into 128 bits at this point
template <typename Int>
void FormatEFast(Int v, int exp, bool uppercase, const FormatState& state) {
  if (!v) {
    absl::string_view mantissa_str = state.ShouldPrintDot() ? "0." : "0";
    FinalPrint(state, mantissa_str, 0, state.precision,
               uppercase ? "E+00" : "e+00");
    return;
  }
  constexpr int kInputBits = sizeof(Int) * 8;
  constexpr int kMaxFractionalDigits = 128;
  constexpr int kBufferSize = 2 +                    // '.' + rounding
                              kMaxFixedPrecision +   // Integral
                              kMaxFractionalDigits;  // Fractional
  const int total_bits = kInputBits - LeadingZeros(v) + exp;
  char buffer[kBufferSize];
  char* integral_start = buffer + 2;
  char* integral_end = buffer + 2 + kMaxFixedPrecision;
  char* final_start;
  char* final_end;
  bool zero_integral = false;
  int scientific_exp = 0;
  size_t digits_printed = 0;
  size_t trailing_zeros = 0;
  bool has_more_non_zero = false;

  auto check_integral_zeros =
      [](char* const begin, char* const end,
         const size_t precision, size_t digits_processed) -> bool {
    // When considering rounding to even, we care about the digits after the
    // round digit which means the total digits to move from the start is
    // precision + 2 since the first digit we print before the decimal point
    // is not a part of precision.
    size_t digit_upper_bound = precision + 2;
    if (digits_processed > digit_upper_bound) {
      return std::any_of(begin + digit_upper_bound, end,
                         [](char c) { return c != '0'; });
    }
    return false;
  };

  if (exp >= 0) {
    integral_end = total_bits <= 64 ? numbers_internal::FastIntToBuffer(
                               static_cast<uint64_t>(v) << exp, integral_start)
                         : numbers_internal::FastIntToBuffer(
                               static_cast<uint128>(v) << exp, integral_start);
    *integral_end = '0';
    final_start = integral_start;
    // Integral is guaranteed to be non-zero at this point.
    scientific_exp = static_cast<int>(integral_end - integral_start) - 1;
    digits_printed = static_cast<size_t>(integral_end - integral_start);
    final_end = integral_end;
    has_more_non_zero = check_integral_zeros(integral_start, integral_end,
                                             state.precision, digits_printed);
  } else {
    exp = -exp;
    if (exp < kInputBits) {
      integral_end =
          numbers_internal::FastIntToBuffer(v >> exp, integral_start);
    }
    *integral_end = '0';
    // We didn't move integral_start and it gets set to 0 in
    zero_integral = exp >= kInputBits || v >> exp == 0;
    if (!zero_integral) {
      digits_printed = static_cast<size_t>(integral_end - integral_start);
      has_more_non_zero = check_integral_zeros(integral_start, integral_end,
                                               state.precision, digits_printed);
      final_end = integral_end;
    }
    // Print fractional digits
    char* fractional_start = integral_end;

    size_t digits_to_print = (state.precision + 1) >= digits_printed
                                 ? state.precision + 1 - digits_printed
                                 : 0;
    bool print_extra = digits_printed <= state.precision + 1;
    auto [fractional_end, skipped_zeros, has_nonzero_rem] =
        exp <= 64 ? PrintFractionalDigitsScientific(
                        v, fractional_start, exp, digits_to_print + print_extra,
                        zero_integral)
                  : PrintFractionalDigitsScientific(
                        static_cast<uint128>(v), fractional_start, exp,
                        digits_to_print + print_extra, zero_integral);
    final_end = fractional_end;
    *fractional_end = '0';
    has_more_non_zero |= has_nonzero_rem;
    digits_printed += static_cast<size_t>(fractional_end - fractional_start);
    if (zero_integral) {
      scientific_exp = -1 * static_cast<int>(skipped_zeros + 1);
    } else {
      scientific_exp = static_cast<int>(integral_end - integral_start) - 1;
    }
    // Don't do any rounding here, we will do it ourselves.
    final_start = zero_integral ? fractional_start : integral_start;
  }

  // For rounding
  if (digits_printed >= state.precision + 1) {
    final_start[-1] = '0';
    char* round_digit_ptr = final_start + 1 + state.precision;
    if (*round_digit_ptr > '5') {
      RoundUp(round_digit_ptr - 1);
    } else if (*round_digit_ptr == '5') {
      if (has_more_non_zero) {
        RoundUp(round_digit_ptr - 1);
      } else {
        RoundToEven(round_digit_ptr - 1);
      }
    }
    final_end = round_digit_ptr;
    if (final_start[-1] == '1') {
      --final_start;
      ++scientific_exp;
      --final_end;
    }
  } else {
    // Need to pad with zeros.
    trailing_zeros = state.precision - (digits_printed - 1);
  }

  if (state.precision > 0 || state.ShouldPrintDot()) {
    final_start[-1] = *final_start;
    *final_start = '.';
    --final_start;
  }

  // We need to add 2 to the buffer size for the +/- sign and the e
  constexpr size_t kExpBufferSize = numbers_internal::kFastToBufferSize + 2;
  char exp_buffer[kExpBufferSize];
  char* exp_ptr_start = exp_buffer;
  char* exp_ptr = exp_ptr_start;
  *exp_ptr++ = uppercase ? 'E' : 'e';
  if (scientific_exp >= 0) {
    *exp_ptr++ = '+';
  } else {
    *exp_ptr++ = '-';
    scientific_exp = -scientific_exp;
  }

  if (scientific_exp < 10) {
    *exp_ptr++ = '0';
  }
  exp_ptr = numbers_internal::FastIntToBuffer(scientific_exp, exp_ptr);
  FinalPrint(state,
             absl::string_view(final_start,
                               static_cast<size_t>(final_end - final_start)),
             0, trailing_zeros,
             absl::string_view(exp_ptr_start,
                               static_cast<size_t>(exp_ptr - exp_ptr_start)));
}

void FormatENegativeExpSlow(uint128 mantissa, int exp, bool uppercase,
                            const FormatState& state,
                            size_t digits_to_trim = 0) {
  assert(exp < 0);

  FractionalDigitGenerator::RunConversion(
      mantissa, -exp,
      [&](FractionalDigitGenerator digit_gen) {
        int first_digit = 0;
        size_t nines = 0;
        int num_leading_zeros = 0;
        while (digit_gen.HasMoreDigits()) {
          auto digits = digit_gen.GetDigits();
          if (digits.digit_before_nine != 0) {
            first_digit = digits.digit_before_nine;
            nines = digits.num_nines;
            break;
          } else if (digits.num_nines > 0) {
            // This also means the first digit is 0
            first_digit = 9;
            nines = digits.num_nines - 1;
            num_leading_zeros++;
            break;
          }
          num_leading_zeros++;
        }
        size_t precision = state.precision;
        if (precision > digits_to_trim) {
          precision -= digits_to_trim;
        } else {
          precision = 0;
        }
        bool change_to_zeros = false;
        if (nines >= precision || state.precision == 0) {
          bool round_up = false;
          if (nines == precision) {
            round_up = digit_gen.IsGreaterThanHalf();
          } else {
            round_up = nines > 0 || digit_gen.IsGreaterThanHalf();
          }
          if (round_up) {
            first_digit = (first_digit == 9 ? 1 : first_digit + 1);
            num_leading_zeros -= (first_digit == 1);
            change_to_zeros = true;
          }
        }
        int scientific_exp = -(num_leading_zeros + 1);
        assert(scientific_exp < 0);
        char exp_buffer[numbers_internal::kFastToBufferSize];
        char* exp_start = exp_buffer;
        *exp_start++ = '-';
        if (scientific_exp > -10) {
          *exp_start++ = '0';
        }
        scientific_exp *= -1;
        char* exp_end =
            numbers_internal::FastIntToBuffer(scientific_exp, exp_start);
        const size_t total_digits =
            1  // First digit
            +
            ((precision > 0 || state.conv.has_alt_flag()) ? 1
                                                          : 0)  // Decimal point
            + precision  // Digits after decimal
            + 1          // 'e' or 'E'
            + static_cast<size_t>(exp_end - exp_buffer);  // Exponent digits

        const auto padding = ExtraWidthToPadding(
            total_digits + (state.sign_char != '\0' ? 1 : 0), state);
        state.sink->Append(padding.left_spaces, ' ');

        if (state.sign_char != '\0') {
          state.sink->Append(1, state.sign_char);
        }

        state.sink->Append(1, static_cast<char>(first_digit + '0'));
        if (precision > 0 || state.conv.has_alt_flag()) {
          state.sink->Append(1, '.');
        }
        size_t digits_to_go = precision;
        size_t nines_to_print = std::min(nines, digits_to_go);
        state.sink->Append(nines_to_print, change_to_zeros ? '0' : '9');
        digits_to_go -= nines_to_print;
        while (digits_to_go > 0 && digit_gen.HasMoreDigits()) {
          auto digits = digit_gen.GetDigits();

          if (digits.num_nines + 1 < digits_to_go) {
            state.sink->Append(1, digits.digit_before_nine + '0');
            state.sink->Append(digits.num_nines, '9');
            digits_to_go -= digits.num_nines + 1;
          } else {
            bool round_up = false;
            if (digits.num_nines + 1 > digits_to_go) {
              round_up = true;
            } else if (digit_gen.IsGreaterThanHalf()) {
              round_up = true;
            } else if (digit_gen.IsExactlyHalf()) {
              round_up =
                  digits.num_nines != 0 || digits.digit_before_nine % 2 == 1;
            }
            if (round_up) {
              state.sink->Append(1, digits.digit_before_nine + '1');
              --digits_to_go;
            } else {
              state.sink->Append(1, digits.digit_before_nine + '0');
              state.sink->Append(digits_to_go - 1, '9');
              digits_to_go = 0;
            }
            break;
          }
        }
        state.sink->Append(digits_to_go, '0');
        state.sink->Append(1, uppercase ? 'E' : 'e');
        state.sink->Append(absl::string_view(
            exp_buffer, static_cast<size_t>(exp_end - exp_buffer)));
        state.sink->Append(padding.right_spaces, ' ');
      });
}

void FormatEPositiveExpSlow(uint128 mantissa, int exp, bool uppercase,
                            const FormatState& state,
                            size_t digits_to_trim = 0) {
  BinaryToDecimal::RunConversion(
      mantissa, exp, [&](BinaryToDecimal btd) {
        int scientific_exp = static_cast<int>(btd.TotalDigits() - 1);
        absl::string_view digits_view = btd.CurrentDigits();

        size_t digits_to_go = state.precision + 1;
        auto [first_digit_opt, nines] = GetDigits(btd, digits_view);
        if (!first_digit_opt.has_value() && nines == 0) {
          return;
        }

        int first_digit = first_digit_opt.value_or(9);
        if (!first_digit_opt) {
          --nines;
        }

        // At this point we are guaranteed to have some sort of first digit
        bool change_to_zeros = false;
        if (nines + 1 >= digits_to_go) {
          // Everything we need to print is in the first DigitRun
          auto next_digit_opt = GetDigits(btd, digits_view).digit;
          if (nines == state.precision) {
            change_to_zeros = next_digit_opt.value_or(0) > 4;
          } else {
            change_to_zeros = true;
          }
          if (change_to_zeros) {
            if (first_digit != 9) {
              first_digit = first_digit + 1;
            } else {
              first_digit = 1;
              ++scientific_exp;
            }
          }
        }

        char exp_buffer[numbers_internal::kFastToBufferSize];
        char* exp_buffer_end =
            numbers_internal::FastIntToBuffer(scientific_exp, exp_buffer);
        const bool print_dot =
            (state.precision > digits_to_trim) || state.conv.has_alt_flag();
        const size_t exp_size =
            static_cast<size_t>(exp_buffer_end - exp_buffer) + 2 +
            (scientific_exp < 10 ? 1 : 0);
        const size_t total_digits_out = 1 + (print_dot ? 1 : 0) +
                                        (state.precision - digits_to_trim) +
                                        exp_size;

        const auto padding = ExtraWidthToPadding(
            total_digits_out + (state.sign_char != '\0' ? 1 : 0), state);

        state.sink->Append(padding.left_spaces, ' ');
        if (state.sign_char != '\0') {
          state.sink->Append(1, state.sign_char);
        }
        state.sink->Append(1, static_cast<char>(first_digit + '0'));
        --digits_to_go;
        if (print_dot) {
          state.sink->Append(1, '.');
        }

        size_t remaining_to_print = state.precision - digits_to_trim;
        auto append_with_trim = [&](size_t count, char c) {
          size_t to_append = std::min(count, remaining_to_print);
          if (to_append > 0) {
            state.sink->Append(to_append, c);
            remaining_to_print -= to_append;
          }
        };

        size_t nines_to_append = std::min(digits_to_go, nines);
        append_with_trim(nines_to_append, change_to_zeros ? '0' : '9');
        digits_to_go -= nines_to_append;

        while (digits_to_go > 0) {
          auto [digit_opt, curr_nines] = GetDigits(btd, digits_view);
          if (!digit_opt.has_value()) break;
          int digit = *digit_opt;
          if (curr_nines + 1 < digits_to_go) {
            append_with_trim(1, static_cast<char>(digit + '0'));
            append_with_trim(curr_nines, '9');
            digits_to_go -= curr_nines + 1;
          } else {
            bool need_round_up = false;
            auto next_digit_opt = GetDigits(btd, digits_view).digit;
            if (digits_to_go == 1) {
              need_round_up = curr_nines > 0 || next_digit_opt > 4;
            } else if (digits_to_go == curr_nines + 1) {
              // Only round if next digit is > 4
              need_round_up = next_digit_opt.value_or(0) > 4;
            } else {
              // we know we need to round since nine is after precision ends
              need_round_up = true;
            }
            append_with_trim(1, static_cast<char>(digit + need_round_up + '0'));
            append_with_trim(digits_to_go - 1, need_round_up ? '0' : '9');
            digits_to_go = 0;
          }
        }

        if (digits_to_go > 0) {
          append_with_trim(digits_to_go, '0');
        }

        state.sink->Append(1, uppercase ? 'E' : 'e');
        state.sink->Append(1, scientific_exp >= 0 ? '+' : '-');
        if (scientific_exp < 10) {
          state.sink->Append(1, '0');
        }
        state.sink->Append(absl::string_view(
            exp_buffer, static_cast<size_t>(exp_buffer_end - exp_buffer)));
        state.sink->Append(padding.right_spaces, ' ');
      });
}

//
template <typename Int>
void FormatGFast(Int v, int exp, bool uppercase, const FormatState& state) {
  if (!v) {
    absl::string_view mantissa_str =
        state.ShouldPrintDot() && state.conv.has_alt_flag() ? "0." : "0";
    FinalPrint(state, mantissa_str, 0,
               state.conv.has_alt_flag() * state.precision, "");
    return;
  }
  constexpr int kInputBits = sizeof(Int) * 8;
  constexpr int kMaxFractionalDigits = 128;
  // We need enough headroom to the left of our starting pointer to support
  // a potential prefix shift for values between 1e-1 and 1e-4.
  // The prefix "0.000" is 5 chars, plus potential rounding carry (1 char).
  constexpr int kHeadroom = 32;
  constexpr int kBufferSize = kHeadroom +           // headroom + rounding + '.'
                              kMaxFixedPrecision +  // Integral
                              kMaxFractionalDigits;  // Fractional
  const int total_bits = kInputBits - LeadingZeros(v) + exp;
  char buffer[kBufferSize];
  char* integral_start = buffer + kHeadroom;
  char* integral_end = buffer + kHeadroom + kMaxFixedPrecision;
  char* final_start;
  char* final_end;
  bool zero_integral = false;
  int scientific_exp = 0;
  size_t digits_printed = 0;
  size_t trailing_zeros = 0;
  bool has_more_non_zero = false;

  auto check_integral_zeros = [](char* const begin, char* const end,
                                 const size_t precision,
                                 size_t digits_processed) -> bool {
    // When considering rounding to even, we care about the digits after the
    // round digit which means the total digits to move from the start is
    // precision + 2 since the first digit we print before the decimal point
    // is not a part of precision.
    size_t digit_upper_bound = precision + 2;
    if (digits_processed > digit_upper_bound) {
      return std::any_of(begin + digit_upper_bound, end,
                         [](char c) { return c != '0'; });
    }
    return false;
  };

  if (exp >= 0) {
    integral_end = total_bits <= 64
                       ? numbers_internal::FastIntToBuffer(
                             static_cast<uint64_t>(v) << exp, integral_start)
                       : numbers_internal::FastIntToBuffer(
                             static_cast<uint128>(v) << exp, integral_start);
    *integral_end = '0';
    final_start = integral_start;
    // Integral is guaranteed to be non-zero at this point.
    scientific_exp = static_cast<int>(integral_end - integral_start) - 1;
    digits_printed = static_cast<size_t>(integral_end - integral_start);
    final_end = integral_end;
    has_more_non_zero = check_integral_zeros(integral_start, integral_end,
                                             state.precision, digits_printed);
  } else {
    exp = -exp;
    if (exp < kInputBits) {
      integral_end =
          numbers_internal::FastIntToBuffer(v >> exp, integral_start);
    }
    *integral_end = '0';
    // We didn't move integral_start and it gets set to 0 in
    zero_integral = exp >= kInputBits || v >> exp == 0;
    if (!zero_integral) {
      digits_printed = static_cast<size_t>(integral_end - integral_start);
      has_more_non_zero = check_integral_zeros(integral_start, integral_end,
                                               state.precision, digits_printed);
      final_end = integral_end;
    }
    // Print fractional digits
    char* fractional_start = integral_end;

    size_t digits_to_print = (state.precision + 1) >= digits_printed
                                 ? state.precision + 1 - digits_printed
                                 : 0;
    bool print_extra = digits_printed <= state.precision + 1;
    auto [fractional_end, skipped_zeros, has_nonzero_rem] =
        exp <= 64 ? PrintFractionalDigitsScientific(
                        v, fractional_start, exp, digits_to_print + print_extra,
                        zero_integral)
                  : PrintFractionalDigitsScientific(
                        static_cast<uint128>(v), fractional_start, exp,
                        digits_to_print + print_extra, zero_integral);
    final_end = fractional_end;
    *fractional_end = '0';
    has_more_non_zero |= has_nonzero_rem;
    digits_printed += static_cast<size_t>(fractional_end - fractional_start);
    if (zero_integral) {
      scientific_exp = -1 * static_cast<int>(skipped_zeros + 1);
    } else {
      scientific_exp = static_cast<int>(integral_end - integral_start) - 1;
    }
    // Don't do any rounding here, we will do it ourselves.
    final_start = zero_integral ? fractional_start : integral_start;
  }

  // For rounding
  if (digits_printed >= state.precision + 1) {
    final_start[-1] = '0';
    char* round_digit_ptr = final_start + 1 + state.precision;
    if (*round_digit_ptr > '5') {
      RoundUp(round_digit_ptr - 1);
    } else if (*round_digit_ptr == '5') {
      if (has_more_non_zero) {
        RoundUp(round_digit_ptr - 1);
      } else {
        RoundToEven(round_digit_ptr - 1);
      }
    }
    final_end = round_digit_ptr;
    if (final_start[-1] == '1') {
      --final_start;
      ++scientific_exp;
      --final_end;
    }
  } else {
    // Need to pad with zeros.
    trailing_zeros = state.precision - (digits_printed - 1);
  }

  if (state.precision > 0 || state.ShouldPrintDot()) {
    final_start[-1] = *final_start;
    *final_start = '.';
    --final_start;
  }
  // We have scientific exp at this point
  if ((scientific_exp < 0 ||
       state.precision + 1 > static_cast<size_t>(scientific_exp)) &&
      scientific_exp >= -4) {
    if (scientific_exp < 0) {
      // Have 1.23456, needs 0.00123456
      // Move the first digit
      final_start[1] = *final_start;
      if (!state.ShouldPrintDot()) {
        ++final_end;
      }
      // Add some zeros
      for (; scientific_exp < -1; ++scientific_exp) {
        *final_start = '0';
        --final_start;
      }
      *final_start-- = '.';
      *final_start = '0';
    } else if (scientific_exp > 0) {
      // Have 1.23456, needs 1234.56
      // Move the '.' scientific_exp positions to the right.
      std::rotate(final_start + 1, final_start + 2,
                  final_start + scientific_exp + 2);
    }
    scientific_exp = 0;
  }
  auto const& conv = state.conv;
  if (!conv.has_alt_flag()) {
    trailing_zeros = 0;
    while (final_end[-1] == '0') {
      --final_end;
    }
    if (final_end[-1] == '.') --final_end;
  }
  if (scientific_exp) {
    // We need to add 2 to the buffer size for the +/- sign and the e
    constexpr size_t kExpBufferSize = numbers_internal::kFastToBufferSize + 2;
    char exp_buffer[kExpBufferSize];
    char* exp_ptr_start = exp_buffer;
    char* exp_ptr = exp_ptr_start;
    *exp_ptr++ = uppercase ? 'E' : 'e';
    if (scientific_exp >= 0) {
      *exp_ptr++ = '+';
    } else {
      *exp_ptr++ = '-';
      scientific_exp = -scientific_exp;
    }

    if (scientific_exp < 10) {
      *exp_ptr++ = '0';
    }
    exp_ptr = numbers_internal::FastIntToBuffer(scientific_exp, exp_ptr);
    FinalPrint(state,
               absl::string_view(
                   final_start, static_cast<size_t>((final_end - final_start))),
               0, trailing_zeros,
               absl::string_view(exp_ptr_start,
                                 static_cast<size_t>(exp_ptr - exp_ptr_start)));
  } else {
    FinalPrint(state,
               absl::string_view(
                   final_start, static_cast<size_t>((final_end - final_start))),
               0, trailing_zeros, "");
  }
}

template <typename Int>
void FormatGNegativeExpSlow(Int mantissa, int exp, bool uppercase,
                            const FormatState& state) {
  // Most of the code here is to decide whether to use E-style or F-style
  // formatting, with the actual formatting done in FormatENegativeExpSlow and
  // FormatFNegativeExpSlow.
  FractionalDigitGenerator::RunConversion(
      mantissa, -exp, [&](FractionalDigitGenerator digit_gen) {
        int first_digit = 0;
        size_t nines = 0;
        int num_leading_zeros = 0;
        size_t num_trailing_zeros = 0;
        while (digit_gen.HasMoreDigits()) {
          auto digits = digit_gen.GetDigits();
          if (digits.digit_before_nine != 0) {
            first_digit = digits.digit_before_nine;
            nines = digits.num_nines;
            break;
          } else if (digits.num_nines > 0) {
            // This also means the first digit is 0
            first_digit = 9;
            nines = digits.num_nines - 1;
            num_leading_zeros++;
            break;
          }
          num_leading_zeros++;
        }
        if (nines >= state.precision || state.precision == 0) {
          bool round_up = false;
          if (nines == state.precision) {
            round_up = digit_gen.IsGreaterThanHalf();
          } else {
            round_up = nines > 0 || digit_gen.IsGreaterThanHalf();
          }
          if (round_up) {
            first_digit = (first_digit == 9 ? 1 : first_digit + 1);
            num_leading_zeros -= (first_digit == 1);
            num_trailing_zeros = state.precision;
          }
        }
        int scientific_exp = -(num_leading_zeros + 1);
        assert(scientific_exp < 0);
        size_t digits_to_go = state.precision + 1;
        if (state.conv.has_alt_flag()) {
          num_trailing_zeros = 0;
        }
        if (!state.conv.has_alt_flag() && !num_trailing_zeros) {
          num_trailing_zeros = (first_digit == 0);
          digits_to_go -= std::min(digits_to_go, nines + 1);
          while (digits_to_go > 0 && digit_gen.HasMoreDigits()) {
            auto digits = digit_gen.GetDigits();
            if (digits.num_nines + 1 < digits_to_go) {
              if (digits.digit_before_nine == 0 && digits.num_nines == 0) {
                ++num_trailing_zeros;
              } else {
                num_trailing_zeros = 0;
              }
              digits_to_go -= digits.num_nines + 1;
            } else {
              bool round_up = false;
              if (digits.num_nines + 1 > digits_to_go) {
                round_up = true;
              } else if (digit_gen.IsGreaterThanHalf()) {
                round_up = true;
              } else if (digit_gen.IsExactlyHalf()) {
                round_up =
                    digits.num_nines != 0 || digits.digit_before_nine % 2 == 1;
              }

              if (digits_to_go == 1) {
                if (digits.digit_before_nine + (round_up ? 1 : 0) == 0) {
                  ++num_trailing_zeros;
                } else {
                  num_trailing_zeros = 0;
                }
              } else {
                num_trailing_zeros = round_up ? digits_to_go - 1 : 0;
              }
              digits_to_go = 0;
            }
          }
        }
        if (!num_trailing_zeros) {
          num_trailing_zeros = !state.conv.has_alt_flag() * digits_to_go;
        }
        if (scientific_exp <= -4) {
          FormatENegativeExpSlow(static_cast<uint128>(mantissa), exp, uppercase,
                                 state, num_trailing_zeros);
        } else {
          FormatState f_state = state;
          f_state.precision = static_cast<size_t>(
              static_cast<int>(state.precision) - scientific_exp);
          FormatFNegativeExpSlow(static_cast<uint128>(mantissa), -exp, f_state,
                                 num_trailing_zeros);
        }
      });
}
template <typename Int>
void FormatGPositiveExpSlow(Int mantissa, int exp, bool uppercase,
                            const FormatState& state) {
  BinaryToDecimal::RunConversion(mantissa, exp, [&](BinaryToDecimal btd) {
    int scientific_exp = static_cast<int>(btd.TotalDigits()) - 1;
    absl::string_view digits = btd.CurrentDigits();
    size_t digits_to_go = state.precision + 1;
    auto [first_digit_opt, nines] = GetDigits(btd, digits);
    int first_digit = first_digit_opt.value_or(9);
    if (!first_digit_opt) {
      --nines;
    }
    // At this point we are guaranteed to have some sort of first digit
    bool change_to_zeros = false;
    size_t num_trailing_zeros = 0;
    if (nines + 1 >= digits_to_go) {
      // Everything we need to print is in the first DigitRun
      auto next_digit_opt = GetDigits(btd, digits).digit;
      if (nines == state.precision) {
        change_to_zeros = next_digit_opt.value_or(0) > 4;
      } else {
        change_to_zeros = true;
      }
      if (change_to_zeros) {
        if (first_digit != 9) {
          first_digit = first_digit + 1;
        } else {
          first_digit = 1;
          ++scientific_exp;
        }
        num_trailing_zeros = state.precision;
      }
    }
    if (state.conv.has_alt_flag()) {
      num_trailing_zeros = 0;
    }
    // At this point the number of trailing zeros is not covered by the first
    // DigitRun
    if (!state.conv.has_alt_flag() && !num_trailing_zeros) {
      num_trailing_zeros = first_digit == 0;
      digits_to_go -= std::min(digits_to_go, nines + 1);
      while (digits_to_go > 0) {
        auto [digit_opt, curr_nines] = GetDigits(btd, digits);
        if (!digit_opt.has_value()) {
          break;
        }
        if (curr_nines + 1 < digits_to_go) {
          int digit = *digit_opt;
          // If the previous one was a 0 we are too
          if (digit == 0 && curr_nines == 0) {
            ++num_trailing_zeros;
            --digits_to_go;
          } else {
            num_trailing_zeros = 0;
            --digits_to_go;
            digits_to_go -= std::min(digits_to_go, curr_nines);
          }
        } else {
          auto next_digit_opt = GetDigits(btd, digits).digit;
          if (digits_to_go == 1) {
            if (*digit_opt == 0) {
              if (curr_nines || next_digit_opt > 4) {
                num_trailing_zeros = 0;
              } else {
                ++num_trailing_zeros;
              }
            } else {
              num_trailing_zeros = 0;
            }
          } else if (digits_to_go == curr_nines + 1) {
            num_trailing_zeros = next_digit_opt > 4 ? digits_to_go - 1 : 0;
          } else {
            num_trailing_zeros = digits_to_go - 1;
          }
          digits_to_go = 0;
        }
      }
    }
    assert(scientific_exp >= 0);
    // By this point the exponent is accurate
    if (static_cast<size_t>(scientific_exp) > state.precision) {
      FormatEPositiveExpSlow(mantissa, exp, uppercase, state,
                             num_trailing_zeros);
    } else {
      FormatFPositiveExpSlow(mantissa, exp, state, !state.conv.has_alt_flag());
    }
  });
}

template <typename Float>
bool FloatToSink(const Float v, const FormatConversionSpecImpl &conv,
                 FormatSinkImpl *sink) {
  // Print the sign or the sign column.
  Float abs_v = v;
  char sign_char = 0;
  if (std::signbit(abs_v)) {
    sign_char = '-';
    abs_v = -abs_v;
  } else if (conv.has_show_pos_flag()) {
    sign_char = '+';
  } else if (conv.has_sign_col_flag()) {
    sign_char = ' ';
  }

  // Print nan/inf.
  if (ConvertNonNumericFloats(sign_char, abs_v, conv, sink)) {
    return true;
  }

  size_t precision =
      conv.precision() < 0 ? 6 : static_cast<size_t>(conv.precision());

  auto decomposed = Decompose(abs_v);

  FormatConversionChar c = conv.conversion_char();

  if (c == FormatConversionCharInternal::f ||
      c == FormatConversionCharInternal::F) {
    FormatF(decomposed.mantissa, decomposed.exponent,
            {sign_char, precision, conv, sink});
    return true;
  } else if (c == FormatConversionCharInternal::e ||
             c == FormatConversionCharInternal::E) {
    FormatE(decomposed.mantissa, decomposed.exponent,
            FormatConversionCharIsUpper(conv.conversion_char()),
            {sign_char, precision, conv, sink});
    return true;
  } else if (c == FormatConversionCharInternal::g ||
             c == FormatConversionCharInternal::G) {
    precision = std::max(precision, size_t{1}) - 1;
    constexpr int input_bits = sizeof(decomposed.mantissa) * 8;
    const int total_bits =
        input_bits - LeadingZeros(decomposed.mantissa) + decomposed.exponent;
    if (decomposed.exponent >= 0 && total_bits > 128) {
      FormatGPositiveExpSlow(
          decomposed.mantissa, decomposed.exponent,
          FormatConversionCharIsUpper(conv.conversion_char()),
          {sign_char, precision, conv, sink});
      return true;
    } else if (decomposed.exponent < -128) {
      FormatGNegativeExpSlow(
          decomposed.mantissa, decomposed.exponent,
          FormatConversionCharIsUpper(conv.conversion_char()),
          {sign_char, precision, conv, sink});
      return true;
    }
    FormatGFast(decomposed.mantissa, decomposed.exponent,
                FormatConversionCharIsUpper(conv.conversion_char()),
                {sign_char, precision, conv, sink});
    return true;
  } else if (c == FormatConversionCharInternal::a ||
             c == FormatConversionCharInternal::A) {
    bool uppercase = (c == FormatConversionCharInternal::A);
    FormatA(HexFloatTypeParams(Float{}), decomposed.mantissa,
            decomposed.exponent, uppercase, {sign_char, precision, conv, sink});
    return true;
  } else {
    return false;
  }
}

}  // namespace

bool ConvertFloatImpl(long double v, const FormatConversionSpecImpl &conv,
                      FormatSinkImpl *sink) { __builtin_trap() /* STUB: not implemented */; }

bool ConvertFloatImpl(float v, const FormatConversionSpecImpl &conv,
                      FormatSinkImpl *sink) { __builtin_trap() /* STUB: not implemented */; }

bool ConvertFloatImpl(double v, const FormatConversionSpecImpl &conv,
                      FormatSinkImpl *sink) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace str_format_internal
ABSL_NAMESPACE_END
}  // namespace absl
