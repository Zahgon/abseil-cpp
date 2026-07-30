//
// Copyright 2019 The Abseil Authors.
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
#include "absl/flags/usage.h"

#include <stdlib.h>

#include <string>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/const_init.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/thread_annotations.h"
#include "absl/flags/internal/usage.h"
#include "absl/strings/string_view.h"
#include "absl/synchronization/mutex.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace flags_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace flags_internal

// --------------------------------------------------------------------
// Sets the "usage" message to be used by help reporting routines.
void SetProgramUsageMessage(absl::string_view new_usage_message) { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------
// Returns the usage message set by SetProgramUsageMessage().
// Note: We able to return string_view here only because calling
// SetProgramUsageMessage twice is prohibited.
absl::string_view ProgramUsageMessage() { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
