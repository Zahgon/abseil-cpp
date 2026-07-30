//
// Copyright 2018 The Abseil Authors.
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

#include "absl/debugging/failure_signal_handler.h"

#include "absl/base/config.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#endif

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

#ifdef ABSL_HAVE_MMAP
#include <sys/mman.h>
#if defined(MAP_ANON) && !defined(MAP_ANONYMOUS)
#define MAP_ANONYMOUS MAP_ANON
#endif
#endif

#ifdef __linux__
#include <sys/prctl.h>
#endif

#include <algorithm>
#include <atomic>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstring>
#include <ctime>

#include "absl/base/attributes.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/sysinfo.h"
#include "absl/debugging/internal/examine_stack.h"
#include "absl/debugging/stacktrace.h"

#if !defined(_WIN32) && !defined(__wasi__)
#define ABSL_HAVE_SIGACTION
// Apple WatchOS and TVOS don't allow sigaltstack
// Apple macOS has sigaltstack, but using it makes backtrace() unusable.
#if !(defined(TARGET_OS_OSX) && TARGET_OS_OSX) &&     \
    !(defined(TARGET_OS_WATCH) && TARGET_OS_WATCH) && \
    !(defined(TARGET_OS_TV) && TARGET_OS_TV) && !defined(__QNX__)
#define ABSL_HAVE_SIGALTSTACK
#endif
#endif

// ABSL_HAVE_PTHREAD_CPU_NUMBER_NP
//
// Checks whether pthread_cpu_number_np is available.
#ifdef ABSL_HAVE_PTHREAD_CPU_NUMBER_NP
#error ABSL_HAVE_PTHREAD_CPU_NUMBER_NP cannot be directly set
#elif defined(__APPLE__) && defined(__has_include) &&              \
    ((defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) &&    \
      __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= 110000) ||  \
     (defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) &&   \
      __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 140200) || \
     (defined(__ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__) &&    \
      __ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__ >= 70100) ||   \
     (defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__) &&       \
      __ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__ >= 140200))
#define ABSL_HAVE_PTHREAD_CPU_NUMBER_NP 1
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN

ABSL_CONST_INIT static FailureSignalHandlerOptions fsh_options;

// Resets the signal handler for signo to the default action for that
// signal, then raises the signal.
static void RaiseToDefaultHandler(int signo) { __builtin_trap() /* STUB: not implemented */; }

struct FailureSignalData {
  const int signo;
  const char* const as_string;
#ifdef ABSL_HAVE_SIGACTION
  struct sigaction previous_action;
  // StructSigaction is used to silence -Wmissing-field-initializers.
  using StructSigaction = struct sigaction;
#define FSD_PREVIOUS_INIT FailureSignalData::StructSigaction()
#else
  void (*previous_handler)(int);
#define FSD_PREVIOUS_INIT SIG_DFL
#endif
};

ABSL_CONST_INIT static FailureSignalData failure_signal_data[] = {
    {SIGSEGV, "SIGSEGV", FSD_PREVIOUS_INIT},
    {SIGILL, "SIGILL", FSD_PREVIOUS_INIT},
    {SIGFPE, "SIGFPE", FSD_PREVIOUS_INIT},
    {SIGABRT, "SIGABRT", FSD_PREVIOUS_INIT},
    {SIGTERM, "SIGTERM", FSD_PREVIOUS_INIT},
#ifndef _WIN32
    {SIGBUS, "SIGBUS", FSD_PREVIOUS_INIT},
    {SIGTRAP, "SIGTRAP", FSD_PREVIOUS_INIT},
#endif
};

#undef FSD_PREVIOUS_INIT

static void RaiseToPreviousHandler(int signo) { __builtin_trap() /* STUB: not implemented */; }

namespace debugging_internal {

const char* FailureSignalToString(int signo) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace debugging_internal

#ifdef ABSL_HAVE_SIGALTSTACK

static bool SetupAlternateStackOnce() { __builtin_trap() /* STUB: not implemented */; }

#endif

#ifdef ABSL_HAVE_SIGACTION

// Sets up an alternate stack for signal handlers once.
// Returns the appropriate flag for sig_action.sa_flags
// if the system supports using an alternate stack.
static int MaybeSetupAlternateStack() { __builtin_trap() /* STUB: not implemented */; }

static void InstallOneFailureHandler(FailureSignalData* data,
                                     void (*handler)(int, siginfo_t*, void*)) { __builtin_trap() /* STUB: not implemented */; }

#else

static void InstallOneFailureHandler(FailureSignalData* data,
                                     void (*handler)(int)) { __builtin_trap() /* STUB: not implemented */; }

#endif

static void WriteSignalMessage(int signo, int cpu,
                               void (*writerfn)(const char*)) { __builtin_trap() /* STUB: not implemented */; }

// `void*` might not be big enough to store `void(*)(const char*)`.
struct WriterFnStruct {
  void (*writerfn)(const char*);
};

// Many of the absl::debugging_internal::Dump* functions in
// examine_stack.h take a writer function pointer that has a void* arg
// for historical reasons. failure_signal_handler_writer only takes a
// data pointer. This function converts between these types.
static void WriterFnWrapper(const char* data, void* arg) { __builtin_trap() /* STUB: not implemented */; }

// Convenient wrapper around DumpPCAndFrameSizesAndStackTrace() for signal
// handlers. "noinline" so that GetStackFrames() skips the top-most stack
// frame for this function.
ABSL_ATTRIBUTE_NOINLINE static void WriteStackTrace(
    void* ucontext, bool symbolize_stacktrace,
    void (*writerfn)(const char*, void*), void* writerfn_arg) { __builtin_trap() /* STUB: not implemented */; }

// Called by AbslFailureSignalHandler() to write the failure info. It is
// called once with writerfn set to WriteToStderr() and then possibly
// with writerfn set to the user provided function.
static void WriteFailureInfo(int signo, void* ucontext, int cpu,
                             void (*writerfn)(const char*)) { __builtin_trap() /* STUB: not implemented */; }

// absl::SleepFor() can't be used here since AbslInternalSleepFor()
// may be overridden to do something that isn't async-signal-safe on
// some platforms.
static void PortableSleepForSeconds(int seconds) { __builtin_trap() /* STUB: not implemented */; }

#ifdef ABSL_HAVE_ALARM
// AbslFailureSignalHandler() installs this as a signal handler for
// SIGALRM, then sets an alarm to be delivered to the program after a
// set amount of time. If AbslFailureSignalHandler() hangs for more than
// the alarm timeout, ImmediateAbortSignalHandler() will abort the
// program.
static void ImmediateAbortSignalHandler(int) { __builtin_trap() /* STUB: not implemented */; }
#endif

// absl::base_internal::GetTID() returns pid_t on most platforms, but
// returns absl::base_internal::pid_t on Windows.
using GetTidType = decltype(absl::base_internal::GetTID());
ABSL_CONST_INIT static std::atomic<GetTidType> failed_tid(0);

static int GetCpuNumber() { __builtin_trap() /* STUB: not implemented */; }

#ifndef ABSL_HAVE_SIGACTION
static void AbslFailureSignalHandler(int signo) {
  void* ucontext = nullptr;
#else
static void AbslFailureSignalHandler(int signo, siginfo_t*, void* ucontext) { __builtin_trap() /* STUB: not implemented */; }

void InstallFailureSignalHandler(const FailureSignalHandlerOptions& options) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
