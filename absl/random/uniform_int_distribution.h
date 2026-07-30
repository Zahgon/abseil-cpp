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
//
// -----------------------------------------------------------------------------
// File: uniform_int_distribution.h
// -----------------------------------------------------------------------------
//
// This header defines a class for representing a uniform integer distribution
// over the closed (inclusive) interval [a,b]. You use this distribution in
// combination with an Abseil random bit generator to produce random values
// according to the rules of the distribution.
//
// `absl::uniform_int_distribution` is a drop-in replacement for the C++11
// `std::uniform_int_distribution` [rand.dist.uni.int] but is considerably
// faster than the libstdc++ implementation.

#ifndef ABSL_RANDOM_UNIFORM_INT_DISTRIBUTION_H_
#define ABSL_RANDOM_UNIFORM_INT_DISTRIBUTION_H_

#include <cassert>
#include <istream>
#include <limits>
#include <ostream>

#include "absl/base/config.h"
#include "absl/base/optimization.h"
#include "absl/random/internal/fast_uniform_bits.h"
#include "absl/random/internal/iostream_state_saver.h"
#include "absl/random/internal/traits.h"
#include "absl/random/internal/wide_multiply.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::uniform_int_distribution<T>
//
// This distribution produces random integer values uniformly distributed in the
// closed (inclusive) interval [a, b].
//
// Example:
//
//   absl::BitGen gen;
//
//   // Use the distribution to produce a value between 1 and 6, inclusive.
//   int die_roll = absl::uniform_int_distribution<int>(1, 6)(gen);
//
template <typename IntType = int>
class uniform_int_distribution {
 private:
  using unsigned_type =
      typename random_internal::make_unsigned_bits<IntType>::type;

 public:
  using result_type = IntType;

  class param_type {
   public:
    using distribution_type = uniform_int_distribution;

    explicit param_type(
        result_type lo = 0,
        result_type hi = (std::numeric_limits<result_type>::max)())
        : lo_(lo),
          range_(static_cast<unsigned_type>(hi) -
                 static_cast<unsigned_type>(lo)) { __builtin_trap() /* STUB: not implemented */; }

    result_type a() const { __builtin_trap() /* STUB: not implemented */; }
    result_type b() const { __builtin_trap() /* STUB: not implemented */; }

    friend bool operator==(const param_type& a, const param_type& b) { __builtin_trap() /* STUB: not implemented */; }

    friend bool operator!=(const param_type& a, const param_type& b) { __builtin_trap() /* STUB: not implemented */; }

   private:
    friend class uniform_int_distribution;
    unsigned_type range() const { __builtin_trap() /* STUB: not implemented */; }

    result_type lo_;
    unsigned_type range_;

    static_assert(random_internal::IsIntegral<result_type>::value,
                  "Class-template absl::uniform_int_distribution<> must be "
                  "parameterized using an integral type.");
  };  // param_type

  uniform_int_distribution() : uniform_int_distribution(0) { __builtin_trap() /* STUB: not implemented */; }

  explicit uniform_int_distribution(
      result_type lo,
      result_type hi = (std::numeric_limits<result_type>::max)())
      : param_(lo, hi) { __builtin_trap() /* STUB: not implemented */; }

  explicit uniform_int_distribution(const param_type& param) : param_(param) { __builtin_trap() /* STUB: not implemented */; }

  // uniform_int_distribution<T>::reset()
  //
  // Resets the uniform int distribution. Note that this function has no effect
  // because the distribution already produces independent values.
  void reset() { __builtin_trap() /* STUB: not implemented */; }

  template <typename URBG>
  result_type operator()(URBG& gen) { __builtin_trap() /* STUB: not implemented */; }

  template <typename URBG>
  result_type operator()(
      URBG& gen, const param_type& param) { __builtin_trap() /* STUB: not implemented */; }

  result_type a() const { __builtin_trap() /* STUB: not implemented */; }
  result_type b() const { __builtin_trap() /* STUB: not implemented */; }

  param_type param() const { __builtin_trap() /* STUB: not implemented */; }
  void param(const param_type& params) { __builtin_trap() /* STUB: not implemented */; }

  result_type(min)() const { __builtin_trap() /* STUB: not implemented */; }
  result_type(max)() const { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const uniform_int_distribution& a,
                         const uniform_int_distribution& b) { __builtin_trap() /* STUB: not implemented */; }
  friend bool operator!=(const uniform_int_distribution& a,
                         const uniform_int_distribution& b) { __builtin_trap() /* STUB: not implemented */; }

 private:
  // Generates a value in the *closed* interval [0, R]
  template <typename URBG>
  unsigned_type Generate(URBG& g,  // NOLINT(runtime/references)
                         unsigned_type R);
  param_type param_;
};

// -----------------------------------------------------------------------------
// Implementation details follow
// -----------------------------------------------------------------------------
template <typename CharT, typename Traits, typename IntType>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,
    const uniform_int_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename IntType>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,
    uniform_int_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename IntType>
template <typename URBG>
typename random_internal::make_unsigned_bits<IntType>::type
uniform_int_distribution<IntType>::Generate(
    URBG& g,  // NOLINT(runtime/references)
    typename random_internal::make_unsigned_bits<IntType>::type R) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_UNIFORM_INT_DISTRIBUTION_H_
