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

#ifndef ABSL_RANDOM_POISSON_DISTRIBUTION_H_
#define ABSL_RANDOM_POISSON_DISTRIBUTION_H_

#include <cassert>
#include <cmath>
#include <cstdint>
#include <istream>
#include <limits>
#include <ostream>

#include "absl/base/config.h"
#include "absl/random/internal/fast_uniform_bits.h"
#include "absl/random/internal/fastmath.h"
#include "absl/random/internal/generate_real.h"
#include "absl/random/internal/iostream_state_saver.h"
#include "absl/random/internal/traits.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::poisson_distribution:
// Generates discrete variates conforming to a Poisson distribution.
//   p(n) = (mean^n / n!) exp(-mean)
//
// Depending on the parameter, the distribution selects one of the following
// algorithms:
// * The standard algorithm, attributed to Knuth, extended using a split method
// for larger values
// * The "Ratio of Uniforms as a convenient method for sampling from classical
// discrete distributions", Stadlober, 1989.
// http://www.sciencedirect.com/science/article/pii/0377042790903495
//
// NOTE: param_type.mean() is a double, which permits values larger than
// poisson_distribution<IntType>::max(), however this should be avoided and
// the distribution results are limited to the max() value.
//
// The goals of this implementation are to provide good performance while still
// being thread-safe: This limits the implementation to not using lgamma
// provided by <math.h>.
//
template <typename IntType = int>
class poisson_distribution {
 public:
  using result_type = IntType;

  class param_type {
   public:
    using distribution_type = poisson_distribution;
    explicit param_type(double mean = 1.0);

    double mean() const { return mean_; }

    friend bool operator==(const param_type& a, const param_type& b) {
      return a.mean_ == b.mean_;
    }

    friend bool operator!=(const param_type& a, const param_type& b) {
      return !(a == b);
    }

   private:
    friend class poisson_distribution;

    double mean_;
    double emu_;  // e ^ -mean_
    double lmu_;  // ln(mean_)
    double s_;
    double log_k_;
    int split_;

    static_assert(random_internal::IsIntegral<IntType>::value,
                  "Class-template absl::poisson_distribution<> must be "
                  "parameterized using an integral type.");
  };

  poisson_distribution() : poisson_distribution(1.0) { __builtin_trap() /* STUB: not implemented */; }

  explicit poisson_distribution(double mean) : param_(mean) { __builtin_trap() /* STUB: not implemented */; }

  explicit poisson_distribution(const param_type& p) : param_(p) { __builtin_trap() /* STUB: not implemented */; }

  void reset() { __builtin_trap() /* STUB: not implemented */; }

  // generating functions
  template <typename URBG>
  result_type operator()(URBG& g) { __builtin_trap() /* STUB: not implemented */; }

  template <typename URBG>
  result_type operator()(URBG& g,  // NOLINT(runtime/references)
                         const param_type& p);

  param_type param() const { __builtin_trap() /* STUB: not implemented */; }
  void param(const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

  result_type(min)() const { __builtin_trap() /* STUB: not implemented */; }
  result_type(max)() const { __builtin_trap() /* STUB: not implemented */; }

  double mean() const { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const poisson_distribution& a,
                         const poisson_distribution& b) { __builtin_trap() /* STUB: not implemented */; }
  friend bool operator!=(const poisson_distribution& a,
                         const poisson_distribution& b) { __builtin_trap() /* STUB: not implemented */; }

 private:
  param_type param_;
  random_internal::FastUniformBits<uint64_t> fast_u64_;
};

// -----------------------------------------------------------------------------
// Implementation details follow
// -----------------------------------------------------------------------------

template <typename IntType>
poisson_distribution<IntType>::param_type::param_type(double mean)
    : mean_(mean), split_(0) { __builtin_trap() /* STUB: not implemented */; }

template <typename IntType>
template <typename URBG>
typename poisson_distribution<IntType>::result_type
poisson_distribution<IntType>::operator()(
    URBG& g,  // NOLINT(runtime/references)
    const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename IntType>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,  // NOLINT(runtime/references)
    const poisson_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename IntType>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,  // NOLINT(runtime/references)
    poisson_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_POISSON_DISTRIBUTION_H_
