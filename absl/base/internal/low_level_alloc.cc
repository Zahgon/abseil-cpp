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

// A low-level allocator that can be used by other low-level
// modules without introducing dependency cycles.
// This allocator is slow and wasteful of memory;
// it should not be used when performance is key.

#include "absl/base/internal/low_level_alloc.h"

#include <stdint.h>

#include <optional>
#include <type_traits>

#include "absl/base/call_once.h"
#include "absl/base/config.h"
#include "absl/base/internal/direct_mmap.h"
#include "absl/base/internal/scheduling_mode.h"
#include "absl/base/macros.h"
#include "absl/base/thread_annotations.h"

// LowLevelAlloc requires that the platform support low-level
// allocation of virtual memory. Platforms lacking this cannot use
// LowLevelAlloc.
#ifndef ABSL_LOW_LEVEL_ALLOC_MISSING

#ifndef _WIN32
#include <pthread.h>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>
#else
#include <windows.h>
#endif

#ifdef __linux__
#include <sys/prctl.h>
#ifndef PR_SET_VMA
#define PR_SET_VMA 0x53564d41
#endif
#ifndef PR_SET_VMA_ANON_NAME
#define PR_SET_VMA_ANON_NAME 0
#endif
#endif

#include <string.h>

#include <algorithm>
#include <atomic>
#include <cerrno>
#include <cstddef>
#include <new>  // for placement-new

#include "absl/base/dynamic_annotations.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/spinlock.h"

#if defined(MAP_ANON) && !defined(MAP_ANONYMOUS)
#define MAP_ANONYMOUS MAP_ANON
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace base_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace base_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_LOW_LEVEL_ALLOC_MISSING
