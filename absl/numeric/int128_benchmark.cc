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

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/base/config.h"
#include "absl/numeric/int128.h"
#include "absl/random/random.h"
#include "benchmark/benchmark.h"

namespace {

constexpr size_t kSampleSize = 1000000;

template <typename T, typename H = std::conditional_t<
                          std::numeric_limits<T>::is_signed, int64_t, uint64_t>>
std::vector<std::pair<T, T>> GetRandomClass128SampleUniformDivisor() { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
void BM_DivideClass128UniformDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_DivideClass128UniformDivisor, absl::uint128);
BENCHMARK_TEMPLATE(BM_DivideClass128UniformDivisor, absl::int128);

template <typename T>
void BM_RemainderClass128UniformDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_RemainderClass128UniformDivisor, absl::uint128);
BENCHMARK_TEMPLATE(BM_RemainderClass128UniformDivisor, absl::int128);

template <typename T, typename H = std::conditional_t<
                          std::numeric_limits<T>::is_signed, int64_t, uint64_t>>
std::vector<std::pair<T, H>> GetRandomClass128SampleSmallDivisor() { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
void BM_DivideClass128SmallDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_DivideClass128SmallDivisor, absl::uint128);
BENCHMARK_TEMPLATE(BM_DivideClass128SmallDivisor, absl::int128);

template <typename T>
void BM_RemainderClass128SmallDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_RemainderClass128SmallDivisor, absl::uint128);
BENCHMARK_TEMPLATE(BM_RemainderClass128SmallDivisor, absl::int128);

std::vector<std::pair<absl::uint128, absl::uint128>> GetRandomClass128Sample() { __builtin_trap() /* STUB: not implemented */; }

void BM_MultiplyClass128(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_MultiplyClass128);

void BM_AddClass128(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_AddClass128);

#ifdef ABSL_HAVE_INTRINSIC_INT128

// Some implementations of <random> do not support __int128 when it is
// available, so we make our own uniform_int_distribution-like type.
template <typename T, typename H = std::conditional_t<
                          std::is_same_v<T, __int128>, int64_t, uint64_t>>
class UniformIntDistribution128 {
 public:
  // NOLINTNEXTLINE: mimicking std::uniform_int_distribution API
  template <class URBG>
  T operator()(URBG& generator) { __builtin_trap() /* STUB: not implemented */; }

 private:
  std::uniform_int_distribution<H> dist64_;
};

template <typename T, typename H = std::conditional_t<
                          std::is_same_v<T, __int128>, int64_t, uint64_t>>
std::vector<std::pair<T, T>> GetRandomIntrinsic128SampleUniformDivisor() { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
void BM_DivideIntrinsic128UniformDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_DivideIntrinsic128UniformDivisor, unsigned __int128);
BENCHMARK_TEMPLATE(BM_DivideIntrinsic128UniformDivisor, __int128);

template <typename T>
void BM_RemainderIntrinsic128UniformDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_RemainderIntrinsic128UniformDivisor, unsigned __int128);
BENCHMARK_TEMPLATE(BM_RemainderIntrinsic128UniformDivisor, __int128);

template <typename T, typename H = std::conditional_t<
                          std::is_same_v<T, __int128>, int64_t, uint64_t>>
std::vector<std::pair<T, H>> GetRandomIntrinsic128SampleSmallDivisor() { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
void BM_DivideIntrinsic128SmallDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_DivideIntrinsic128SmallDivisor, unsigned __int128);
BENCHMARK_TEMPLATE(BM_DivideIntrinsic128SmallDivisor, __int128);

template <typename T>
void BM_RemainderIntrinsic128SmallDivisor(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_RemainderIntrinsic128SmallDivisor, unsigned __int128);
BENCHMARK_TEMPLATE(BM_RemainderIntrinsic128SmallDivisor, __int128);

std::vector<std::pair<unsigned __int128, unsigned __int128>>
GetRandomIntrinsic128Sample() { __builtin_trap() /* STUB: not implemented */; }

void BM_MultiplyIntrinsic128(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_MultiplyIntrinsic128);

void BM_AddIntrinsic128(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_AddIntrinsic128);

#endif  // ABSL_HAVE_INTRINSIC_INT128

}  // namespace
