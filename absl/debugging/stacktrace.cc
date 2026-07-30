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

// Produce stack trace.
//
// There are three different ways we can try to get the stack trace:
//
// 1) Our hand-coded stack-unwinder.  This depends on a certain stack
//    layout, which is used by gcc (and those systems using a
//    gcc-compatible ABI) on x86 systems, at least since gcc 2.95.
//    It uses the frame pointer to do its work.
//
// 2) The libunwind library.  This is still in development, and as a
//    separate library adds a new dependency, but doesn't need a frame
//    pointer.  It also doesn't call malloc.
//
// 3) The gdb unwinder -- also the one used by the c++ exception code.
//    It's obviously well-tested, but has a fatal flaw: it can call
//    malloc() from the unwinder.  This is a problem because we're
//    trying to use the unwinder to instrument malloc().
//
// Note: if you add a new implementation here, make sure it works
// correctly when absl::GetStackTrace() is called with max_depth == 0.
// Some code may do that.

#include "absl/debugging/stacktrace.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <algorithm>
#include <atomic>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/optimization.h"
#include "absl/base/port.h"
#include "absl/debugging/internal/stacktrace_config.h"

#if defined(ABSL_STACKTRACE_INL_HEADER)
#include ABSL_STACKTRACE_INL_HEADER
#else
#error Cannot calculate stack trace: will need to write for your environment

#include "absl/debugging/internal/stacktrace_aarch64-inl.inc"
#include "absl/debugging/internal/stacktrace_arm-inl.inc"
#include "absl/debugging/internal/stacktrace_emscripten-inl.inc"
#include "absl/debugging/internal/stacktrace_generic-inl.inc"
#include "absl/debugging/internal/stacktrace_powerpc-inl.inc"
#include "absl/debugging/internal/stacktrace_riscv-inl.inc"
#include "absl/debugging/internal/stacktrace_unimplemented-inl.inc"
#include "absl/debugging/internal/stacktrace_win32-inl.inc"
#include "absl/debugging/internal/stacktrace_x86-inl.inc"
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace { __builtin_trap() /* STUB: not implemented */; }  // anonymous namespace

ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int GetStackFrames(
    void** result, int* sizes, int max_depth, int skip_count) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int
internal_stacktrace::GetStackTraceNoFixup(void** result, int max_depth,
                                          int skip_count) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int
GetStackFramesWithContext(void** result, int* sizes, int max_depth,
                          int skip_count, const void* uc,
                          int* min_dropped_frames) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int GetStackTrace(
    void** result, int max_depth, int skip_count) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int
GetStackTraceWithContext(void** result, int max_depth, int skip_count,
                         const void* uc, int* min_dropped_frames) { __builtin_trap() /* STUB: not implemented */; }

void SetStackUnwinder(Unwinder w) { __builtin_trap() /* STUB: not implemented */; }

int DefaultStackUnwinder(void** pcs, int* sizes, int depth, int skip,
                         const void* uc, int* min_dropped_frames) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_WEAK bool internal_stacktrace::ShouldFixUpStack() { __builtin_trap() /* STUB: not implemented */; }

// Fixes up the stack trace of the current thread, in the first `depth` frames
// of each buffer. The buffers need to be larger than `depth`, to accommodate
// any newly inserted elements. `depth` is updated to reflect the new number of
// elements valid across all the buffers. (It is therefore recommended that all
// buffer sizes be equal.)
//
// The `frames` and `sizes` parameters denote the bounds of the stack frame
// corresponding to each instruction pointer in the `pcs`.
// Any elements inside these buffers may be zero or null, in which case that
// information is assumed to be absent/unavailable.
ABSL_ATTRIBUTE_WEAK void internal_stacktrace::FixUpStack(void**, uintptr_t*,
                                                         int*, size_t,
                                                         size_t&) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
