// Copyright 2018 The Abseil Authors.
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
// mocking_bit_gen.h
// -----------------------------------------------------------------------------
//
// This file includes an `absl::MockingBitGen` class to use as a mock within the
// GoogleTest testing framework. Such a mock is useful to provide deterministic
// values as return values within (otherwise random) Abseil distribution
// functions. Such determinism within a mock is useful within testing frameworks
// to test otherwise indeterminate APIs.
//
// More information about the GoogleTest testing framework is available at
// https://github.com/google/googletest

#ifndef ABSL_RANDOM_MOCKING_BIT_GEN_H_
#define ABSL_RANDOM_MOCKING_BIT_GEN_H_

#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

#include "gmock/gmock.h"
#include "absl/base/config.h"
#include "absl/base/fast_type_id.h"
#include "absl/container/flat_hash_map.h"
#include "absl/meta/type_traits.h"
#include "absl/random/internal/mock_helpers.h"
#include "absl/random/mocking_access.h"
#include "absl/random/random.h"
#include "absl/utility/utility.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// MockingBitGen
//
// `absl::MockingBitGen` is a mock Uniform Random Bit Generator (URBG) class
// which can act in place of an `absl::BitGen` URBG within tests using the
// GoogleTest testing framework.
//
// Usage:
//
// Use an `absl::MockingBitGen` along with a mock distribution object (within
// mock_distributions.h) inside Googletest constructs such as ON_CALL(),
// EXPECT_TRUE(), etc. to produce deterministic results conforming to the
// distribution's API contract.
//
// Example:
//
//  // Mock a call to an `absl::Bernoulli` distribution using Googletest
//   absl::MockingBitGen bitgen;
//
//   ON_CALL(absl::MockBernoulli(), Call(bitgen, 0.5))
//       .WillByDefault(testing::Return(true));
//   EXPECT_TRUE(absl::Bernoulli(bitgen, 0.5));
//
//  // Mock a call to an `absl::Uniform` distribution within Googletest
//  absl::MockingBitGen bitgen;
//
//   ON_CALL(absl::MockUniform<int>(), Call(bitgen, testing::_, testing::_))
//       .WillByDefault([] (int low, int high) {
//           return low + (high - low) / 2;
//       });
//
//   EXPECT_EQ(absl::Uniform<int>(gen, 0, 10), 5);
//   EXPECT_EQ(absl::Uniform<int>(gen, 30, 40), 35);
//
// At this time, only mock distributions supplied within the Abseil random
// library are officially supported.
//
// EXPECT_CALL and ON_CALL need to be made within the same DLL component as
// the call to absl::Uniform and related methods, otherwise mocking will fail
// since the  underlying implementation creates a type-specific pointer which
// will be distinct across different DLL boundaries.
//
class MockingBitGen { __builtin_trap() /* STUB: not implemented */; };

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_MOCKING_BIT_GEN_H_
