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

#include <cstdlib>
#include <cstring>
#include <string>

#include "absl/strings/charconv.h"
#include "benchmark/benchmark.h"

namespace {

void BM_Strtod_Pi(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Strtod_Pi);

void BM_Absl_Pi(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Absl_Pi);

void BM_Strtod_Pi_float(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Strtod_Pi_float);

void BM_Absl_Pi_float(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Absl_Pi_float);

void BM_Strtod_HardLarge(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Strtod_HardLarge);

void BM_Absl_HardLarge(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Absl_HardLarge);

void BM_Strtod_HardSmall(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Strtod_HardSmall);

void BM_Absl_HardSmall(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Absl_HardSmall);

void BM_Strtod_HugeMantissa(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Strtod_HugeMantissa);

void BM_Absl_HugeMantissa(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Absl_HugeMantissa);

std::string MakeHardCase(int length) { __builtin_trap() /* STUB: not implemented */; }

void BM_Strtod_Big_And_Difficult(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Strtod_Big_And_Difficult)->Range(3, 5000);

void BM_Absl_Big_And_Difficult(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Absl_Big_And_Difficult)->Range(3, 5000);

}  // namespace

// ------------------------------------------------------------------------
// Benchmark                                 Time           CPU Iterations
// ------------------------------------------------------------------------
// BM_Strtod_Pi                             96 ns         96 ns    6337454
// BM_Absl_Pi                               35 ns         35 ns   20031996
// BM_Strtod_Pi_float                       91 ns         91 ns    7745851
// BM_Absl_Pi_float                         35 ns         35 ns   20430298
// BM_Strtod_HardLarge                     133 ns        133 ns    5288341
// BM_Absl_HardLarge                       181 ns        181 ns    3855615
// BM_Strtod_HardSmall                     279 ns        279 ns    2517243
// BM_Absl_HardSmall                       287 ns        287 ns    2458744
// BM_Strtod_HugeMantissa                  433 ns        433 ns    1604293
// BM_Absl_HugeMantissa                    160 ns        160 ns    4403671
// BM_Strtod_Big_And_Difficult/3           236 ns        236 ns    2942496
// BM_Strtod_Big_And_Difficult/8           232 ns        232 ns    2983796
// BM_Strtod_Big_And_Difficult/64          437 ns        437 ns    1591951
// BM_Strtod_Big_And_Difficult/512        1738 ns       1738 ns     402519
// BM_Strtod_Big_And_Difficult/4096       3943 ns       3943 ns     176128
// BM_Strtod_Big_And_Difficult/5000       4397 ns       4397 ns     157878
// BM_Absl_Big_And_Difficult/3              39 ns         39 ns   17799583
// BM_Absl_Big_And_Difficult/8              43 ns         43 ns   16096859
// BM_Absl_Big_And_Difficult/64            550 ns        550 ns    1259717
// BM_Absl_Big_And_Difficult/512          4167 ns       4167 ns     171414
// BM_Absl_Big_And_Difficult/4096         9160 ns       9159 ns      76297
// BM_Absl_Big_And_Difficult/5000         9738 ns       9738 ns      70140
