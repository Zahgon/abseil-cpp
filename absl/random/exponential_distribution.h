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

#ifndef ABSL_RANDOM_EXPONENTIAL_DISTRIBUTION_H_
#define ABSL_RANDOM_EXPONENTIAL_DISTRIBUTION_H_

#include <cassert>
#include <cmath>
#include <istream>
#include <limits>
#include <type_traits>

#include "absl/base/config.h"
#include "absl/meta/type_traits.h"
#include "absl/random/internal/fast_uniform_bits.h"
#include "absl/random/internal/generate_real.h"
#include "absl/random/internal/iostream_state_saver.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::exponential_distribution:
// Generates a number conforming to an exponential distribution and is
// equivalent to the standard [rand.dist.pois.exp] distribution.
template <typename RealType = double>
class exponential_distribution {
 public:
  using result_type = RealType;

  class param_type {
   public:
    using distribution_type = exponential_distribution;

    explicit param_type(result_type lambda = 1) : lambda_(lambda) {
      assert(lambda > 0);
      neg_inv_lambda_ = -result_type(1) / lambda_;
    }

    result_type lambda() const { return lambda_; }

    friend bool operator==(const param_type& a, const param_type& b) {
      return a.lambda_ == b.lambda_;
    }

    friend bool operator!=(const param_type& a, const param_type& b) {
      return !(a == b);
    }

   private:
    friend class exponential_distribution;

    result_type lambda_;
    result_type neg_inv_lambda_;

    static_assert(
        std::is_floating_point_v<RealType>,
        "Class-template absl::exponential_distribution<> must be parameterized "
        "using a floating-point type.");
  };

  exponential_distribution() : exponential_distribution(1) { __builtin_trap() /* STUB: not implemented */; }

  explicit exponential_distribution(result_type lambda) : param_(lambda) { __builtin_trap() /* STUB: not implemented */; }

  explicit exponential_distribution(const param_type& p) : param_(p) { __builtin_trap() /* STUB: not implemented */; }

  void reset() { __builtin_trap() /* STUB: not implemented */; }

  // Generating functions
  template <typename URBG>
  result_type operator()(URBG& g) { __builtin_trap() /* STUB: not implemented */; }

  template <typename URBG>
  result_type operator()(URBG& g,  // NOLINT(runtime/references)
                         const param_type& p);

  param_type param() const { __builtin_trap() /* STUB: not implemented */; }
  void param(const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

  result_type(min)() const { __builtin_trap() /* STUB: not implemented */; }
  result_type(max)() const { __builtin_trap() /* STUB: not implemented */; }

  result_type lambda() const { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const exponential_distribution& a,
                         const exponential_distribution& b) { __builtin_trap() /* STUB: not implemented */; }
  friend bool operator!=(const exponential_distribution& a,
                         const exponential_distribution& b) { __builtin_trap() /* STUB: not implemented */; }

 private:
  param_type param_;
  random_internal::FastUniformBits<uint64_t> fast_u64_;
};

// --------------------------------------------------------------------------
// Implementation details follow
// --------------------------------------------------------------------------

template <typename RealType>
template <typename URBG>
typename exponential_distribution<RealType>::result_type
exponential_distribution<RealType>::operator()(
    URBG& g,  // NOLINT(runtime/references)
    const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename RealType>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,  // NOLINT(runtime/references)
    const exponential_distribution<RealType>& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename RealType>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,    // NOLINT(runtime/references)
    exponential_distribution<RealType>& x) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_EXPONENTIAL_DISTRIBUTION_H_
