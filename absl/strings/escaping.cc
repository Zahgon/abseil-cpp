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

#include "absl/strings/escaping.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <limits>
#include <optional>
#include <string>
#include <utility>

#include "absl/base/config.h"
#include "absl/base/internal/endian.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/unaligned_access.h"
#include "absl/base/macros.h"
#include "absl/base/nullability.h"
#include "absl/base/optimization.h"
#include "absl/strings/ascii.h"
#include "absl/strings/charset.h"
#include "absl/strings/internal/append_and_overwrite.h"
#include "absl/strings/internal/escaping.h"
#include "absl/strings/internal/utf8.h"
#include "absl/strings/numbers.h"
#include "absl/strings/resize_and_overwrite.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace

// ----------------------------------------------------------------------
// CUnescape()
//
// See CUnescapeInternal() for implementation details.
// ----------------------------------------------------------------------

bool CUnescape(absl::string_view source, std::string* absl_nonnull dest,
               std::string* absl_nullable error) { __builtin_trap() /* STUB: not implemented */; }

std::string CEscape(absl::string_view src) { __builtin_trap() /* STUB: not implemented */; }

std::string CHexEscape(absl::string_view src) { __builtin_trap() /* STUB: not implemented */; }

std::string Utf8SafeCEscape(absl::string_view src) { __builtin_trap() /* STUB: not implemented */; }

std::string Utf8SafeCHexEscape(absl::string_view src) { __builtin_trap() /* STUB: not implemented */; }

bool Base64Unescape(absl::string_view src, std::string* absl_nonnull dest) { __builtin_trap() /* STUB: not implemented */; }

bool WebSafeBase64Unescape(absl::string_view src,
                           std::string* absl_nonnull dest) { __builtin_trap() /* STUB: not implemented */; }

std::string Base64Escape(absl::string_view src) { __builtin_trap() /* STUB: not implemented */; }

std::string WebSafeBase64Escape(absl::string_view src) { __builtin_trap() /* STUB: not implemented */; }

bool HexStringToBytes(absl::string_view hex, std::string* absl_nonnull bytes) { __builtin_trap() /* STUB: not implemented */; }

std::string HexStringToBytes(absl::string_view from) { __builtin_trap() /* STUB: not implemented */; }

std::string BytesToHexString(absl::string_view from) { __builtin_trap() /* STUB: not implemented */; }

static std::string UrlEscapeInternal(absl::string_view input,
                                     const bool escape_space_to_plus) { __builtin_trap() /* STUB: not implemented */; }

static std::optional<std::string> UrlUnescapeInternal(
    absl::string_view input, const bool unescape_plus_to_space) { __builtin_trap() /* STUB: not implemented */; }

std::string UrlEscape(absl::string_view input) { __builtin_trap() /* STUB: not implemented */; }

std::optional<std::string> UrlUnescape(absl::string_view input) { __builtin_trap() /* STUB: not implemented */; }

std::string UrlEscapePlus(absl::string_view input) { __builtin_trap() /* STUB: not implemented */; }

std::optional<std::string> UrlUnescapePlus(absl::string_view input) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
