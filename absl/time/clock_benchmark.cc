// Copyright 2018 The Abseil Authors.
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

#include "absl/time/clock.h"

#if !defined(_WIN32)
#include <sys/time.h>
#else
#include <winsock2.h>
#endif  // _WIN32
#include <cstdio>

#include "absl/base/internal/cycleclock.h"
#include "benchmark/benchmark.h"

namespace {

void BM_Clock_Now_AbslTime(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Clock_Now_AbslTime);

void BM_Clock_Now_GetCurrentTimeNanos(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Clock_Now_GetCurrentTimeNanos);

void BM_Clock_Now_AbslTime_ToUnixNanos(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Clock_Now_AbslTime_ToUnixNanos);

void BM_Clock_Now_CycleClock(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Clock_Now_CycleClock);

#if !defined(_WIN32)
static void BM_Clock_Now_gettimeofday(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Clock_Now_gettimeofday);

static void BM_Clock_Now_clock_gettime(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Clock_Now_clock_gettime);
#endif  // _WIN32

}  // namespace
