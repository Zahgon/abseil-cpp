// Copyright 2016 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   https://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

// This file implements the TimeZoneIf interface using the "zoneinfo"
// data provided by the IANA Time Zone Database (i.e., the only real game
// in town).
//
// TimeZoneInfo represents the history of UTC-offset changes within a time
// zone. Most changes are due to daylight-saving rules, but occasionally
// shifts are made to the time-zone's base offset. The database only attempts
// to be definitive for times since 1970, so be wary of local-time conversions
// before that. Also, rule and zone-boundary changes are made at the whim
// of governments, so the conversion of future times needs to be taken with
// a grain of salt.
//
// For more information see tzfile(5), http://www.iana.org/time-zones, or
// https://en.wikipedia.org/wiki/Zoneinfo.
//
// Note that we assume the proleptic Gregorian calendar and 60-second
// minutes throughout.

#include "absl/time/internal/cctz/src/time_zone_info.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/config.h"
#include "absl/time/internal/cctz/include/cctz/civil_time.h"
#include "absl/time/internal/cctz/src/time_zone_fixed.h"
#include "absl/time/internal/cctz/src/time_zone_posix.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace time_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace time_internal
ABSL_NAMESPACE_END
}  // namespace absl
