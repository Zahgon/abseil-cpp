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

#include <string.h>

#include <cctype>
#include <cstdint>
#include <utility>

#include "absl/strings/ascii.h"
#include "absl/strings/match.h"
#include "absl/strings/string_view.h"
#include "absl/time/internal/cctz/include/cctz/time_zone.h"
#include "absl/time/time.h"

namespace cctz = absl::time_internal::cctz;

namespace absl {
ABSL_NAMESPACE_BEGIN

ABSL_DLL extern const char RFC3339_full[] = "%Y-%m-%d%ET%H:%M:%E*S%Ez";
ABSL_DLL extern const char RFC3339_sec[] = "%Y-%m-%d%ET%H:%M:%S%Ez";

ABSL_DLL extern const char RFC1123_full[] = "%a, %d %b %E4Y %H:%M:%S %z";
ABSL_DLL extern const char RFC1123_no_wday[] = "%d %b %E4Y %H:%M:%S %z";

namespace {

constexpr absl::string_view kInfiniteFutureStr = "infinite-future";
constexpr absl::string_view kInfinitePastStr = "infinite-past";

struct cctz_parts {
  cctz::time_point<cctz::seconds> sec;
  cctz::detail::femtoseconds fem;
};

inline cctz::time_point<cctz::seconds> unix_epoch() { __builtin_trap() /* STUB: not implemented */; }

// Splits a Time into seconds and femtoseconds, which can be used with CCTZ.
// Requires that 't' is finite. See duration.cc for details about rep_hi and
// rep_lo.
cctz_parts Split(absl::Time t) { __builtin_trap() /* STUB: not implemented */; }

// Joins the given seconds and femtoseconds into a Time. See duration.cc for
// details about rep_hi and rep_lo.
absl::Time Join(const cctz_parts& parts) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

std::string FormatTime(absl::string_view format, absl::Time t,
                       absl::TimeZone tz) { __builtin_trap() /* STUB: not implemented */; }

std::string FormatTime(absl::Time t, absl::TimeZone tz) { __builtin_trap() /* STUB: not implemented */; }

std::string FormatTime(absl::Time t) { __builtin_trap() /* STUB: not implemented */; }

bool ParseTime(absl::string_view format, absl::string_view input,
               absl::Time* time, std::string* err) { __builtin_trap() /* STUB: not implemented */; }

// If the input string does not contain an explicit UTC offset, interpret
// the fields with respect to the given TimeZone.
bool ParseTime(absl::string_view format, absl::string_view input,
               absl::TimeZone tz, absl::Time* time, std::string* err) { __builtin_trap() /* STUB: not implemented */; }

// Functions required to support absl::Time flags.
bool AbslParseFlag(absl::string_view text, absl::Time* t, std::string* error) { __builtin_trap() /* STUB: not implemented */; }

std::string AbslUnparseFlag(absl::Time t) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
