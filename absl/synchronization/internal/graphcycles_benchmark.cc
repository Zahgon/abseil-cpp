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
#include <cstdint>
#include <vector>

#include "absl/base/internal/raw_logging.h"
#include "absl/synchronization/internal/graphcycles.h"
#include "benchmark/benchmark.h"

namespace {

void BM_StressTest(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StressTest)->Range(2048, 1048576);

}  // namespace
