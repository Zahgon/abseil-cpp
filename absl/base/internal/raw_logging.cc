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

#include "absl/base/internal/raw_logging.h"

#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten/console.h>
#endif

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/atomic_hook.h"
#include "absl/base/internal/errno_saver.h"
#include "absl/base/log_severity.h"

// We know how to perform low-level writes to stderr in POSIX and Windows.  For
// these platforms, we define the token ABSL_LOW_LEVEL_WRITE_SUPPORTED.
// Much of raw_logging.cc becomes a no-op when we can't output messages,
// although a FATAL ABSL_RAW_LOG message will still abort the process.

// ABSL_HAVE_POSIX_WRITE is defined when the platform provides posix write()
// (as from unistd.h)
//
// This preprocessor token is also defined in raw_io.cc.  If you need to copy
// this, consider moving both to config.h instead.
#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) ||     \
    defined(__hexagon__) || defined(__Fuchsia__) || defined(__OpenBSD__) || \
    defined(__EMSCRIPTEN__) || defined(__ASYLO__)

#include <unistd.h>

#define ABSL_HAVE_POSIX_WRITE 1
#define ABSL_LOW_LEVEL_WRITE_SUPPORTED 1
#else
#undef ABSL_HAVE_POSIX_WRITE
#endif

// ABSL_HAVE_SYSCALL_WRITE is defined when the platform provides the syscall
//   syscall(SYS_write, /*int*/ fd, /*char* */ buf, /*size_t*/ len);
// for low level operations that want to avoid libc.
#if (defined(__linux__) || defined(__FreeBSD__)) && !defined(__ANDROID__)
#include <sys/syscall.h>
#define ABSL_HAVE_SYSCALL_WRITE 1
#define ABSL_LOW_LEVEL_WRITE_SUPPORTED 1
#else
#undef ABSL_HAVE_SYSCALL_WRITE
#endif

#ifdef _WIN32
#include <io.h>

#define ABSL_HAVE_RAW_IO 1
#define ABSL_LOW_LEVEL_WRITE_SUPPORTED 1
#else
#undef ABSL_HAVE_RAW_IO
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace raw_log_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace raw_log_internal
ABSL_NAMESPACE_END
}  // namespace absl
