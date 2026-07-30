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

#ifndef ABSL_RANDOM_BERNOULLI_DISTRIBUTION_H_
#define ABSL_RANDOM_BERNOULLI_DISTRIBUTION_H_

#include <cassert>
#include <cstdint>
#include <istream>
#include <ostream>

#include "absl/base/config.h"
#include "absl/base/optimization.h"
#include "absl/random/internal/fast_uniform_bits.h"
#include "absl/random/internal/iostream_state_saver.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::bernoulli_distribution is a drop in replacement for
// std::bernoulli_distribution. It guarantees that (given a perfect
// UniformRandomBitGenerator) the acceptance probability is *exactly* equal to
// the given double.
//
// The implementation assumes that double is IEEE754
class bernoulli_distribution { __builtin_trap() /* STUB: not implemented */; };

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,  // NOLINT(runtime/references)
    const bernoulli_distribution& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,  // NOLINT(runtime/references)
    bernoulli_distribution& x) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
bool bernoulli_distribution::Generate(double p,
                                      URBG& g) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_BERNOULLI_DISTRIBUTION_H_
