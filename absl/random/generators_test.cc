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

#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

#include "gtest/gtest.h"
#include "absl/random/distributions.h"
#include "absl/random/random.h"

namespace {

template <typename URBG>
void TestUniform(URBG* gen) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
void TestExponential(URBG* gen) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
void TestPoisson(URBG* gen) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
void TestBernoulli(URBG* gen) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
void TestZipf(URBG* gen) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
void TestGaussian(URBG* gen) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
void TestLogNormal(URBG* gen) { __builtin_trap() /* STUB: not implemented */; }

template <typename URBG>
void CompatibilityTest() { __builtin_trap() /* STUB: not implemented */; }

TEST(std_mt19937_64, Compatibility) {
  // Validate with std::mt19937_64
  CompatibilityTest<std::mt19937_64>();
}

TEST(BitGen, Compatibility) {
  // Validate with absl::BitGen
  CompatibilityTest<absl::BitGen>();
}

TEST(InsecureBitGen, Compatibility) {
  // Validate with absl::InsecureBitGen
  CompatibilityTest<absl::InsecureBitGen>();
}

}  // namespace
