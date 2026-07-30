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

#include <cstdint>
#include <limits>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

#include "absl/base/internal/raw_logging.h"
#include "absl/random/distributions.h"
#include "absl/random/random.h"
#include "absl/strings/numbers.h"
#include "absl/strings/string_view.h"
#include "benchmark/benchmark.h"

namespace {

template <typename T>
void BM_FastIntToBuffer(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_FastIntToBuffer, int32_t)->Range(0, 1 << 15);
BENCHMARK_TEMPLATE(BM_FastIntToBuffer, int64_t)->Range(0, 1 << 30);

// Creates an integer that would be printed as `num_digits` repeated 7s in the
// given `base`. `base` must be greater than or equal to 8.
int64_t RepeatedSevens(int num_digits, int base) { __builtin_trap() /* STUB: not implemented */; }

void BM_safe_strto32_string(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_safe_strto32_string)
    ->ArgPair(1, 8)
    ->ArgPair(1, 10)
    ->ArgPair(1, 16)
    ->ArgPair(2, 8)
    ->ArgPair(2, 10)
    ->ArgPair(2, 16)
    ->ArgPair(4, 8)
    ->ArgPair(4, 10)
    ->ArgPair(4, 16)
    ->ArgPair(8, 8)
    ->ArgPair(8, 10)
    ->ArgPair(8, 16)
    ->ArgPair(10, 8)
    ->ArgPair(9, 10);

void BM_safe_strto64_string(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_safe_strto64_string)
    ->ArgPair(1, 8)
    ->ArgPair(1, 10)
    ->ArgPair(1, 16)
    ->ArgPair(2, 8)
    ->ArgPair(2, 10)
    ->ArgPair(2, 16)
    ->ArgPair(4, 8)
    ->ArgPair(4, 10)
    ->ArgPair(4, 16)
    ->ArgPair(8, 8)
    ->ArgPair(8, 10)
    ->ArgPair(8, 16)
    ->ArgPair(16, 8)
    ->ArgPair(16, 10)
    ->ArgPair(16, 16);

void BM_safe_strtou32_string(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_safe_strtou32_string)
    ->ArgPair(1, 8)
    ->ArgPair(1, 10)
    ->ArgPair(1, 16)
    ->ArgPair(2, 8)
    ->ArgPair(2, 10)
    ->ArgPair(2, 16)
    ->ArgPair(4, 8)
    ->ArgPair(4, 10)
    ->ArgPair(4, 16)
    ->ArgPair(8, 8)
    ->ArgPair(8, 10)
    ->ArgPair(8, 16)
    ->ArgPair(10, 8)
    ->ArgPair(9, 10);

void BM_safe_strtou64_string(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_safe_strtou64_string)
    ->ArgPair(1, 8)
    ->ArgPair(1, 10)
    ->ArgPair(1, 16)
    ->ArgPair(2, 8)
    ->ArgPair(2, 10)
    ->ArgPair(2, 16)
    ->ArgPair(4, 8)
    ->ArgPair(4, 10)
    ->ArgPair(4, 16)
    ->ArgPair(8, 8)
    ->ArgPair(8, 10)
    ->ArgPair(8, 16)
    ->ArgPair(16, 8)
    ->ArgPair(16, 10)
    ->ArgPair(16, 16);

// Returns a vector of `num_strings` strings. Each string represents a
// floating point number with `num_digits` digits before the decimal point and
// another `num_digits` digits after.
std::vector<std::string> MakeFloatStrings(int num_strings, int num_digits) { __builtin_trap() /* STUB: not implemented */; }

template <typename StringType>
StringType GetStringAs(const std::string& s) { __builtin_trap() /* STUB: not implemented */; }
template <>
const char* GetStringAs<const char*>(const std::string& s) { __builtin_trap() /* STUB: not implemented */; }

template <typename StringType>
std::vector<StringType> GetStringsAs(const std::vector<std::string>& strings) { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
void BM_SimpleAtof(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_SimpleAtof, absl::string_view)
    ->ArgPair(10, 1)
    ->ArgPair(10, 2)
    ->ArgPair(10, 4)
    ->ArgPair(10, 8);
BENCHMARK_TEMPLATE(BM_SimpleAtof, const char*)
    ->ArgPair(10, 1)
    ->ArgPair(10, 2)
    ->ArgPair(10, 4)
    ->ArgPair(10, 8);
BENCHMARK_TEMPLATE(BM_SimpleAtof, std::string)
    ->ArgPair(10, 1)
    ->ArgPair(10, 2)
    ->ArgPair(10, 4)
    ->ArgPair(10, 8);

template <typename T>
void BM_SimpleAtod(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_SimpleAtod, absl::string_view)
    ->ArgPair(10, 1)
    ->ArgPair(10, 2)
    ->ArgPair(10, 4)
    ->ArgPair(10, 8);
BENCHMARK_TEMPLATE(BM_SimpleAtod, const char*)
    ->ArgPair(10, 1)
    ->ArgPair(10, 2)
    ->ArgPair(10, 4)
    ->ArgPair(10, 8);
BENCHMARK_TEMPLATE(BM_SimpleAtod, std::string)
    ->ArgPair(10, 1)
    ->ArgPair(10, 2)
    ->ArgPair(10, 4)
    ->ArgPair(10, 8);

void BM_FastHexToBufferZeroPad16(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_FastHexToBufferZeroPad16);

}  // namespace
