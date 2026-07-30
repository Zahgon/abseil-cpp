// Copyright 2022 The Abseil Authors.
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

#include <string>

#include "absl/strings/internal/damerau_levenshtein_distance.h"
#include "benchmark/benchmark.h"

namespace {

std::string MakeTestString(int desired_length, int num_edits) { __builtin_trap() /* STUB: not implemented */; }

void BenchmarkArgs(benchmark::internal::Benchmark* benchmark) { __builtin_trap() /* STUB: not implemented */; }

using absl::strings_internal::CappedDamerauLevenshteinDistance;
void BM_Distance(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Distance)->Apply(BenchmarkArgs);

}  // namespace
