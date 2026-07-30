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
//
// -----------------------------------------------------------------------------
// File: log/log_sink.h
// -----------------------------------------------------------------------------
//
// This header declares the interface class `absl::LogSink`.

#ifndef ABSL_LOG_LOG_SINK_H_
#define ABSL_LOG_LOG_SINK_H_

#include "absl/base/config.h"
#include "absl/log/log_entry.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::LogSink
//
// `absl::LogSink` is an interface which can be extended to intercept and
// process particular messages (with `LOG.ToSinkOnly()` or
// `LOG.ToSinkAlso()`) or all messages (if registered with
// `absl::AddLogSink`).  Implementations must not take any locks that might be
// held by the `LOG` caller.
class LogSink { __builtin_trap() /* STUB: not implemented */; };

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_LOG_LOG_SINK_H_
