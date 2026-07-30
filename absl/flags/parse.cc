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

#include "absl/flags/parse.h"

#include <stdlib.h>

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include "absl/algorithm/container.h"
#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/no_destructor.h"
#include "absl/base/thread_annotations.h"
#include "absl/flags/commandlineflag.h"
#include "absl/flags/config.h"
#include "absl/flags/flag.h"
#include "absl/flags/internal/commandlineflag.h"
#include "absl/flags/internal/flag.h"
#include "absl/flags/internal/parse.h"
#include "absl/flags/internal/private_handle_accessor.h"
#include "absl/flags/internal/program_name.h"
#include "absl/flags/internal/usage.h"
#include "absl/flags/reflection.h"
#include "absl/flags/usage.h"
#include "absl/flags/usage_config.h"
#include "absl/strings/ascii.h"
#include "absl/strings/internal/damerau_levenshtein_distance.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/synchronization/mutex.h"

// --------------------------------------------------------------------

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace flags_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace flags_internal
ABSL_NAMESPACE_END
}  // namespace absl

// These flags influence how command line flags are parsed and are only intended
// to be set on the command line.  Avoid reading or setting them from C++ code.
ABSL_FLAG(std::vector<std::string>, flagfile, {},
          "comma-separated list of files to load flags from")
    .OnUpdate([]() {
      if (absl::GetFlag(FLAGS_flagfile).empty()) return;

      absl::MutexLock l(absl::flags_internal::ProcessingChecksMutex());

      // Setting this flag twice before it is handled most likely an internal
      // error and should be reviewed by developers.
      if (absl::flags_internal::flagfile_needs_processing) {
        ABSL_INTERNAL_LOG(WARNING, "flagfile set twice before it is handled");
      }

      absl::flags_internal::flagfile_needs_processing = true;
    });
ABSL_FLAG(std::vector<std::string>, fromenv, {},
          "comma-separated list of flags to set from the environment"
          " [use 'export FLAGS_flag1=value']")
    .OnUpdate([]() {
      if (absl::GetFlag(FLAGS_fromenv).empty()) return;

      absl::MutexLock l(absl::flags_internal::ProcessingChecksMutex());

      // Setting this flag twice before it is handled most likely an internal
      // error and should be reviewed by developers.
      if (absl::flags_internal::fromenv_needs_processing) {
        ABSL_INTERNAL_LOG(WARNING, "fromenv set twice before it is handled.");
      }

      absl::flags_internal::fromenv_needs_processing = true;
    });
ABSL_FLAG(std::vector<std::string>, tryfromenv, {},
          "comma-separated list of flags to try to set from the environment if "
          "present")
    .OnUpdate([]() {
      if (absl::GetFlag(FLAGS_tryfromenv).empty()) return;

      absl::MutexLock l(absl::flags_internal::ProcessingChecksMutex());

      // Setting this flag twice before it is handled most likely an internal
      // error and should be reviewed by developers.
      if (absl::flags_internal::tryfromenv_needs_processing) {
        ABSL_INTERNAL_LOG(WARNING,
                          "tryfromenv set twice before it is handled.");
      }

      absl::flags_internal::tryfromenv_needs_processing = true;
    });

// Rather than reading or setting --undefok from C++ code, please consider using
// ABSL_RETIRED_FLAG instead.
ABSL_FLAG(std::vector<std::string>, undefok, {},
          "comma-separated list of flag names that it is okay to specify "
          "on the command line even if the program does not define a flag "
          "with that name");

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace flags_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace flags_internal

void ParseAbseilFlagsOnly(int argc, char* argv[],
                          std::vector<char*>& positional_args,
                          std::vector<UnrecognizedFlag>& unrecognized_flags) { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------

void ReportUnrecognizedFlags(
    const std::vector<UnrecognizedFlag>& unrecognized_flags) { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------

std::vector<char*> ParseCommandLine(int argc, char* argv[]) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
