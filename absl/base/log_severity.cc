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

#include "absl/base/log_severity.h"

#include <ostream>

#include "absl/base/attributes.h"
#include "absl/base/config.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

std::ostream& operator<<(std::ostream& os, absl::LogSeverity s) { __builtin_trap() /* STUB: not implemented */; }

std::ostream& operator<<(std::ostream& os, absl::LogSeverityAtLeast s) { __builtin_trap() /* STUB: not implemented */; }

std::ostream& operator<<(std::ostream& os, absl::LogSeverityAtMost s) { __builtin_trap() /* STUB: not implemented */; }
ABSL_NAMESPACE_END
}  // namespace absl
