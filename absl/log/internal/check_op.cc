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

#include "absl/log/internal/check_op.h"

#include <cstdint>
#include <cstring>
#include <ostream>
#include <string>
#include <utility>

#include "absl/base/config.h"
#include "absl/base/nullability.h"
#include "absl/debugging/leak_check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

#ifdef _MSC_VER
#define strcasecmp _stricmp
#else
#include <strings.h>  // for strcasecmp, but msvc does not have this header
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace log_internal { __builtin_trap() /* STUB: not implemented */; }w text) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace detect_specialization

}  // namespace log_internal
ABSL_NAMESPACE_END
}  // namespace absl
