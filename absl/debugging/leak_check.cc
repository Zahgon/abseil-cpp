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
//
// Wrappers around lsan_interface functions.
//
// These are always-available run-time functions manipulating the LeakSanitizer,
// even when the lsan_interface (and LeakSanitizer) is not available. When
// LeakSanitizer is not linked in, these functions become no-op stubs.

#include "absl/debugging/leak_check.h"

#include "absl/base/attributes.h"
#include "absl/base/config.h"

#if defined(ABSL_HAVE_LEAK_SANITIZER)

#include <sanitizer/lsan_interface.h>

#if ABSL_HAVE_ATTRIBUTE_WEAK
extern "C" ABSL_ATTRIBUTE_WEAK int __lsan_is_turned_off() { __builtin_trap() /* STUB: not implemented */; }
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
bool HaveLeakSanitizer() { __builtin_trap() /* STUB: not implemented */; }

#if ABSL_HAVE_ATTRIBUTE_WEAK
bool LeakCheckerIsActive() { __builtin_trap() /* STUB: not implemented */; }
#else
bool LeakCheckerIsActive() { __builtin_trap() /* STUB: not implemented */; }
#endif

bool FindAndReportLeaks() { __builtin_trap() /* STUB: not implemented */; }
void DoIgnoreLeak(const void* ptr) { __builtin_trap() /* STUB: not implemented */; }
void RegisterLivePointers(const void* ptr, size_t size) { __builtin_trap() /* STUB: not implemented */; }
void UnRegisterLivePointers(const void* ptr, size_t size) { __builtin_trap() /* STUB: not implemented */; }
LeakCheckDisabler::LeakCheckDisabler() { __builtin_trap() /* STUB: not implemented */; }
LeakCheckDisabler::~LeakCheckDisabler() { __builtin_trap() /* STUB: not implemented */; }
ABSL_NAMESPACE_END
}  // namespace absl

#else  // defined(ABSL_HAVE_LEAK_SANITIZER)

namespace absl {
ABSL_NAMESPACE_BEGIN
bool HaveLeakSanitizer() { __builtin_trap() /* STUB: not implemented */; }
bool LeakCheckerIsActive() { __builtin_trap() /* STUB: not implemented */; }
void DoIgnoreLeak(const void*) { __builtin_trap() /* STUB: not implemented */; }
void RegisterLivePointers(const void*, size_t) { __builtin_trap() /* STUB: not implemented */; }
void UnRegisterLivePointers(const void*, size_t) { __builtin_trap() /* STUB: not implemented */; }
LeakCheckDisabler::LeakCheckDisabler() = default;
LeakCheckDisabler::~LeakCheckDisabler() = default;
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // defined(ABSL_HAVE_LEAK_SANITIZER)
