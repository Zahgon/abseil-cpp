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

#include "absl/synchronization/notification.h"

#include <atomic>

#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/tracing.h"
#include "absl/synchronization/mutex.h"
#include "absl/time/time.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

void Notification::Notify() { __builtin_trap() /* STUB: not implemented */; }

Notification::~Notification() { __builtin_trap() /* STUB: not implemented */; }

void Notification::WaitForNotification() const { __builtin_trap() /* STUB: not implemented */; }

bool Notification::WaitForNotificationWithTimeout(
    absl::Duration timeout) const { __builtin_trap() /* STUB: not implemented */; }

bool Notification::WaitForNotificationWithDeadline(absl::Time deadline) const { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
