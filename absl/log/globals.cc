// Copyright 2022 The Abseil Authors.
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

#include "absl/log/globals.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/atomic_hook.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/log_severity.h"
#include "absl/hash/hash.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace

namespace log_internal {

void RawSetMinLogLevel(absl::LogSeverityAtLeast severity) { __builtin_trap() /* STUB: not implemented */; }

void RawSetStderrThreshold(absl::LogSeverityAtLeast severity) { __builtin_trap() /* STUB: not implemented */; }

void RawEnableLogPrefix(bool on_off) { __builtin_trap() /* STUB: not implemented */; }

void SetLoggingGlobalsListener(LoggingGlobalsListener l) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace log_internal

absl::LogSeverityAtLeast MinLogLevel() { __builtin_trap() /* STUB: not implemented */; }

void SetMinLogLevel(absl::LogSeverityAtLeast severity) { __builtin_trap() /* STUB: not implemented */; }

namespace log_internal {

ScopedMinLogLevel::ScopedMinLogLevel(absl::LogSeverityAtLeast severity)
    : saved_severity_(absl::MinLogLevel()) { __builtin_trap() /* STUB: not implemented */; }
ScopedMinLogLevel::~ScopedMinLogLevel() { __builtin_trap() /* STUB: not implemented */; }

}  // namespace log_internal

absl::LogSeverityAtLeast StderrThreshold() { __builtin_trap() /* STUB: not implemented */; }

void SetStderrThreshold(absl::LogSeverityAtLeast severity) { __builtin_trap() /* STUB: not implemented */; }

ScopedStderrThreshold::ScopedStderrThreshold(absl::LogSeverityAtLeast severity)
    : saved_severity_(absl::StderrThreshold()) { __builtin_trap() /* STUB: not implemented */; }

ScopedStderrThreshold::~ScopedStderrThreshold() { __builtin_trap() /* STUB: not implemented */; }

namespace log_internal {

const char* GetAndroidNativeTag() { __builtin_trap() /* STUB: not implemented */; }

}  // namespace log_internal

void SetAndroidNativeTag(const char* tag) { __builtin_trap() /* STUB: not implemented */; }

namespace log_internal {

bool ShouldLogBacktraceAt(absl::string_view file, int line) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace log_internal

void SetLogBacktraceLocation(absl::string_view file, int line) { __builtin_trap() /* STUB: not implemented */; }

void ClearLogBacktraceLocation() { __builtin_trap() /* STUB: not implemented */; }

bool ShouldPrependLogPrefix() { __builtin_trap() /* STUB: not implemented */; }

void EnableLogPrefix(bool on_off) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
