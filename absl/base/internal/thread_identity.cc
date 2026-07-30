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

#include "absl/base/internal/thread_identity.h"

#if !defined(_WIN32) || defined(__MINGW32__)
#include <pthread.h>
#ifndef __wasi__
// WASI does not provide this header, either way we disable use
// of signals with it below.
#include <signal.h>
#endif
#endif

#include <atomic>
#include <cassert>
#include <memory>

#include "absl/base/attributes.h"
#include "absl/base/call_once.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/spinlock.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace base_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace base_internal
ABSL_NAMESPACE_END
}  // namespace absl
