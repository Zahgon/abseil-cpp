//
//  Copyright 2020 The Abseil Authors.
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

#include "absl/flags/reflection.h"

#include <assert.h>

#include <atomic>
#include <string>
#include <utility>

#include "absl/base/config.h"
#include "absl/base/no_destructor.h"
#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/flags/commandlineflag.h"
#include "absl/flags/internal/private_handle_accessor.h"
#include "absl/flags/internal/registry.h"
#include "absl/flags/usage_config.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/synchronization/mutex.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace flags_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace flags_internal

FlagSaver::FlagSaver() : impl_(new flags_internal::FlagSaverImpl) { __builtin_trap() /* STUB: not implemented */; }

FlagSaver::~FlagSaver() { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------

CommandLineFlag* FindCommandLineFlag(absl::string_view name) { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------

absl::flat_hash_map<absl::string_view, absl::CommandLineFlag*> GetAllFlags() { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
