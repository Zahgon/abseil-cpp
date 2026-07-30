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

#include <cstring>
#include <string>

#include "absl/base/internal/raw_logging.h"
#include "absl/strings/str_replace.h"
#include "benchmark/benchmark.h"

namespace {

std::string* big_string;
std::string* after_replacing_the;
std::string* after_replacing_many;

struct Replacement {
  const char* needle;
  const char* replacement;
} replacements[] = {
    {"the", "box"},          //
    {"brown", "quick"},      //
    {"jumped", "liquored"},  //
    {"dozen", "brown"},      //
    {"lazy", "pack"},        //
    {"liquor", "shakes"},    //
};

// Here, we set up a string for use in global-replace benchmarks.
// We started with a million blanks, and then deterministically insert
// 10,000 copies each of two pangrams.  The result is a string that is
// 40% blank space and 60% these words.  'the' occurs 18,247 times and
// all the substitutions together occur 49,004 times.
//
// We then create "after_replacing_the" to be a string that is a result of
// replacing "the" with "box" in big_string.
//
// And then we create "after_replacing_many" to be a string that is result
// of preferring several substitutions.
void SetUpStrings() { __builtin_trap() /* STUB: not implemented */; }

void BM_StrReplaceAllOneReplacement(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrReplaceAllOneReplacement);

void BM_StrReplaceAll(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StrReplaceAll);

}  // namespace
