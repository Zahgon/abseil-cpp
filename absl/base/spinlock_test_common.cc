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

// A bunch of threads repeatedly hash an array of ints protected by a
// spinlock.  If the spinlock is working properly, all elements of the
// array should be equal at the end of the test.

#include <cstdint>
#include <limits>
#include <mutex>  // NOLINT(build/c++11)
#include <random>
#include <thread>  // NOLINT(build/c++11)
#include <type_traits>
#include <vector>

#include "gtest/gtest.h"
#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/low_level_scheduling.h"
#include "absl/base/internal/scheduling_mode.h"
#include "absl/base/internal/spinlock.h"
#include "absl/base/internal/sysinfo.h"
#include "absl/base/macros.h"
#include "absl/synchronization/blocking_counter.h"
#include "absl/synchronization/notification.h"

constexpr uint32_t kNumThreads = 10;
constexpr int32_t kIters = 1000;

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace base_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace base_internal
ABSL_NAMESPACE_END
}  // namespace absl
