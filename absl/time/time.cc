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

// The implementation of the absl::Time class, which is declared in
// //absl/time.h.
//
// The representation for an absl::Time is an absl::Duration offset from the
// epoch.  We use the traditional Unix epoch (1970-01-01 00:00:00 +0000)
// for convenience, but this is not exposed in the API and could be changed.
//
// NOTE: To keep type verbosity to a minimum, the following variable naming
// conventions are used throughout this file.
//
// tz: An absl::TimeZone
// ci: An absl::TimeZone::CivilInfo
// ti: An absl::TimeZone::TimeInfo
// cd: An absl::CivilDay or a cctz::civil_day
// cs: An absl::CivilSecond or a cctz::civil_second
// bd: An absl::Time::Breakdown
// cl: A cctz::time_zone::civil_lookup
// al: A cctz::time_zone::absolute_lookup

#include "absl/time/time.h"

#if defined(_MSC_VER)
#include <winsock2.h>  // for timeval
#endif

#include <cstring>
#include <ctime>
#include <limits>

#include "absl/time/internal/cctz/include/cctz/civil_time.h"
#include "absl/time/internal/cctz/include/cctz/time_zone.h"

namespace cctz = absl::time_internal::cctz;

namespace absl {
ABSL_NAMESPACE_BEGIN

namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace

//
// Time
//

ABSL_INTERNAL_DISABLE_DEPRECATED_DECLARATION_WARNING
absl::Time::Breakdown Time::In(absl::TimeZone tz) const { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_RESTORE_DEPRECATED_DECLARATION_WARNING

//
// Conversions from/to other time types.
//

absl::Time FromUDate(double udate) { __builtin_trap() /* STUB: not implemented */; }

absl::Time FromUniversal(int64_t universal) { __builtin_trap() /* STUB: not implemented */; }

int64_t ToUnixNanos(Time t) { __builtin_trap() /* STUB: not implemented */; }

int64_t ToUnixMicros(Time t) { __builtin_trap() /* STUB: not implemented */; }

int64_t ToUnixMillis(Time t) { __builtin_trap() /* STUB: not implemented */; }

int64_t ToUnixSeconds(Time t) { __builtin_trap() /* STUB: not implemented */; }

time_t ToTimeT(Time t) { __builtin_trap() /* STUB: not implemented */; }

double ToUDate(Time t) { __builtin_trap() /* STUB: not implemented */; }

int64_t ToUniversal(absl::Time t) { __builtin_trap() /* STUB: not implemented */; }

absl::Time TimeFromTimespec(timespec ts) { __builtin_trap() /* STUB: not implemented */; }

absl::Time TimeFromTimeval(timeval tv) { __builtin_trap() /* STUB: not implemented */; }

timespec ToTimespec(Time t) { __builtin_trap() /* STUB: not implemented */; }

timeval ToTimeval(Time t) { __builtin_trap() /* STUB: not implemented */; }

Time FromChrono(const std::chrono::system_clock::time_point& tp) { __builtin_trap() /* STUB: not implemented */; }

std::chrono::system_clock::time_point ToChronoTime(absl::Time t) { __builtin_trap() /* STUB: not implemented */; }

//
// TimeZone
//

absl::TimeZone::CivilInfo TimeZone::At(Time t) const { __builtin_trap() /* STUB: not implemented */; }

absl::TimeZone::TimeInfo TimeZone::At(CivilSecond ct) const { __builtin_trap() /* STUB: not implemented */; }

bool TimeZone::NextTransition(Time t, CivilTransition* trans) const { __builtin_trap() /* STUB: not implemented */; }

bool TimeZone::PrevTransition(Time t, CivilTransition* trans) const { __builtin_trap() /* STUB: not implemented */; }

//
// Conversions involving time zones.
//
ABSL_INTERNAL_DISABLE_DEPRECATED_DECLARATION_WARNING
absl::TimeConversion ConvertDateTime(int64_t year, int mon, int day, int hour,
                                     int min, int sec, TimeZone tz) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_RESTORE_DEPRECATED_DECLARATION_WARNING

absl::Time FromTM(const struct tm& tm, absl::TimeZone tz) { __builtin_trap() /* STUB: not implemented */; }

struct tm ToTM(absl::Time t, absl::TimeZone tz) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
