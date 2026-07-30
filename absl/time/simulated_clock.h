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
// File: simulated_clock.h
// -----------------------------------------------------------------------------

#ifndef ABSL_TIME_SIMULATED_CLOCK_H_
#define ABSL_TIME_SIMULATED_CLOCK_H_

#include <cstdint>
#include <map>
#include <memory>
#include <optional>

#include "absl/base/config.h"
#include "absl/base/macros.h"
#include "absl/base/nullability.h"
#include "absl/base/thread_annotations.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/clock.h"
#include "absl/time/clock_interface.h"
#include "absl/time/time.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// A simulated clock is a concrete Clock implementation that does not "tick"
// on its own.  Time is advanced by explicit calls to the AdvanceTime() or
// SetTime() functions.
//
// Example:
//   absl::SimulatedClock sim_clock;
//   absl::Time now = sim_clock.TimeNow();
//   // now == absl::UnixEpoch()
//
//   now = sim_clock.TimeNow();
//   // now == absl::UnixEpoch() (still)
//
//   sim_clock.AdvanceTime(absl::Seconds(3));
//   now = sim_clock.TimeNow();
//   // now == absl::UnixEpoch() + absl::Seconds(3)
//
// This class is thread-safe.
class SimulatedClock : public Clock { __builtin_trap() /* STUB: not implemented */; };

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_TIME_SIMULATED_CLOCK_H_
