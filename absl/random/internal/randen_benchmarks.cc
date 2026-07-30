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
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "absl/base/internal/raw_logging.h"
#include "absl/random/internal/nanobenchmark.h"
#include "absl/random/internal/randen.h"
#include "absl/random/internal/randen_detect.h"
#include "absl/random/internal/randen_engine.h"
#include "absl/random/internal/randen_hwaes.h"
#include "absl/random/internal/randen_slow.h"
#include "absl/strings/numbers.h"

namespace {

using absl::random_internal::CPUSupportsRandenHwAes;
using absl::random_internal::Randen;
using absl::random_internal::RandenHwAes;
using absl::random_internal::RandenSlow;

using absl::random_internal_nanobenchmark::FuncInput;
using absl::random_internal_nanobenchmark::FuncOutput;
using absl::random_internal_nanobenchmark::InvariantTicksPerSecond;
using absl::random_internal_nanobenchmark::MeasureClosure;
using absl::random_internal_nanobenchmark::Params;
using absl::random_internal_nanobenchmark::PinThreadToCPU;
using absl::random_internal_nanobenchmark::Result;

// Local state parameters.
static constexpr size_t kStateSizeT = Randen::kStateBytes / sizeof(uint64_t);
static constexpr size_t kSeedSizeT = Randen::kSeedBytes / sizeof(uint32_t);

// Randen implementation benchmarks.
template <typename T>
struct AbsorbFn : public T {
  // These are both cast to uint128* in the RandenHwAes implementation, so
  // ensure they are 16 byte aligned.
  alignas(16) mutable uint64_t state[kStateSizeT] = {};
  alignas(16) mutable uint32_t seed[kSeedSizeT] = {};

  static constexpr size_t bytes() { return {}; }

  FuncOutput operator()(const FuncInput num_iters) const { __builtin_trap() /* STUB: not implemented */; }
};

template <typename T>
struct GenerateFn : public T {
  mutable uint64_t state[kStateSizeT];
  GenerateFn() { __builtin_trap() /* STUB: not implemented */; }

  static constexpr size_t bytes() { return {}; }

  FuncOutput operator()(const FuncInput num_iters) const { __builtin_trap() /* STUB: not implemented */; }
};

template <typename UInt>
struct Engine {
  mutable absl::random_internal::randen_engine<UInt> rng;

  static constexpr size_t bytes() { return {}; }

  FuncOutput operator()(const FuncInput num_iters) const { __builtin_trap() /* STUB: not implemented */; }
};

template <size_t N>
void Print(const char* name, const size_t n, const Result (&results)[N],
           const size_t bytes) { __builtin_trap() /* STUB: not implemented */; }

// Fails here
template <typename Op, size_t N>
void Measure(const char* name, const FuncInput (&inputs)[N]) { __builtin_trap() /* STUB: not implemented */; }

// unpredictable == 1 but the compiler does not know that.
void RunAll(const int argc, char* argv[]) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

int main(int argc, char* argv[]) { __builtin_trap() /* STUB: not implemented */; }
