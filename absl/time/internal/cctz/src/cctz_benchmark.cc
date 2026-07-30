// Copyright 2016 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   https://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include <algorithm>
#include <cassert>
#include <chrono>
#include <ctime>
#include <random>
#include <string>
#include <vector>

#include "benchmark/benchmark.h"
#include "absl/time/internal/cctz/include/cctz/civil_time.h"
#include "absl/time/internal/cctz/include/cctz/time_zone.h"
#include "absl/time/internal/cctz/src/test_time_zone_names.h"
#include "absl/time/internal/cctz/src/time_zone_impl.h"

namespace {

namespace cctz = absl::time_internal::cctz;

void BM_Difference_Days(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Difference_Days);

void BM_Step_Days(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Step_Days);

void BM_GetWeekday(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_GetWeekday);

void BM_NextWeekday(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_NextWeekday);

void BM_PrevWeekday(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_PrevWeekday);

const char RFC3339_full[] = "%Y-%m-%d%ET%H:%M:%E*S%Ez";
const char RFC3339_sec[] = "%Y-%m-%d%ET%H:%M:%S%Ez";

const char RFC1123_full[] = "%a, %d %b %Y %H:%M:%S %z";
const char RFC1123_no_wday[] = "%d %b %Y %H:%M:%S %z";

std::vector<std::string> AllTimeZoneNames() { __builtin_trap() /* STUB: not implemented */; }

cctz::time_zone TestTimeZone() { __builtin_trap() /* STUB: not implemented */; }

void BM_Zone_LoadUTCTimeZoneFirst(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_LoadUTCTimeZoneFirst);

void BM_Zone_LoadUTCTimeZoneLast(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_LoadUTCTimeZoneLast);

void BM_Zone_LoadTimeZoneFirst(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_LoadTimeZoneFirst);

void BM_Zone_LoadTimeZoneCached(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_LoadTimeZoneCached);

void BM_Zone_LoadLocalTimeZoneCached(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_LoadLocalTimeZoneCached);

void BM_Zone_LoadAllTimeZonesFirst(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_LoadAllTimeZonesFirst);

void BM_Zone_LoadAllTimeZonesCached(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_LoadAllTimeZonesCached);

void BM_Zone_TimeZoneEqualityImplicit(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_TimeZoneEqualityImplicit);

void BM_Zone_TimeZoneEqualityExplicit(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_TimeZoneEqualityExplicit);

void BM_Zone_UTCTimeZone(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Zone_UTCTimeZone);

// In each "ToCivil" benchmark we switch between two instants separated
// by at least one transition in order to defeat any internal caching of
// previous results (e.g., see local_time_hint_).
//
// The "UTC" variants use UTC instead of the Google/local time zone.

void BM_Time_ToCivil_CCTZ(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToCivil_CCTZ);

void BM_Time_ToCivil_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToCivil_Libc);

void BM_Time_ToCivilUTC_CCTZ(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToCivilUTC_CCTZ);

void BM_Time_ToCivilUTC_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_ToCivilUTC_Libc);

// In each "FromCivil" benchmark we switch between two YMDhms values
// separated by at least one transition in order to defeat any internal
// caching of previous results (e.g., see time_local_hint_).
//
// The "UTC" variants use UTC instead of the Google/local time zone.
// The "Day0" variants require normalization of the day of month.

void BM_Time_FromCivil_CCTZ(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivil_CCTZ);

void BM_Time_FromCivil_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivil_Libc);

void BM_Time_FromCivilUTC_CCTZ(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivilUTC_CCTZ);

// There is no BM_Time_FromCivilUTC_Libc.

void BM_Time_FromCivilDay0_CCTZ(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivilDay0_CCTZ);

void BM_Time_FromCivilDay0_Libc(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Time_FromCivilDay0_Libc);

const char* const kFormats[] = {
    RFC1123_full,           // 0
    RFC1123_no_wday,        // 1
    RFC3339_full,           // 2
    RFC3339_sec,            // 3
    "%Y-%m-%d%ET%H:%M:%S",  // 4
    "%Y-%m-%d",             // 5
    "%F%ET%T",              // 6
};
const int kNumFormats = sizeof(kFormats) / sizeof(kFormats[0]);

void BM_Format_FormatTime(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Format_FormatTime)->DenseRange(0, kNumFormats - 1);

void BM_Format_ParseTime(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Format_ParseTime)->DenseRange(0, kNumFormats - 1);

}  // namespace
