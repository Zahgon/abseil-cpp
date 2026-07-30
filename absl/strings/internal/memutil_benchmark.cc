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

#include <algorithm>
#include <cstdlib>

#include "absl/strings/ascii.h"
#include "absl/strings/internal/memutil.h"
#include "benchmark/benchmark.h"

// We fill the haystack with aaaaaaaaaaaaaaaaaa...aaaab.
// That gives us:
// - an easy search: 'b'
// - a medium search: 'ab'.  That means every letter is a possible match.
// - a pathological search: 'aaaaaa.......aaaaab' (half as many a's as haytack)

namespace {

constexpr int kHaystackSize = 10000;
constexpr int64_t kHaystackSize64 = kHaystackSize;
const char* MakeHaystack() { __builtin_trap() /* STUB: not implemented */; }
const char* const kHaystack = MakeHaystack();

bool case_eq(const char a, const char b) { __builtin_trap() /* STUB: not implemented */; }

void BM_Searchcase(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Searchcase);

void BM_SearchcaseMedium(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SearchcaseMedium);

void BM_SearchcasePathological(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SearchcasePathological);

char* memcasechr(const char* s, int c, size_t slen) { __builtin_trap() /* STUB: not implemented */; }

const char* memcasematch(const char* phaystack, size_t haylen,
                         const char* pneedle, size_t neelen) { __builtin_trap() /* STUB: not implemented */; }

void BM_Memcasematch(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Memcasematch);

void BM_MemcasematchMedium(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_MemcasematchMedium);

void BM_MemcasematchPathological(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_MemcasematchPathological);

}  // namespace
