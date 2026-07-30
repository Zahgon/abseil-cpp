// Copyright 2017 Google Inc. All Rights Reserved.
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

#include "absl/random/internal/nanobenchmark.h"

#include <sys/types.h>

#include <algorithm>  // sort
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>  // memcpy
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/random/internal/platform.h"
#include "absl/random/internal/randen_engine.h"

// OS
#if defined(_WIN32) || defined(_WIN64)
#define ABSL_OS_WIN
#include <windows.h>  // NOLINT

#elif defined(__ANDROID__)
#define ABSL_OS_ANDROID

#elif defined(__linux__)
#define ABSL_OS_LINUX
#include <sched.h>        // NOLINT
#include <sys/syscall.h>  // NOLINT
#endif

#if defined(ABSL_ARCH_X86_64) && !defined(ABSL_OS_WIN)
#include <cpuid.h>  // NOLINT
#endif

// __ppc_get_timebase_freq
#if defined(ABSL_ARCH_PPC)
#include <sys/platform/ppc.h>  // NOLINT
#endif

// clock_gettime
#if defined(ABSL_ARCH_ARM) || defined(ABSL_ARCH_AARCH64)
#include <time.h>  // NOLINT
#endif

// ABSL_RANDOM_INTERNAL_ATTRIBUTE_NEVER_INLINE prevents inlining of the method.
#if ABSL_HAVE_ATTRIBUTE(noinline) || (defined(__GNUC__) && !defined(__clang__))
#define ABSL_RANDOM_INTERNAL_ATTRIBUTE_NEVER_INLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define ABSL_RANDOM_INTERNAL_ATTRIBUTE_NEVER_INLINE __declspec(noinline)
#else
#define ABSL_RANDOM_INTERNAL_ATTRIBUTE_NEVER_INLINE
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace random_internal_nanobenchmark { __builtin_trap() /* STUB: not implemented */; }  // namespace random_internal_nanobenchmark
ABSL_NAMESPACE_END
}  // namespace absl
