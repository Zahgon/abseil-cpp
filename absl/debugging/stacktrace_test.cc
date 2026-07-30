// Copyright 2023 The Abseil Authors.
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

#include "absl/debugging/stacktrace.h"

#include <stddef.h>
#include <stdint.h>

#include <cerrno>
#include <csignal>
#include <cstring>
#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/errno_saver.h"
#include "absl/base/optimization.h"
#include "absl/types/span.h"

static int g_should_fixup_calls = 0;
static int g_fixup_calls = 0;
static bool g_enable_fixup = false;
static uintptr_t g_last_fixup_frame_address = 0;

#if ABSL_HAVE_ATTRIBUTE_WEAK
bool absl::internal_stacktrace::ShouldFixUpStack() { __builtin_trap() /* STUB: not implemented */; }

void absl::internal_stacktrace::FixUpStack(void**, uintptr_t*, int*, size_t,
                                           size_t&) { __builtin_trap() /* STUB: not implemented */; }
#endif

namespace {

using ::testing::ContainerEq;
using ::testing::Contains;
using ::testing::internal::Cleanup;

struct StackTrace {
  static constexpr int kStackCount = 64;
  int depth;
  void* result[kStackCount];
  int sizes[kStackCount];
};

// This test is currently only known to pass on Linux x86_64/aarch64.
#if defined(__linux__) && (defined(__x86_64__) || defined(__aarch64__))
ABSL_ATTRIBUTE_NOINLINE void Unwind(void* p) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE void HugeFrame() { __builtin_trap() /* STUB: not implemented */; }

TEST(StackTrace, HugeFrame) {
  // Ensure that the unwinder is not confused by very large stack frames.
  HugeFrame();
  ABSL_BLOCK_TAIL_CALL_OPTIMIZATION();
}
#endif

// This is a separate function to avoid inlining.
ABSL_ATTRIBUTE_NOINLINE static void FixupNoFixupEquivalenceNoInline() { __builtin_trap() /* STUB: not implemented */; }

TEST(StackTrace, FixupNoFixupEquivalence) { FixupNoFixupEquivalenceNoInline(); }

TEST(StackTrace, FixupLowStackUsage) {
#if !ABSL_HAVE_ATTRIBUTE_WEAK
  const char* kSkipReason = "Skipping test on MSVC due to weak symbols";
#elif defined(_WIN32)
  // TODO(b/434184677): Add support for fixups on Windows if needed
  const char* kSkipReason =
      "Skipping test on Windows due to lack of support for fixups";
#else
  const char* kSkipReason = nullptr;
#endif

  // This conditional is to avoid an unreachable code warning.
  if (kSkipReason != nullptr) {
    GTEST_SKIP() << kSkipReason;
  }

  const Cleanup restore_state([enable_fixup = g_enable_fixup,
                               fixup_calls = g_fixup_calls,
                               should_fixup_calls = g_should_fixup_calls]() {
    g_enable_fixup = enable_fixup;
    g_fixup_calls = fixup_calls;
    g_should_fixup_calls = should_fixup_calls;
  });

  g_enable_fixup = true;

  // Request a ton of stack frames, regardless of how many are actually used.
  // It's fine to request more frames than we have, since functions preallocate
  // memory before discovering how high the stack really is, and we're really
  // just trying to make sure the preallocations don't overflow the stack.
  //
  // Note that we loop in order to cover all sides of any branches in the
  // implementation that switch allocation behavior (e.g., from stack to heap)
  // and to ensure that no sides allocate too much stack space.
  constexpr size_t kPageSize = 4096;
  for (size_t depth = 2; depth < (1 << 20); depth += depth / 2) {
    const auto stack = std::make_unique<void*[]>(depth);
    const auto frames = std::make_unique<int[]>(depth);

    absl::GetStackFrames(stack.get(), frames.get(), static_cast<int>(depth), 0);
    const void* frame_address = nullptr;
#if ABSL_HAVE_BUILTIN(__builtin_frame_address)
    frame_address = __builtin_frame_address(0);
#endif
    size_t stack_usage =
        reinterpret_cast<uintptr_t>(frame_address) - g_last_fixup_frame_address;
    EXPECT_LT(stack_usage, kPageSize);
  }
}

TEST(StackTrace, CustomUnwinderPerformsFixup) {
#if !ABSL_HAVE_ATTRIBUTE_WEAK
  const char* kSkipReason = "Need weak symbol support";
#elif defined(_WIN32)
  // TODO(b/434184677): Add support for fixups on Windows if needed
  const char* kSkipReason =
      "Skipping test on Windows due to lack of support for fixups";
#else
  const char* kSkipReason = nullptr;
#endif

  // This conditional is to avoid an unreachable code warning.
  if (kSkipReason != nullptr) {
    GTEST_SKIP() << kSkipReason;
  }

  constexpr int kSkip = 1;  // Skip our own frame, whose return PCs won't match
  constexpr auto kStackCount = 1;

  absl::SetStackUnwinder(absl::DefaultStackUnwinder);
  const Cleanup restore_state([enable_fixup = g_enable_fixup,
                               fixup_calls = g_fixup_calls,
                               should_fixup_calls = g_should_fixup_calls]() {
    absl::SetStackUnwinder(nullptr);
    g_enable_fixup = enable_fixup;
    g_fixup_calls = fixup_calls;
    g_should_fixup_calls = should_fixup_calls;
  });

  StackTrace trace;

  g_enable_fixup = true;
  g_should_fixup_calls = 0;
  g_fixup_calls = 0;
  absl::GetStackTrace(trace.result, kSkip, kStackCount);
  EXPECT_GT(g_should_fixup_calls, 0);
  EXPECT_GT(g_fixup_calls, 0);

  g_enable_fixup = true;
  g_should_fixup_calls = 0;
  g_fixup_calls = 0;
  absl::GetStackFrames(trace.result, trace.sizes, kSkip, kStackCount);
  EXPECT_GT(g_should_fixup_calls, 0);
  EXPECT_GT(g_fixup_calls, 0);

  g_enable_fixup = true;
  g_should_fixup_calls = 0;
  g_fixup_calls = 0;
  absl::GetStackTraceWithContext(trace.result, kSkip, kStackCount, nullptr,
                                 nullptr);
  EXPECT_GT(g_should_fixup_calls, 0);
  EXPECT_GT(g_fixup_calls, 0);

  g_enable_fixup = true;
  g_should_fixup_calls = 0;
  g_fixup_calls = 0;
  absl::GetStackFramesWithContext(trace.result, trace.sizes, kSkip, kStackCount,
                                  nullptr, nullptr);
  EXPECT_GT(g_should_fixup_calls, 0);
  EXPECT_GT(g_fixup_calls, 0);
}

// This test is Linux specific.
#if defined(__linux__)
const void* g_return_address = nullptr;
bool g_sigusr2_raised = false;

void SigUsr2Handler(int, siginfo_t*, void* uc) { __builtin_trap() /* STUB: not implemented */; }

void SigUsr1Handler(int, siginfo_t*, void*) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE void RaiseSignal() { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE void TestNestedSignal() { __builtin_trap() /* STUB: not implemented */; }

TEST(StackTrace, NestedSignal) {
  // Verify we can unwind past the nested signal handlers.
  TestNestedSignal();
  EXPECT_TRUE(g_sigusr2_raised);
}
#endif

TEST(StackTrace, NoNullptrInPopulatedRange) {
  constexpr int kMaxDepth = 1024;
  void* results[kMaxDepth];
  int depth = absl::GetStackTrace(results, kMaxDepth, 0);
  for (int i = 0; i < depth; ++i) {
    EXPECT_NE(results[i], nullptr) << "Unexpected nullptr found at index " << i;
  }
}


#if defined(__aarch64__) && defined(__linux__)
static void CorruptedSigStackHandler(int, siginfo_t*, void*) { __builtin_trap() /* STUB: not implemented */; }
#endif

TEST(StackTrace, CorruptedSignalStackFrameSafety) {
#if defined(__aarch64__) && defined(__linux__)
  stack_t sigstk{};
  constexpr size_t kAltstackSize = 1 << 14;
  char altstack[kAltstackSize];
  sigstk.ss_sp = altstack;
  sigstk.ss_size = kAltstackSize;
  sigstk.ss_flags = 0;
  ASSERT_EQ(sigaltstack(&sigstk, nullptr), 0);

  struct sigaction act{}, oldact{};
  act.sa_sigaction = CorruptedSigStackHandler;
  act.sa_flags = SA_SIGINFO | SA_ONSTACK;
  ASSERT_EQ(sigaction(SIGUSR1, &act, &oldact), 0);

  raise(SIGUSR1);

  sigaction(SIGUSR1, &oldact, nullptr);
  stack_t disable_stk{};
  disable_stk.ss_flags = SS_DISABLE;
  sigaltstack(&disable_stk, nullptr);
#endif
}

}  // namespace
