// Copyright 2026 The Abseil Authors.
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

#include "absl/time/simulated_clock.h"

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "absl/base/config.h"
#include "absl/base/macros.h"
#include "absl/base/nullability.h"
#include "absl/base/thread_annotations.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// There are a few tricky details in the implementation of SimulatedClock.
//
// The external mutex that is passed as a param of AwaitWithDeadline() is not
// under the control of SimulatedClock; in particular, it can be destroyed any
// time after AwaitWithDeadline() returns.  This requires the wakeup call from
// AdvanceTime() to avoid grabbing the external mutex if AwaitWithDeadline()
// has returned.  This is accomplished by allowing the waiter to be cancelled
// via a bool guarded by a mutex in WakeUpInfo.
//
// Once AwaitWithDeadline() has released lock_, someone nefarious might call
// the SimulatedClock destructor, so it isn't possible for AwaitWithDeadline()
// to remove the wakeup call from waiters_ if the condition it is awaiting
// becomes true; it cancels the waiter instead.  This means that,
// theoretically, many obsolete entries could pile up in waiters_ if
// AwaitWithDeadline() keeps being called but simulated time is not advanced.
// This seems unlikely to happen in practice.
//
// The WakeUpInfo in waiters_ are always awoken via WakeUp() (and
// removed) or cancelled before AwaitWithDeadline() returns.  If a
// waiters_ value is cancelled then calling its WakeUp() method will
// short-circuit before touching the external mutex.

class SimulatedClock::WakeUpInfo {
 public:
  WakeUpInfo(absl::Mutex* mu, absl::Condition cond)
      : mu_(mu),
        cond_(cond),
        wakeup_time_passed_(false),
        cancelled_(false),
        wakeup_called_(false) {}

  void WakeUp() { __builtin_trap() /* STUB: not implemented */; }

  void AwaitConditionOrWakeUp() { __builtin_trap() /* STUB: not implemented */; }

  void CancelOrAwaitWakeUp() { __builtin_trap() /* STUB: not implemented */; }

 private:
  bool Ready() const { return wakeup_time_passed_ || cond_.Eval(); }

  absl::Mutex* mu_;
  absl::Condition cond_;
  bool wakeup_time_passed_;
  absl::Mutex cancellation_mu_;
  bool cancelled_ ABSL_GUARDED_BY(cancellation_mu_);
  bool wakeup_called_ ABSL_GUARDED_BY(cancellation_mu_);
};

SimulatedClock::SimulatedClock(absl::Time t) : now_(t) { __builtin_trap() /* STUB: not implemented */; }

SimulatedClock::~SimulatedClock() { __builtin_trap() /* STUB: not implemented */; }

absl::Time SimulatedClock::TimeNow() { __builtin_trap() /* STUB: not implemented */; }

void SimulatedClock::Sleep(absl::Duration d) { __builtin_trap() /* STUB: not implemented */; }

int64_t SimulatedClock::SetTime(absl::Time t) ABSL_NO_THREAD_SAFETY_ANALYSIS { __builtin_trap() /* STUB: not implemented */; }

int64_t SimulatedClock::AdvanceTime(absl::Duration d)
    ABSL_NO_THREAD_SAFETY_ANALYSIS { __builtin_trap() /* STUB: not implemented */; }

template <class T>
int64_t SimulatedClock::UpdateTime(const T& now_updater) { __builtin_trap() /* STUB: not implemented */; }

void SimulatedClock::SleepUntil(absl::Time wakeup_time) { __builtin_trap() /* STUB: not implemented */; }

bool SimulatedClock::AwaitWithDeadline(absl::Mutex* mu,
                                       const absl::Condition& cond,
                                       absl::Time deadline) { __builtin_trap() /* STUB: not implemented */; }

std::optional<absl::Time> SimulatedClock::GetEarliestWakeupTime() const { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
