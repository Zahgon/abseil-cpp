//
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

#include "absl/log/internal/log_message.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <ios>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/strerror.h"
#include "absl/base/internal/sysinfo.h"
#include "absl/base/log_severity.h"
#include "absl/base/nullability.h"
#include "absl/container/inlined_vector.h"
#include "absl/debugging/internal/examine_stack.h"
#include "absl/log/globals.h"
#include "absl/log/internal/append_truncated.h"
#include "absl/log/internal/globals.h"
#include "absl/log/internal/log_format.h"
#include "absl/log/internal/log_sink_set.h"
#include "absl/log/internal/nullguard.h"
#include "absl/log/internal/proto.h"
#include "absl/log/internal/structured_proto.h"
#include "absl/log/log_entry.h"
#include "absl/log/log_sink.h"
#include "absl/log/log_sink_registry.h"
#include "absl/strings/internal/utf8.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "absl/types/span.h"

extern "C" ABSL_ATTRIBUTE_WEAK void ABSL_INTERNAL_C_SYMBOL(
    AbslInternalOnFatalLogMessage)(const absl::LogEntry&) {
  // Default - Do nothing
}

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace log_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace log_internal

ABSL_NAMESPACE_END
}  // namespace absl
