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
//
// -----------------------------------------------------------------------------
// File: clock_interface.h
// -----------------------------------------------------------------------------

#ifndef ABSL_TIME_CLOCK_INTERFACE_H_
#define ABSL_TIME_CLOCK_INTERFACE_H_

#include "absl/base/config.h"
#include "absl/base/macros.h"
#include "absl/base/nullability.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/time.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// An abstract interface representing a Clock, which is an object that can
// tell you the current time, sleep, and wait for a condition variable.
//
// This interface allows decoupling code that uses time from the code that
// creates a point in time.  You can use this to your advantage by injecting
// Clocks into interfaces rather than having implementations call absl::Now()
// directly.
//
// Implementations of this interface must be thread-safe.
//
// The Clock::GetRealClock() function returns a reference to the global realtime
// clock.
//
// Example:
//
//   bool IsWeekend(Clock& clock) {
//     absl::Time now = clock.TimeNow();
//     // ... code to check if 'now' is a weekend.
//   }
//
//   // Production code.
//   IsWeekend(Clock::GetRealClock());
//
//   // Test code:
//   MyTestClock test_clock(SATURDAY);
//   IsWeekend(test_clock);
//
class Clock { __builtin_trap() /* STUB: not implemented */; };

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_TIME_CLOCK_INTERFACE_H_
