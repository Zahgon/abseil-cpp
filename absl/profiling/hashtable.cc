// Copyright 2025 The Abseil Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may
// obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "absl/profiling/hashtable.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/config.h"
#include "absl/container/internal/hashtablez_sampler.h"
#include "absl/profiling/internal/profile_builder.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "absl/types/span.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

StatusOr<std::string> MarshalHashtableProfile() { __builtin_trap() /* STUB: not implemented */; }

namespace debugging_internal {

static void DroppedHashtableSample() { __builtin_trap() /* STUB: not implemented */; }

StatusOr<std::string> MarshalHashtableProfile(
    container_internal::HashtablezSampler& sampler, Time now) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace debugging_internal
ABSL_NAMESPACE_END
}  // namespace absl
