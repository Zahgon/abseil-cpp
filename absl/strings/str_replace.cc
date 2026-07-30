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

#include "absl/strings/str_replace.h"

#include <cstddef>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/config.h"
#include "absl/base/nullability.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace strings_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace strings_internal

// We can implement this in terms of the generic StrReplaceAll, but
// we must specify the template overload because C++ cannot deduce the type
// of an initializer_list parameter to a function, and also if we don't specify
// the type, we just call ourselves.
//
// Note that we implement them here, rather than in the header, so that they
// aren't inlined.

std::string StrReplaceAll(absl::string_view s,
                          strings_internal::FixedMapping replacements) { __builtin_trap() /* STUB: not implemented */; }

int StrReplaceAll(strings_internal::FixedMapping replacements,
                  std::string* absl_nonnull target) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
