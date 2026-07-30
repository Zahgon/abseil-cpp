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

#include "absl/strings/match.h"

#include <algorithm>
#include <cstdint>

#include "absl/base/config.h"
#include "absl/base/internal/endian.h"
#include "absl/base/optimization.h"
#include "absl/numeric/bits.h"
#include "absl/strings/ascii.h"
#include "absl/strings/internal/memutil.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

bool EqualsIgnoreCase(absl::string_view piece1,
                      absl::string_view piece2) noexcept { __builtin_trap() /* STUB: not implemented */; }

bool StrContainsIgnoreCase(absl::string_view haystack,
                           absl::string_view needle) noexcept { __builtin_trap() /* STUB: not implemented */; }

bool StrContainsIgnoreCase(absl::string_view haystack,
                           char needle) noexcept { __builtin_trap() /* STUB: not implemented */; }

bool StartsWithIgnoreCase(absl::string_view text,
                          absl::string_view prefix) noexcept { __builtin_trap() /* STUB: not implemented */; }

bool EndsWithIgnoreCase(absl::string_view text,
                        absl::string_view suffix) noexcept { __builtin_trap() /* STUB: not implemented */; }

absl::string_view FindLongestCommonPrefix(absl::string_view a,
                                          absl::string_view b) { __builtin_trap() /* STUB: not implemented */; }

absl::string_view FindLongestCommonSuffix(absl::string_view a,
                                          absl::string_view b) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
