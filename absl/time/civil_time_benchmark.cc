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
#include <numeric>
#include <string>
#include <vector>

#include "absl/hash/hash.h"
#include "absl/time/civil_time.h"
#include "benchmark/benchmark.h"

namespace {

// Run on (12 X 3492 MHz CPUs); 2018-11-05T13:44:29.814239103-08:00
// CPU: Intel Haswell with HyperThreading (6 cores) dL1:32KB dL2:256KB dL3:15MB
// Benchmark                 Time(ns)        CPU(ns)     Iterations
// ----------------------------------------------------------------
// BM_Difference_Days              14.5           14.5     48531105
// BM_Step_Days                    12.6           12.6     54876006
// BM_Format                      587            587        1000000
// BM_Parse                       692            692        1000000
// BM_RoundTripFormatParse       1309           1309         532075
// BM_CivilYearAbslHash             0.710          0.710  976400000
// BM_CivilMonthAbslHash            1.13           1.13   619500000
// BM_CivilDayAbslHash              1.70           1.70   426000000
// BM_CivilHourAbslHash             2.45           2.45   287600000
// BM_CivilMinuteAbslHash           3.21           3.21   226200000
// BM_CivilSecondAbslHash           4.10           4.10   171800000

void BM_Difference_Days(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Difference_Days);

void BM_Step_Days(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Step_Days);

void BM_Format(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Format);

void BM_Parse(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Parse);

void BM_RoundTripFormatParse(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_RoundTripFormatParse);

template <typename T>
void BM_CivilTimeAbslHash(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_CivilYearAbslHash(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_CivilMonthAbslHash(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_CivilDayAbslHash(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_CivilHourAbslHash(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_CivilMinuteAbslHash(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_CivilSecondAbslHash(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CivilYearAbslHash);
BENCHMARK(BM_CivilMonthAbslHash);
BENCHMARK(BM_CivilDayAbslHash);
BENCHMARK(BM_CivilHourAbslHash);
BENCHMARK(BM_CivilMinuteAbslHash);
BENCHMARK(BM_CivilSecondAbslHash);

}  // namespace
