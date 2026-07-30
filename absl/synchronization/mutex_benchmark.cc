// Copyright 2017 The Abseil Authors.
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

#include <cstdint>
#include <mutex>  // NOLINT(build/c++11)
#include <vector>

#include "absl/base/config.h"
#include "absl/base/internal/cycleclock.h"
#include "absl/base/internal/spinlock.h"
#include "absl/base/no_destructor.h"
#include "absl/synchronization/blocking_counter.h"
#include "absl/synchronization/internal/thread_pool.h"
#include "absl/synchronization/mutex.h"
#include "benchmark/benchmark.h"

namespace {

void BM_Mutex(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Mutex)->UseRealTime()->Threads(1)->ThreadPerCpu();

void BM_ReaderLock(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_ReaderLock)->UseRealTime()->Threads(1)->ThreadPerCpu();

void BM_TryLock(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_TryLock);

void BM_ReaderTryLock(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_ReaderTryLock)->UseRealTime()->Threads(1)->ThreadPerCpu();

static void DelayNs(int64_t ns, int* data) { __builtin_trap() /* STUB: not implemented */; }

// RAII object to change the Mutex priority of the running thread.
class ScopedThreadMutexPriority {
 public:
  explicit ScopedThreadMutexPriority(int priority) { __builtin_trap() /* STUB: not implemented */; }
  ~ScopedThreadMutexPriority() { __builtin_trap() /* STUB: not implemented */; }
};

void BM_MutexEnqueue(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

BENCHMARK(BM_MutexEnqueue)
    ->Threads(4)
    ->Threads(64)
    ->Threads(128)
    ->Threads(512)
    ->ArgName("multiple_priorities")
    ->Arg(false)
    ->Arg(true);

template <typename MutexType>
void BM_Contended(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void SetupBenchmarkArgs(benchmark::internal::Benchmark* bm,
                        bool do_test_priorities) { __builtin_trap() /* STUB: not implemented */; }

BENCHMARK_TEMPLATE(BM_Contended, absl::Mutex)
    ->Apply([](benchmark::internal::Benchmark* bm) {
      SetupBenchmarkArgs(bm, /*do_test_priorities=*/true);
    });

BENCHMARK_TEMPLATE(BM_Contended, absl::base_internal::SpinLock)
    ->Apply([](benchmark::internal::Benchmark* bm) {
      SetupBenchmarkArgs(bm, /*do_test_priorities=*/false);
    });

BENCHMARK_TEMPLATE(BM_Contended, std::mutex)
    ->Apply([](benchmark::internal::Benchmark* bm) {
      SetupBenchmarkArgs(bm, /*do_test_priorities=*/false);
    });

// Measure the overhead of conditions on mutex release (when they must be
// evaluated).  Mutex has (some) support for equivalence classes allowing
// Conditions with the same function/argument to potentially not be multiply
// evaluated.
//
// num_classes==0 is used for the special case of every waiter being distinct.
void BM_ConditionWaiters(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

// Some configurations have higher thread limits than others.
#if defined(__linux__) && !defined(ABSL_HAVE_THREAD_SANITIZER)
constexpr int kMaxConditionWaiters = 8192;
#else
constexpr int kMaxConditionWaiters = 1024;
#endif
BENCHMARK(BM_ConditionWaiters)->RangePair(0, 2, 1, kMaxConditionWaiters);

}  // namespace
