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

#include <cstddef>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "absl/base/internal/raw_logging.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "benchmark/benchmark.h"

namespace {

std::string MakeTestString(int desired_length) { __builtin_trap() /* STUB: not implemented */; }

void BM_Split2StringView(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_Split2StringView, 0, 1 << 20);

static const absl::string_view kDelimiters = ";:,.";

std::string MakeMultiDelimiterTestString(int desired_length) { __builtin_trap() /* STUB: not implemented */; }

// Measure StrSplit with ByAnyChar with four delimiters to choose from.
void BM_Split2StringViewByAnyChar(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_Split2StringViewByAnyChar, 0, 1 << 20);

void BM_Split2StringViewLifted(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_Split2StringViewLifted, 0, 1 << 20);

void BM_Split2String(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_Split2String, 0, 1 << 20);

// This benchmark is for comparing Split2 to Split1 (SplitStringUsing). In
// particular, this benchmark uses SkipEmpty() to match SplitStringUsing's
// behavior.
void BM_Split2SplitStringUsing(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_Split2SplitStringUsing, 0, 1 << 20);

void BM_SplitStringToUnorderedSet(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_SplitStringToUnorderedSet, 0, 1 << 20);

void BM_SplitStringToUnorderedMap(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_SplitStringToUnorderedMap, 0, 1 << 20);

void BM_SplitStringAllowEmpty(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_RANGE(BM_SplitStringAllowEmpty, 0, 1 << 20);

struct OneCharLiteral {
  char operator()() const { __builtin_trap() /* STUB: not implemented */; }
};

struct OneCharStringLiteral {
  const char* operator()() const { __builtin_trap() /* STUB: not implemented */; }
};

template <typename DelimiterFactory>
void BM_SplitStringWithOneChar(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_SplitStringWithOneChar, OneCharLiteral);
BENCHMARK_TEMPLATE(BM_SplitStringWithOneChar, OneCharStringLiteral);

template <typename DelimiterFactory>
void BM_SplitStringWithOneCharNoVector(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_SplitStringWithOneCharNoVector, OneCharLiteral);
BENCHMARK_TEMPLATE(BM_SplitStringWithOneCharNoVector, OneCharStringLiteral);

}  // namespace
