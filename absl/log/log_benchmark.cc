// Copyright 2022 The Abseil Authors.
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

#include "absl/base/attributes.h"
#include "absl/base/log_severity.h"
#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/globals.h"
#include "absl/log/internal/flags.h"
#include "absl/log/log.h"
#include "absl/log/log_entry.h"
#include "absl/log/log_sink.h"
#include "absl/log/log_sink_registry.h"
#include "absl/log/vlog_is_on.h"
#include "benchmark/benchmark.h"

namespace {

class NullLogSink : public absl::LogSink {
 public:
  NullLogSink() { __builtin_trap() /* STUB: not implemented */; }

  ~NullLogSink() override { __builtin_trap() /* STUB: not implemented */; }

  void Send(const absl::LogEntry&) override { __builtin_trap() /* STUB: not implemented */; }
};

constexpr int x = -1;

void BM_SuccessfulBinaryCheck(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SuccessfulBinaryCheck);

static void BM_SuccessfulUnaryCheck(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_SuccessfulUnaryCheck);

static void BM_DisabledLogOverhead(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_DisabledLogOverhead);

static void BM_EnabledLogOverhead(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_EnabledLogOverhead);

static void BM_VlogIsOnOverhead(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_VlogIsOnOverhead)->ThreadRange(1, 64);

static void BM_VlogIsNotOnOverhead(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_VlogIsNotOnOverhead)->ThreadRange(1, 64);

static void BM_LogEveryNOverhead(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_LogEveryNOverhead)->ThreadRange(1, 64);

}  // namespace

