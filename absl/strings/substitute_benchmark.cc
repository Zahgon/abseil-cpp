// Copyright 2020 The Abseil Authors.
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
#include <string>

#include "absl/strings/str_cat.h"
#include "absl/strings/substitute.h"
#include "benchmark/benchmark.h"

namespace {

void BM_Substitute(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Substitute)->Range(0, 1024);

// Like BM_Substitute, but use char* strings (which must then be copied
// to STL strings) for all parameters.  This demonstrates that it is faster
// to use absl::Substitute() even if your inputs are char* strings.
void BM_SubstituteCstr(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SubstituteCstr)->Range(0, 1024);

// For comparison with BM_Substitute.
void BM_StringPrintf(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StringPrintf)->Range(0, 1024);

// Benchmark using absl::Substitute() together with SimpleItoa() to print
// numbers.  This demonstrates that absl::Substitute() is faster than
// StringPrintf() even when the inputs are numbers.
void BM_SubstituteNumber(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SubstituteNumber)->Arg(0)->Arg(1 << 20);

// For comparison with BM_SubstituteNumber.
void BM_StrCatNumber(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrCatNumber)->Arg(0)->Arg(1 << 20);

// Benchmark using absl::Substitute() with a single substitution, to test the
// speed at which it copies simple text.  Even in this case, it's faster
// that StringPrintf().
void BM_SubstituteSimpleText(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SubstituteSimpleText)->Range(0, 1024);

// For comparison with BM_SubstituteSimpleText.
void BM_StrCatSimpleText(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrCatSimpleText)->Range(0, 1024);

std::string MakeFormatByDensity(int density, bool subs_mode) { __builtin_trap() /* STUB: not implemented */; }

void BM_SubstituteDensity(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SubstituteDensity)->Range(0, 256);

void BM_StrCatDensity(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrCatDensity)->Range(0, 256);

}  // namespace
