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

#ifndef ABSL_RANDOM_LOG_UNIFORM_INT_DISTRIBUTION_H_
#define ABSL_RANDOM_LOG_UNIFORM_INT_DISTRIBUTION_H_

#include <algorithm>
#include <cassert>
#include <cmath>
#include <istream>
#include <limits>
#include <ostream>

#include "absl/base/config.h"
#include "absl/random/internal/iostream_state_saver.h"
#include "absl/random/internal/traits.h"
#include "absl/random/uniform_int_distribution.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// log_uniform_int_distribution:
//
// Returns a random variate R in range [min, max] such that
// floor(log(R-min, base)) is uniformly distributed.
// We ensure uniformity by discretization using the
// boundary sets [0, 1, base, base * base, ... min(base*n, max)]
//
template <typename IntType = int>
class log_uniform_int_distribution {
 private:
  using unsigned_type =
      typename random_internal::make_unsigned_bits<IntType>::type;

 public:
  using result_type = IntType;

  class param_type {
   public:
    using distribution_type = log_uniform_int_distribution;

    explicit param_type(
        result_type min = 0,
        result_type max = (std::numeric_limits<result_type>::max)(),
        result_type base = 2)
        : min_(min),
          max_(max),
          base_(base),
          range_(static_cast<unsigned_type>(max_) -
                 static_cast<unsigned_type>(min_)),
          log_range_(0) { __builtin_trap() /* STUB: not implemented */; }

    result_type(min)() const { __builtin_trap() /* STUB: not implemented */; }
    result_type(max)() const { __builtin_trap() /* STUB: not implemented */; }
    result_type base() const { __builtin_trap() /* STUB: not implemented */; }

    friend bool operator==(const param_type& a, const param_type& b) { __builtin_trap() /* STUB: not implemented */; }

    friend bool operator!=(const param_type& a, const param_type& b) { __builtin_trap() /* STUB: not implemented */; }

   private:
    friend class log_uniform_int_distribution;

    int log_range() const { __builtin_trap() /* STUB: not implemented */; }
    unsigned_type range() const { __builtin_trap() /* STUB: not implemented */; }

    result_type min_;
    result_type max_;
    result_type base_;
    unsigned_type range_;  // max - min
    int log_range_;        // ceil(logN(range_))

    static_assert(random_internal::IsIntegral<IntType>::value,
                  "Class-template absl::log_uniform_int_distribution<> must be "
                  "parameterized using an integral type.");
  };

  log_uniform_int_distribution() : log_uniform_int_distribution(0) { __builtin_trap() /* STUB: not implemented */; }

  explicit log_uniform_int_distribution(
      result_type min,
      result_type max = (std::numeric_limits<result_type>::max)(),
      result_type base = 2)
      : param_(min, max, base) { __builtin_trap() /* STUB: not implemented */; }

  explicit log_uniform_int_distribution(const param_type& p) : param_(p) { __builtin_trap() /* STUB: not implemented */; }

  void reset() { __builtin_trap() /* STUB: not implemented */; }

  // generating functions
  template <typename URBG>
  result_type operator()(URBG& g) { __builtin_trap() /* STUB: not implemented */; }

  template <typename URBG>
  result_type operator()(URBG& g,  // NOLINT(runtime/references)
                         const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

  result_type(min)() const { __builtin_trap() /* STUB: not implemented */; }
  result_type(max)() const { __builtin_trap() /* STUB: not implemented */; }
  result_type base() const { __builtin_trap() /* STUB: not implemented */; }

  param_type param() const { __builtin_trap() /* STUB: not implemented */; }
  void param(const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const log_uniform_int_distribution& a,
                         const log_uniform_int_distribution& b) { __builtin_trap() /* STUB: not implemented */; }
  friend bool operator!=(const log_uniform_int_distribution& a,
                         const log_uniform_int_distribution& b) { __builtin_trap() /* STUB: not implemented */; }

 private:
  // Returns a log-uniform variate in the range [0, p.range()]. The caller
  // should add min() to shift the result to the correct range.
  template <typename URNG>
  unsigned_type Generate(URNG& g,  // NOLINT(runtime/references)
                         const param_type& p);

  param_type param_;
};

template <typename IntType>
template <typename URBG>
typename log_uniform_int_distribution<IntType>::unsigned_type
log_uniform_int_distribution<IntType>::Generate(
    URBG& g,  // NOLINT(runtime/references)
    const param_type& p) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename IntType>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,  // NOLINT(runtime/references)
    const log_uniform_int_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits, typename IntType>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,       // NOLINT(runtime/references)
    log_uniform_int_distribution<IntType>& x) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_LOG_UNIFORM_INT_DISTRIBUTION_H_
