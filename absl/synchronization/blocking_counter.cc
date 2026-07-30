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

#include "absl/synchronization/blocking_counter.h"

#include <atomic>

#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/tracing.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

namespace {

// Return whether int *arg is true.
bool IsDone(void *arg) { return *reinterpret_cast<bool *>(arg); }

}  // namespace

BlockingCounter::BlockingCounter(int initial_count)
    : count_(initial_count),
      num_waiting_(0),
      done_{initial_count == 0 ? true : false} { __builtin_trap() /* STUB: not implemented */; }

bool BlockingCounter::DecrementCount() { __builtin_trap() /* STUB: not implemented */; }

void BlockingCounter::Wait() { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
