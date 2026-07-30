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

#include "absl/base/internal/sysinfo.h"

#include "absl/base/attributes.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef __linux__
#include <sys/syscall.h>
#endif

#if defined(__APPLE__) || defined(__FreeBSD__)
#include <sys/sysctl.h>
#endif

#ifdef __FreeBSD__
#include <pthread_np.h>
#endif

#ifdef __NetBSD__
#include <lwp.h>
#endif

#if defined(__myriad2__)
#include <rtems.h>
#endif

#if defined(__Fuchsia__)
#include <zircon/process.h>
#endif

#include <string.h>

#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <thread>  // NOLINT(build/c++11)
#include <utility>
#include <vector>

#include "absl/base/call_once.h"
#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/spinlock.h"
#include "absl/base/internal/unscaledcycleclock.h"
#include "absl/base/thread_annotations.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace base_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace base_internal
ABSL_NAMESPACE_END
}  // namespace absl
