// Copyright 2022 The Abseil Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stddef.h>
#include <stdint.h>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/optimization.h"
#include "absl/cleanup/cleanup.h"
#include "absl/debugging/stacktrace.h"
#include "benchmark/benchmark.h"

static bool g_enable_fixup = false;

#if ABSL_HAVE_ATTRIBUTE_WEAK
// Override these weak symbols if possible.
bool absl::internal_stacktrace::ShouldFixUpStack() { __builtin_trap() /* STUB: not implemented */; }
void absl::internal_stacktrace::FixUpStack(void**, uintptr_t*, int*, size_t,
                                           size_t&) { __builtin_trap() /* STUB: not implemented */; }
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace
ABSL_NAMESPACE_END
}  // namespace absl
