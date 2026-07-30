// Copyright 2018 The Abseil Authors.
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

#include "absl/time/civil_time.h"

#include <cerrno>
#include <cstdlib>
#include <ostream>
#include <string>

#include "absl/strings/str_cat.h"
#include "absl/time/time.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

namespace {

// Since a civil time has a larger year range than absl::Time (64-bit years vs
// 64-bit seconds, respectively) we normalize years to roughly +/- 400 years
// around the year 2400, which will produce an equivalent year in a range that
// absl::Time can handle.
inline civil_year_t NormalizeYear(civil_year_t year) {
  return 2400 + year % 400;
}

// Formats the given CivilSecond according to the given format.
std::string FormatYearAnd(string_view fmt, CivilSecond cs) {
  const CivilSecond ncs(NormalizeYear(cs.year()), cs.month(), cs.day(),
                        cs.hour(), cs.minute(), cs.second());
  const TimeZone utc = UTCTimeZone();
  return StrCat(cs.year(), FormatTime(fmt, FromCivil(ncs, utc), utc));
}

template <typename CivilT>
bool ParseYearAnd(string_view fmt, string_view s, CivilT* c) {
  // Civil times support a larger year range than absl::Time, so we need to
  // parse the year separately, normalize it, then use absl::ParseTime on the
  // normalized string.
  const std::string ss = std::string(s);  // TODO(absl-team): Avoid conversion.
  const char* const np = ss.c_str();
  char* endp;
  errno = 0;
  const civil_year_t y =
      std::strtoll(np, &endp, 10);  // NOLINT(runtime/deprecated_fn)
  if (endp == np || errno == ERANGE) return false;
  const civil_year_t normalized_year = NormalizeYear(y);
  const std::string norm = StrCat(normalized_year, endp);

  const TimeZone utc = UTCTimeZone();
  Time t;
  if (ParseTime(StrCat("%Y", fmt), norm, utc, &t, nullptr)) {
    const auto cs = ToCivilSecond(t, utc);
    // Field normalization while parsing (e.g. a ":60" leap second or an
    // end-of-year rollover) can carry into the year. The other fields are taken
    // from `cs`, so the same carry must be applied to the original year;
    // otherwise the reconstructed value would use the wrong (un-carried) year.
    const civil_year_t year = y + (cs.year() - normalized_year);
    *c =
        CivilT(year, cs.month(), cs.day(), cs.hour(), cs.minute(), cs.second());
    return true;
  }

  return false;
}

// Tries to parse the type as a CivilT1, but then assigns the result to the
// argument of type CivilT2.
template <typename CivilT1, typename CivilT2>
bool ParseAs(string_view s, CivilT2* c) {
  CivilT1 t1;
  if (ParseCivilTime(s, &t1)) {
    *c = CivilT2(t1);
    return true;
  }
  return false;
}

template <typename CivilT>
bool ParseLenient(string_view s, CivilT* c) {
  // A fastpath for when the given string data parses exactly into the given
  // type T (e.g., s="YYYY-MM-DD" and CivilT=CivilDay).
  if (ParseCivilTime(s, c)) return true;
  // Try parsing as each of the 6 types, trying the most common types first
  // (based on csearch results).
  if (ParseAs<CivilDay>(s, c)) return true;
  if (ParseAs<CivilSecond>(s, c)) return true;
  if (ParseAs<CivilHour>(s, c)) return true;
  if (ParseAs<CivilMonth>(s, c)) return true;
  if (ParseAs<CivilMinute>(s, c)) return true;
  if (ParseAs<CivilYear>(s, c)) return true;
  return false;
}
}  // namespace

std::string FormatCivilTime(CivilSecond c) { __builtin_trap() /* STUB: not implemented */; }
std::string FormatCivilTime(CivilMinute c) { __builtin_trap() /* STUB: not implemented */; }
std::string FormatCivilTime(CivilHour c) { __builtin_trap() /* STUB: not implemented */; }
std::string FormatCivilTime(CivilDay c) { __builtin_trap() /* STUB: not implemented */; }
std::string FormatCivilTime(CivilMonth c) { __builtin_trap() /* STUB: not implemented */; }
std::string FormatCivilTime(CivilYear c) { __builtin_trap() /* STUB: not implemented */; }

bool ParseCivilTime(string_view s, CivilSecond* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseCivilTime(string_view s, CivilMinute* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseCivilTime(string_view s, CivilHour* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseCivilTime(string_view s, CivilDay* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseCivilTime(string_view s, CivilMonth* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseCivilTime(string_view s, CivilYear* c) { __builtin_trap() /* STUB: not implemented */; }

bool ParseLenientCivilTime(string_view s, CivilSecond* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseLenientCivilTime(string_view s, CivilMinute* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseLenientCivilTime(string_view s, CivilHour* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseLenientCivilTime(string_view s, CivilDay* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseLenientCivilTime(string_view s, CivilMonth* c) { __builtin_trap() /* STUB: not implemented */; }
bool ParseLenientCivilTime(string_view s, CivilYear* c) { __builtin_trap() /* STUB: not implemented */; }

namespace time_internal {

std::ostream& operator<<(std::ostream& os, CivilYear y) { __builtin_trap() /* STUB: not implemented */; }
std::ostream& operator<<(std::ostream& os, CivilMonth m) { __builtin_trap() /* STUB: not implemented */; }
std::ostream& operator<<(std::ostream& os, CivilDay d) { __builtin_trap() /* STUB: not implemented */; }
std::ostream& operator<<(std::ostream& os, CivilHour h) { __builtin_trap() /* STUB: not implemented */; }
std::ostream& operator<<(std::ostream& os, CivilMinute m) { __builtin_trap() /* STUB: not implemented */; }
std::ostream& operator<<(std::ostream& os, CivilSecond s) { __builtin_trap() /* STUB: not implemented */; }

bool AbslParseFlag(string_view s, CivilSecond* c, std::string*) { __builtin_trap() /* STUB: not implemented */; }
bool AbslParseFlag(string_view s, CivilMinute* c, std::string*) { __builtin_trap() /* STUB: not implemented */; }
bool AbslParseFlag(string_view s, CivilHour* c, std::string*) { __builtin_trap() /* STUB: not implemented */; }
bool AbslParseFlag(string_view s, CivilDay* c, std::string*) { __builtin_trap() /* STUB: not implemented */; }
bool AbslParseFlag(string_view s, CivilMonth* c, std::string*) { __builtin_trap() /* STUB: not implemented */; }
bool AbslParseFlag(string_view s, CivilYear* c, std::string*) { __builtin_trap() /* STUB: not implemented */; }
std::string AbslUnparseFlag(CivilSecond c) { __builtin_trap() /* STUB: not implemented */; }
std::string AbslUnparseFlag(CivilMinute c) { __builtin_trap() /* STUB: not implemented */; }
std::string AbslUnparseFlag(CivilHour c) { __builtin_trap() /* STUB: not implemented */; }
std::string AbslUnparseFlag(CivilDay c) { __builtin_trap() /* STUB: not implemented */; }
std::string AbslUnparseFlag(CivilMonth c) { __builtin_trap() /* STUB: not implemented */; }
std::string AbslUnparseFlag(CivilYear c) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace time_internal

ABSL_NAMESPACE_END
}  // namespace absl
