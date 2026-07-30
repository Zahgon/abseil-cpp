//
// Copyright 2019 The Abseil Authors.
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

#include "absl/flags/internal/usage.h"

#include <stdint.h>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <map>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/no_destructor.h"
#include "absl/base/thread_annotations.h"
#include "absl/flags/commandlineflag.h"
#include "absl/flags/flag.h"
#include "absl/flags/internal/flag.h"
#include "absl/flags/internal/path_util.h"
#include "absl/flags/internal/private_handle_accessor.h"
#include "absl/flags/internal/program_name.h"
#include "absl/flags/internal/registry.h"
#include "absl/flags/usage_config.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/synchronization/mutex.h"

// Dummy global variables to prevent anyone else defining these.
bool FLAGS_help = false;
bool FLAGS_helpfull = false;
bool FLAGS_helpshort = false;
bool FLAGS_helppackage = false;
bool FLAGS_version = false;
bool FLAGS_only_check_args = false;
bool FLAGS_helpon = false;
bool FLAGS_helpmatch = false;

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace flags_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace flags_internal
ABSL_NAMESPACE_END
}  // namespace absl
