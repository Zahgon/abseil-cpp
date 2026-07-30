// Copyright 2025 The Abseil Authors.
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
#include <string>
#include <vector>

#include "absl/container/linked_hash_map.h"
#include "absl/functional/function_ref.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "benchmark/benchmark.h"

namespace {

struct BenchmarkData {
  std::vector<std::string> sample;
  size_t str_bytes = 0;
  explicit BenchmarkData(int size,
                         absl::FunctionRef<std::string(int)> factory) { __builtin_trap() /* STUB: not implemented */; }
};

void BenchmarkTryEmplaceStrings(benchmark::State& state,
                                absl::FunctionRef<std::string(int)> factory) { __builtin_trap() /* STUB: not implemented */; }

void BenchmarkInsertOrAssignStrings(
    benchmark::State& state, absl::FunctionRef<std::string(int)> factory) { __builtin_trap() /* STUB: not implemented */; }

constexpr absl::string_view kFormatShort = "%10d";
constexpr absl::string_view kFormatLong =
    "a longer string that exceeds the SSO %10d";

void BM_TryEmplaceShortStrings_Hit(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_TryEmplaceShortStrings_Hit)->Range(1, 1 << 16);

void BM_TryEmplaceLongStrings_Hit(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_TryEmplaceLongStrings_Hit)->Range(1, 1 << 16);

void BM_TryEmplaceShortStrings_Miss(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_TryEmplaceShortStrings_Miss)->Range(1, 1 << 16);

void BM_TryEmplaceLongStrings_Miss(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_TryEmplaceLongStrings_Miss)->Range(1, 1 << 16);

void BM_InsertOrAssignShortStrings_Hit(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InsertOrAssignShortStrings_Hit)->Range(1, 1 << 16);

void BM_InsertOrAssignLongStrings_Hit(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InsertOrAssignLongStrings_Hit)->Range(1, 1 << 16);

void BM_InsertOrAssignShortStrings_Miss(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InsertOrAssignShortStrings_Miss)->Range(1, 1 << 16);

void BM_InsertOrAssignLongStrings_Miss(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InsertOrAssignLongStrings_Miss)->Range(1, 1 << 16);

}  // namespace
