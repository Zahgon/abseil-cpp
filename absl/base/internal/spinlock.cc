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

#include "absl/base/internal/spinlock.h"

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <limits>

#include "absl/base/attributes.h"
#include "absl/base/call_once.h"
#include "absl/base/config.h"
#include "absl/base/internal/atomic_hook.h"
#include "absl/base/internal/cycleclock.h"
#include "absl/base/internal/scheduling_mode.h"
#include "absl/base/internal/spinlock_wait.h"
#include "absl/base/internal/sysinfo.h" /* For NumCPUs() */
#include "absl/base/internal/tsan_mutex_interface.h"

// Description of lock-word:
//  31..00: [............................3][2][1][0]
//
//     [0]: kSpinLockHeld
//     [1]: kSpinLockCooperative
//     [2]: kSpinLockDisabledScheduling
// [31..3]: ONLY kSpinLockSleeper OR
//          Wait time in cycles >> PROFILE_TIMESTAMP_SHIFT
//
// Detailed descriptions:
//
// Bit [0]: The lock is considered held iff kSpinLockHeld is set.
//
// Bit [1]: Eligible waiters (e.g. Fibers) may co-operatively reschedule when
//          contended iff kSpinLockCooperative is set.
//
// Bit [2]: This bit is exclusive from bit [1].  It is used only by a
//          non-cooperative lock.  When set, indicates that scheduling was
//          successfully disabled when the lock was acquired.  May be unset,
//          even if non-cooperative, if a ThreadIdentity did not yet exist at
//          time of acquisition.
//
// Bit [3]: If this is the only upper bit ([31..3]) set then this lock was
//          acquired without contention, however, at least one waiter exists.
//
//          Otherwise, bits [31..3] represent the time spent by the current lock
//          holder to acquire the lock.  There may be outstanding waiter(s).

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace base_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace base_internal
ABSL_NAMESPACE_END
}  // namespace absl
