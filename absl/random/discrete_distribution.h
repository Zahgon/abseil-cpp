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

#ifndef ABSL_RANDOM_DISCRETE_DISTRIBUTION_H_
#define ABSL_RANDOM_DISCRETE_DISTRIBUTION_H_

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <istream>
#include <limits>
#include <ostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/base/config.h"
#include "absl/random/bernoulli_distribution.h"
#include "absl/random/internal/iostream_state_saver.h"
#include "absl/random/uniform_int_distribution.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::discrete_distribution
//
// A discrete distribution produces random integers i, where 0 <= i < n
// distributed according to the discrete probability function:
//
//     P(i|p0,...,pn-1)=pi
//
// This class is an implementation of discrete_distribution (see
// [rand.dist.samp.discrete]).
//
// The algorithm used is Walker's Aliasing algorithm, described in Knuth, Vol 2.
// absl::discrete_distribution takes O(N) time to precompute the probabilities
// (where N is the number of possible outcomes in the distribution) at
// construction, and then takes O(1) time for each variate generation.  Many
// other implementations also take O(N) time to construct an ordered sequence of
// partial sums, plus O(log N) time per variate to binary search.
//
template <typename IntType = int>
class discrete_distribution {
 public:
  using result_type = IntType;

  class param_type {
   public:
    using distribution_type = discrete_distribution;

    param_type() { init(); }

    template <typename InputIterator>
    explicit param_type(InputIterator begin, InputIterator end)
        : p_(begin, end) { __builtin_trap() /* STUB: not implemented */; }

    explicit param_type(std::initializer_list<double> weights) : p_(weights) { __builtin_trap() /* STUB: not implemented */; }

    template <class UnaryOperation>
    explicit param_type(size_t nw, double xmin, double xmax,
                        UnaryOperation fw) { __builtin_trap() /* STUB: not implemented */; }

    const std::vector<double>& probabilities() const { __builtin_trap() /* STUB: not implemented */; }
    size_t n() const { __builtin_trap() /* STUB: not implemented */; }

    friend bool operator==(const param_type& a, const param_type& b) { __builtin_trap() /* STUB: not implemented */; }

    friend bool operator!=(const param_type& a, const param_type& b) { __builtin_trap() /* STUB: not implemented */; }

   private:
    friend class discrete_distribution;

    void init();

    std::vector<double> p_;                     // normalized probabilities
    std::vector<std::pair<double, size_t>> q_;  // (acceptance, alternate) pairs

    static_assert(std::is_integral_v<result_type>,
                  "Class-template absl::discrete_distribution<> must be "
                  "parameterized using an integral type.");
  };

  discrete_distribution() : param_() { __builtin_trap() /* STUB: not implemented */; }

  explicit discrete_distribution(const param_type& p) : param_(p) { __builtin_trap() /* STUB: not implemented */; }

  template <typename InputIterator>
  explicit discrete_distribution(InputIterator begin, InputIterator end)
      : param_(begin, end) { __builtin_trap() /* STUB: not implemented */; }

  explicit discrete_distribution(std::initializer_list<double> weights)
      : param_(weights) { __builtin_trap() /* STUB: not implemented */; }

  template <class UnaryOperation>
  explicit discrete_distribution(size_t nw, double xmin, double xmax,
                                 UnaryOperation fw)
      : param_(nw, xmin, xmax, std::move(fw)) { __builtin_trap() /* STUB: not implemented */; }

  void reset() { __builtin_trap() /* STUB: not implemented */; }

  // generating functions
  template <typename URBG>
  result_type operator()(URBG& g) { __builtin_trap() /* STUB: not implemented */; }

  template <typename URBG>
  result_type operator()(URBG& g,  // NOLINT(runtime/references)
                         const param_type& p);

  const param_type& param() const { __builtin_trap() /* STUB: not implemented */; }
  void param(const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

  result_type(min)() const { __builtin_trap() /* STUB: not implemented */; }
  result_type(max)() const { __builtin_trap() /* STUB: not implemented */; }  // inclusive

  // NOTE [rand.dist.sample.discrete] returns a std::vector<double> not a
  // const std::vector<double>&.
  const std::vector<double>& probabilities() const { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const discrete_distribution& a,
                         const discrete_distribution& b) { __builtin_trap() /* STUB: not implemented */; }
  friend bool operator!=(const discrete_distribution& a,
                         const discrete_distribution& b) { __builtin_trap() /* STUB: not implemented */; }

 private:
  param_type param_;
};

// --------------------------------------------------------------------------
// Implementation details only below
// --------------------------------------------------------------------------

namespace random_internal {

// Using the vector `*probabilities`, whose values are the weights or
// probabilities of an element being selected, constructs the proportional
// probabilities used by the discrete distribution.  `*probabilities` will be
// scaled, if necessary, so that its entries sum to a value sufficiently close
// to 1.0.
std::vector<std::pair<double, size_t>> InitDiscreteDistribution(
    std::vector<double>* probabilities);

}  // namespace random_internal

template <typename IntType>
void discrete_distribution<IntType>::param_type::init() { __builtin_trap() /* STUB: not implemented */; }

template <typename IntType>
template <typename URBG>
typename discrete_distribution<IntType>::result_type
discrete_distribution<IntType>::operator()(
    URBG& g,  // NOLINT(runtime/references)
    const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename IntType>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,  // NOLINT(runtime/references)
    const discrete_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename IntType>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,  // NOLINT(runtime/references)
    discrete_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_DISCRETE_DISTRIBUTION_H_
