//
//  Copyright 2019 The Abseil Authors.
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

#include "absl/flags/usage_config.h"

#include <functional>
#include <iostream>
#include <string>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/const_init.h"
#include "absl/base/no_destructor.h"
#include "absl/base/thread_annotations.h"
#include "absl/flags/internal/path_util.h"
#include "absl/flags/internal/program_name.h"
#include "absl/strings/match.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/synchronization/mutex.h"

extern "C" {

// Additional report of fatal usage error message before we std::exit. Error is
// fatal if is_fatal argument to ReportUsageError is true.
ABSL_ATTRIBUTE_WEAK void ABSL_INTERNAL_C_SYMBOL(
    AbslInternalReportFatalUsageError)(absl::string_view) {}

}  // extern "C"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace flags_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace flags_internal

void SetFlagsUsageConfig(FlagsUsageConfig usage_config) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
