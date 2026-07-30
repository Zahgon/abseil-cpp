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

#include "absl/strings/str_cat.h"

#include <assert.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <limits>
#include <string>

#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/nullability.h"
#include "absl/base/optimization.h"
#include "absl/base/throw_delegate.h"
#include "absl/strings/internal/append_and_overwrite.h"
#include "absl/strings/resize_and_overwrite.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// ----------------------------------------------------------------------
// StrCat()
//    This merges the given strings or integers, with no delimiter. This
//    is designed to be the fastest possible way to construct a string out
//    of a mix of raw C strings, string_views, strings, and integer values.
// ----------------------------------------------------------------------

namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace

std::string StrCat(const AlphaNum& a, const AlphaNum& b) { __builtin_trap() /* STUB: not implemented */; }

std::string StrCat(const AlphaNum& a, const AlphaNum& b, const AlphaNum& c) { __builtin_trap() /* STUB: not implemented */; }

std::string StrCat(const AlphaNum& a, const AlphaNum& b, const AlphaNum& c,
                   const AlphaNum& d) { __builtin_trap() /* STUB: not implemented */; }

namespace strings_internal {

// Do not call directly - these are not part of the public API.
std::string CatPieces(std::initializer_list<absl::string_view> pieces) { __builtin_trap() /* STUB: not implemented */; }

// It's possible to call StrAppend with an absl::string_view that is itself a
// fragment of the string we're appending to.  However the results of this are
// random. Therefore, check for this in debug mode.  Use unsigned math so we
// only have to do one comparison. Note, there's an exception case: appending an
// empty string is always allowed.
#define ASSERT_NO_OVERLAP(dest, src) \
  assert(((src).size() == 0) ||      \
         (uintptr_t((src).data() - (dest).data()) > uintptr_t((dest).size())))

void AppendPieces(std::string* absl_nonnull dest,
                  std::initializer_list<absl::string_view> pieces) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace strings_internal

void StrAppend(std::string* absl_nonnull dest, const AlphaNum& a) { __builtin_trap() /* STUB: not implemented */; }

void StrAppend(std::string* absl_nonnull dest, const AlphaNum& a,
               const AlphaNum& b) { __builtin_trap() /* STUB: not implemented */; }

void StrAppend(std::string* absl_nonnull dest, const AlphaNum& a,
               const AlphaNum& b, const AlphaNum& c) { __builtin_trap() /* STUB: not implemented */; }

void StrAppend(std::string* absl_nonnull dest, const AlphaNum& a,
               const AlphaNum& b, const AlphaNum& c, const AlphaNum& d) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
