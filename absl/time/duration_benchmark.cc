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

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <string>

#include "absl/base/attributes.h"
#include "absl/flags/flag.h"
#include "absl/time/time.h"
#include "benchmark/benchmark.h"

ABSL_FLAG(absl::Duration, absl_duration_flag_for_benchmark,
          absl::Milliseconds(1),
          "Flag to use for benchmarking duration flag access speed.");

namespace {

//
// Factory functions
//

void BM_Duration_Factory_Nanoseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_Nanoseconds);

void BM_Duration_Factory_Microseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_Microseconds);

void BM_Duration_Factory_Milliseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_Milliseconds);

void BM_Duration_Factory_Seconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_Seconds);

void BM_Duration_Factory_Minutes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_Minutes);

void BM_Duration_Factory_Hours(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_Hours);

void BM_Duration_Factory_DoubleNanoseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_DoubleNanoseconds);

void BM_Duration_Factory_DoubleMicroseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_DoubleMicroseconds);

void BM_Duration_Factory_DoubleMilliseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_DoubleMilliseconds);

void BM_Duration_Factory_DoubleSeconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_DoubleSeconds);

void BM_Duration_Factory_DoubleMinutes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_DoubleMinutes);

void BM_Duration_Factory_DoubleHours(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Factory_DoubleHours);

//
// Arithmetic
//

void BM_Duration_Addition(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Addition);

void BM_Duration_Subtraction(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Subtraction);

void BM_Duration_Multiplication_Fixed(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Multiplication_Fixed);

void BM_Duration_Multiplication_Double(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Multiplication_Double);

void BM_Duration_Division_Fixed(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Division_Fixed);

void BM_Duration_Division_Double(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Division_Double);

void BM_Duration_FDivDuration_Nanoseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_FDivDuration_Nanoseconds);

void BM_Duration_IDivDuration_Nanoseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_IDivDuration_Nanoseconds);

void BM_Duration_IDivDuration_Microseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_IDivDuration_Microseconds);

void BM_Duration_IDivDuration_Milliseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_IDivDuration_Milliseconds);

void BM_Duration_IDivDuration_Seconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_IDivDuration_Seconds);

void BM_Duration_IDivDuration_Minutes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_IDivDuration_Minutes);

void BM_Duration_IDivDuration_Hours(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_IDivDuration_Hours);

void BM_Duration_Modulo(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Modulo);

void BM_Duration_Modulo_FastPath(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_Modulo_FastPath);

void BM_Duration_ToInt64Nanoseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToInt64Nanoseconds);

void BM_Duration_ToInt64Microseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToInt64Microseconds);

void BM_Duration_ToInt64Milliseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToInt64Milliseconds);

void BM_Duration_ToInt64Seconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToInt64Seconds);

void BM_Duration_ToInt64Minutes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToInt64Minutes);

void BM_Duration_ToInt64Hours(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToInt64Hours);

//
// ToDoubleXYZ
//
void BM_Duration_ToDoubleNanoseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleNanoseconds);

void BM_Duration_ToDoubleMicroseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleMicroseconds);

void BM_Duration_ToDoubleMilliseconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleMilliseconds);

void BM_Duration_ToDoubleSeconds(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleSeconds);

void BM_Duration_ToDoubleMinutes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleMinutes);

void BM_Duration_ToDoubleHours(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleHours);

//
// ToDoubleXYZ Latency
//
void BM_Duration_ToDoubleNanoseconds_Latency(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleNanoseconds_Latency);

void BM_Duration_ToDoubleMicroseconds_Latency(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleMicroseconds_Latency);

void BM_Duration_ToDoubleMilliseconds_Latency(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleMilliseconds_Latency);

void BM_Duration_ToDoubleSeconds_Latency(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleSeconds_Latency);

void BM_Duration_ToDoubleMinutes_Latency(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleMinutes_Latency);

void BM_Duration_ToDoubleHours_Latency(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToDoubleHours_Latency);

//
// To/FromTimespec
//

void BM_Duration_ToTimespec_AbslTime(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToTimespec_AbslTime);

ABSL_ATTRIBUTE_NOINLINE timespec DoubleToTimespec(double seconds) { __builtin_trap() /* STUB: not implemented */; }

void BM_Duration_ToTimespec_Double(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ToTimespec_Double);

void BM_Duration_FromTimespec_AbslTime(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_FromTimespec_AbslTime);

ABSL_ATTRIBUTE_NOINLINE double TimespecToDouble(timespec ts) { __builtin_trap() /* STUB: not implemented */; }

void BM_Duration_FromTimespec_Double(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_FromTimespec_Double);

//
// String conversions
//

const char* const kDurations[] = {
    "0",                                   // 0
    "123ns",                               // 1
    "1h2m3s",                              // 2
    "-2h3m4.005006007s",                   // 3
    "2562047788015215h30m7.99999999975s",  // 4
};
const int kNumDurations = sizeof(kDurations) / sizeof(kDurations[0]);

void BM_Duration_FormatDuration(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_FormatDuration)->DenseRange(0, kNumDurations - 1);

void BM_Duration_ParseDuration(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_ParseDuration)->DenseRange(0, kNumDurations - 1);

//
// Flag access
//
void BM_Duration_GetFlag(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Duration_GetFlag);

}  // namespace
