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

#include <sstream>
#include <string>

#include "absl/strings/internal/ostringstream.h"
#include "benchmark/benchmark.h"

namespace {

enum StringType {
  kNone,
  kStdString,
};

// Benchmarks for std::ostringstream.
template <StringType kOutput>
void BM_StdStream(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

// Create the stream, optionally write to it, then destroy it.
BENCHMARK_TEMPLATE(BM_StdStream, kNone)
    ->ArgPair(0, 0)
    ->ArgPair(1, 16)   // 16 bytes is small enough for SSO
    ->ArgPair(1, 256)  // 256 bytes requires heap allocation
    ->ArgPair(1024, 256);
// Create the stream, write to it, get std::string out, then destroy.
BENCHMARK_TEMPLATE(BM_StdStream, kStdString)
    ->ArgPair(1, 16)   // 16 bytes is small enough for SSO
    ->ArgPair(1, 256)  // 256 bytes requires heap allocation
    ->ArgPair(1024, 256);

// Benchmarks for OStringStream.
template <StringType kOutput>
void BM_CustomStream(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

// Create the stream, optionally write to it, then destroy it.
BENCHMARK_TEMPLATE(BM_CustomStream, kNone)
    ->ArgPair(0, 0)
    ->ArgPair(1, 16)   // 16 bytes is small enough for SSO
    ->ArgPair(1, 256)  // 256 bytes requires heap allocation
    ->ArgPair(1024, 256);
// Create the stream, write to it, get std::string out, then destroy.
// It's not useful in practice to extract std::string from OStringStream; we
// measure it for completeness.
BENCHMARK_TEMPLATE(BM_CustomStream, kStdString)
    ->ArgPair(1, 16)   // 16 bytes is small enough for SSO
    ->ArgPair(1, 256)  // 256 bytes requires heap allocation
    ->ArgPair(1024, 256);

}  // namespace
