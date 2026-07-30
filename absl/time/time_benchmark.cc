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

#include "absl/time/time.h"

#if !defined(_WIN32)
#include <sys/time.h>
#endif  // _WIN32
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <memory>
#include <string>

#include "absl/time/clock.h"
#include "absl/time/internal/test_util.h"
#include "benchmark/benchmark.h"

namespace {

//
// Addition/Subtraction of a duration
//

void BM_Time_Arithmetic(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_Arithmetic);

//
// Time difference
//

void BM_Time_Difference(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_Difference);

//
// ToDateTime
//
// In each "ToDateTime" benchmark we switch between two instants
// separated by at least one transition in order to defeat any
// internal caching of previous results (e.g., see local_time_hint_).
//
// The "UTC" variants use UTC instead of the Google/local time zone.
//

void BM_Time_ToDateTime_Absl(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToDateTime_Absl);

void BM_Time_ToDateTime_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToDateTime_Libc);

void BM_Time_ToDateTimeUTC_Absl(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToDateTimeUTC_Absl);

void BM_Time_ToDateTimeUTC_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToDateTimeUTC_Libc);

//
// FromUnixMicros
//

void BM_Time_FromUnixMicros(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromUnixMicros);

void BM_Time_ToUnixNanos(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToUnixNanos);

void BM_Time_ToUnixMicros(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToUnixMicros);

void BM_Time_ToUnixMillis(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToUnixMillis);

void BM_Time_ToUnixSeconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToUnixSeconds);

//
// FromCivil
//
// In each "FromCivil" benchmark we switch between two YMDhms values
// separated by at least one transition in order to defeat any internal
// caching of previous results (e.g., see time_local_hint_).
//
// The "UTC" variants use UTC instead of the Google/local time zone.
// The "Day0" variants require normalization of the day of month.
//

void BM_Time_FromCivil_Absl(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivil_Absl);

void BM_Time_FromCivil_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivil_Libc);

void BM_Time_FromCivilUTC_Absl(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivilUTC_Absl);

void BM_Time_FromCivilDay0_Absl(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivilDay0_Absl);

void BM_Time_FromCivilDay0_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivilDay0_Libc);

//
// To/FromTimespec
//

void BM_Time_ToTimespec(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToTimespec);

void BM_Time_FromTimespec(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromTimespec);

//
// Comparison with InfiniteFuture/Past
//

void BM_Time_InfiniteFuture(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_InfiniteFuture);

void BM_Time_InfinitePast(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_InfinitePast);

}  // namespace
