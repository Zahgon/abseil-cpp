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

#include <stdint.h>

#include <new>

// This file is a no-op if the required LowLevelAlloc support is missing.
#include "absl/base/internal/low_level_alloc.h"
#include "absl/synchronization/internal/waiter.h"
#ifndef ABSL_LOW_LEVEL_ALLOC_MISSING

#include <string.h>

#include "absl/base/attributes.h"
#include "absl/base/internal/spinlock.h"
#include "absl/base/internal/thread_identity.h"
#include "absl/synchronization/internal/per_thread_sem.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace synchronization_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace synchronization_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_LOW_LEVEL_ALLOC_MISSING
