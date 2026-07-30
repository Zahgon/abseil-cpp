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

#include "absl/container/internal/hashtablez_sampler.h"

#include <algorithm>
#include <atomic>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/per_thread_tls.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/macros.h"
#include "absl/base/no_destructor.h"
#include "absl/base/optimization.h"
#include "absl/debugging/stacktrace.h"
#include "absl/memory/memory.h"
#include "absl/profiling/internal/exponential_biased.h"
#include "absl/profiling/internal/sample_recorder.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/clock.h"
#include "absl/utility/utility.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace container_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace container_internal
ABSL_NAMESPACE_END
}  // namespace absl
