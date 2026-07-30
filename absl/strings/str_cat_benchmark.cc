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

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <tuple>
#include <utility>

#include "absl/random/log_uniform_int_distribution.h"
#include "absl/random/random.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/strings/substitute.h"
#include "benchmark/benchmark.h"

namespace {

const char kStringOne[] = "Once Upon A Time, ";
const char kStringTwo[] = "There was a string benchmark";

// We want to include negative numbers in the benchmark, so this function
// is used to count 0, 1, -1, 2, -2, 3, -3, ...
inline int IncrementAlternatingSign(int i) { __builtin_trap() /* STUB: not implemented */; }

void BM_Sum_By_StrCat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Sum_By_StrCat);

void BM_StrCat_By_snprintf(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrCat_By_snprintf);

void BM_StrCat_By_Strings(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrCat_By_Strings);

void BM_StrCat_By_StringOpPlus(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrCat_By_StringOpPlus);

void BM_StrCat_By_StrCat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrCat_By_StrCat);

void BM_HexCat_By_StrCat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_HexCat_By_StrCat);

void BM_HexCat_By_StrFormat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_HexCat_By_StrFormat);

void BM_HexCat_By_Substitute(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_HexCat_By_Substitute);

void BM_FloatToString_By_StrCat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_FloatToString_By_StrCat);

void BM_DoubleToString_By_SixDigits(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_DoubleToString_By_SixDigits);

void BM_FloatToString_By_StrFormat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_FloatToString_By_StrFormat);

template <typename Table, size_t... Index>
void BM_StrAppendImpl(benchmark::State& state, Table table, size_t total_bytes,
                      std::index_sequence<Index...>) { __builtin_trap() /* STUB: not implemented */; }

template <typename Array>
void BM_StrAppend(benchmark::State& state, Array&& table) { __builtin_trap() /* STUB: not implemented */; }

void BM_StrAppendStr(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
void BM_StrAppendInt(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

void StrAppendConfig(::benchmark::Benchmark* benchmark) { __builtin_trap() /* STUB: not implemented */; }

BENCHMARK(BM_StrAppendStr)->Apply(StrAppendConfig);
BENCHMARK(BM_StrAppendInt<int64_t>)->Apply(StrAppendConfig);
BENCHMARK(BM_StrAppendInt<uint64_t>)->Apply(StrAppendConfig);
BENCHMARK(BM_StrAppendInt<int32_t>)->Apply(StrAppendConfig);
BENCHMARK(BM_StrAppendInt<uint32_t>)->Apply(StrAppendConfig);

template <typename... Chunks>
void BM_StrCatImpl(benchmark::State& state,
                      Chunks... chunks) { __builtin_trap() /* STUB: not implemented */; }

void BM_StrCat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

BENCHMARK(BM_StrCat)->Arg(1)->Arg(2)->Arg(3)->Arg(4);

void BM_StrCat_int(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

BENCHMARK(BM_StrCat_int);

}  // namespace
