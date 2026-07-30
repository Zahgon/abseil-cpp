// Copyright 2022 The Abseil Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>
#include <string>

#include "absl/crc/crc32c.h"
#include "absl/crc/internal/crc32c.h"
#include "absl/memory/memory.h"
#include "absl/strings/string_view.h"
#include "benchmark/benchmark.h"

namespace {

std::string TestString(size_t len) { __builtin_trap() /* STUB: not implemented */; }

void BM_Calculate(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Calculate)
    ->Arg(0)
    ->Arg(1)
    ->Arg(100)
    ->Arg(2048)
    ->Arg(10000)
    ->Arg(500000);

void BM_Extend(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Extend)
    ->Arg(0)
    ->Arg(1)
    ->Arg(100)
    ->Arg(2048)
    ->Arg(10000)
    ->Arg(500000)
    ->Arg(100 * 1000 * 1000);

// Make working set >> CPU cache size to benchmark prefetches better
void BM_ExtendCacheMiss(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_ExtendCacheMiss)->Arg(10)->Arg(100)->Arg(1000)->Arg(100000);

void BM_ExtendByZeroes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_ExtendByZeroes)
    ->RangeMultiplier(10)
    ->Range(1, 1000000)
    ->RangeMultiplier(32)
    ->Range(1, 1 << 20);

void BM_UnextendByZeroes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_UnextendByZeroes)
    ->RangeMultiplier(10)
    ->Range(1, 1000000)
    ->RangeMultiplier(32)
    ->Range(1, 1 << 20);

void BM_Concat(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Concat)
    ->RangeMultiplier(10)
    ->Range(1, 1000000)
    ->RangeMultiplier(32)
    ->Range(1, 1 << 20);

void BM_Memcpy(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Memcpy)->Arg(0)->Arg(1)->Arg(100)->Arg(2048)->Arg(10000)->Arg(
    500000);

void BM_RemoveSuffix(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_RemoveSuffix)
    ->ArgPair(1, 1)
    ->ArgPair(100, 10)
    ->ArgPair(100, 100)
    ->ArgPair(10000, 1)
    ->ArgPair(10000, 100)
    ->ArgPair(10000, 10000)
    ->ArgPair(500000, 1)
    ->ArgPair(500000, 100)
    ->ArgPair(500000, 10000)
    ->ArgPair(500000, 500000);
}  // namespace
