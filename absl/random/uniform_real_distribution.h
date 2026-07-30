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
// File: uniform_real_distribution.h
// -----------------------------------------------------------------------------
//
// This header defines a class for representing a uniform floating-point
// distribution over a half-open interval [a,b). You use this distribution in
// combination with an Abseil random bit generator to produce random values
// according to the rules of the distribution.
//
// `absl::uniform_real_distribution` is a drop-in replacement for the C++11
// `std::uniform_real_distribution` [rand.dist.uni.real] but is considerably
// faster than the libstdc++ implementation.
//
// Note: the standard-library version may occasionally return `1.0` when
// default-initialized. See https://bugs.llvm.org//show_bug.cgi?id=18767
// `absl::uniform_real_distribution` does not exhibit this behavior.

#ifndef ABSL_RANDOM_UNIFORM_REAL_DISTRIBUTION_H_
#define ABSL_RANDOM_UNIFORM_REAL_DISTRIBUTION_H_

#include <cassert>
#include <cmath>
#include <cstdint>
#include <istream>
#include <limits>
#include <ostream>
#include <type_traits>

#include "absl/base/config.h"
#include "absl/meta/type_traits.h"
#include "absl/random/internal/fast_uniform_bits.h"
#include "absl/random/internal/generate_real.h"
#include "absl/random/internal/iostream_state_saver.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::uniform_real_distribution<T>
//
// This distribution produces random floating-point values uniformly distributed
// over the half-open interval [a, b).
//
// Example:
//
//   absl::BitGen gen;
//
//   // Use the distribution to produce a value between 0.0 (inclusive)
//   // and 1.0 (exclusive).
//   double value = absl::uniform_real_distribution<double>(0, 1)(gen);
//
template <typename RealType = double>
class uniform_real_distribution {
 public:
  using result_type = RealType;

  class param_type {
   public:
    using distribution_type = uniform_real_distribution;

    explicit param_type(result_type lo = 0, result_type hi = 1)
        : lo_(lo), hi_(hi), range_(hi - lo) {
      // [rand.dist.uni.real] preconditions 2 & 3
      assert(lo <= hi);

      // NOTE: For integral types, we can promote the range to an unsigned type,
      // which gives full width of the range. However for real (fp) types, this
      // is not possible, so value generation cannot use the full range of the
      // real type.
      assert(range_ <= (std::numeric_limits<result_type>::max)());
    }

    result_type a() const { return lo_; }
    result_type b() const { return hi_; }

    friend bool operator==(const param_type& a, const param_type& b) {
      return a.lo_ == b.lo_ && a.hi_ == b.hi_;
    }

    friend bool operator!=(const param_type& a, const param_type& b) {
      return !(a == b);
    }

   private:
    friend class uniform_real_distribution;
    result_type lo_, hi_, range_;

    static_assert(std::is_floating_point_v<RealType>,
                  "Class-template absl::uniform_real_distribution<> must be "
                  "parameterized using a floating-point type.");
  };

  uniform_real_distribution() : uniform_real_distribution(0) {}

  explicit uniform_real_distribution(result_type lo, result_type hi = 1)
      : param_(lo, hi) {}

  explicit uniform_real_distribution(const param_type& param) : param_(param) {}

  // uniform_real_distribution<T>::reset()
  //
  // Resets the uniform real distribution. Note that this function has no effect
  // because the distribution already produces independent values.
  void reset() {}

  template <typename URBG>
  result_type operator()(URBG& gen) { __builtin_trap() /* STUB: not implemented */; }

  template <typename URBG>
  result_type operator()(URBG& gen,  // NOLINT(runtime/references)
                         const param_type& p);

  result_type a() const { __builtin_trap() /* STUB: not implemented */; }
  result_type b() const { __builtin_trap() /* STUB: not implemented */; }

  param_type param() const { __builtin_trap() /* STUB: not implemented */; }
  void param(const param_type& params) { __builtin_trap() /* STUB: not implemented */; }

  result_type(min)() const { __builtin_trap() /* STUB: not implemented */; }
  result_type(max)() const { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const uniform_real_distribution& a,
                         const uniform_real_distribution& b) { __builtin_trap() /* STUB: not implemented */; }
  friend bool operator!=(const uniform_real_distribution& a,
                         const uniform_real_distribution& b) { __builtin_trap() /* STUB: not implemented */; }

 private:
  param_type param_;
  random_internal::FastUniformBits<uint64_t> fast_u64_;
};

// -----------------------------------------------------------------------------
// Implementation details follow
// -----------------------------------------------------------------------------
template <typename RealType>
template <typename URBG>
typename uniform_real_distribution<RealType>::result_type
uniform_real_distribution<RealType>::operator()(
    URBG& gen, const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename RealType>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,  // NOLINT(runtime/references)
    const uniform_real_distribution<RealType>& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename RealType>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,     // NOLINT(runtime/references)
    uniform_real_distribution<RealType>& x) { __builtin_trap() /* STUB: not implemented */; }
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_UNIFORM_REAL_DISTRIBUTION_H_
