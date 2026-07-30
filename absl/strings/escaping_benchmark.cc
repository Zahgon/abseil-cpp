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

#include <cstdint>
#include <memory>
#include <random>
#include <string>

#include "absl/base/internal/raw_logging.h"
#include "absl/strings/ascii.h"
#include "absl/strings/escaping.h"
#include "absl/strings/internal/escaping_test_common.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "benchmark/benchmark.h"

namespace {

void BM_CUnescapeHexString(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CUnescapeHexString);

void BM_WebSafeBase64Escape_string(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_WebSafeBase64Escape_string);

void BM_HexStringToBytes(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_HexStringToBytes)->Range(1, 1 << 8);

void BM_HexStringToBytes_Fail(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_HexStringToBytes_Fail);

static void BM_UrlEscape(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_UrlEscape);

static void BM_UrlEscapePlus(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_UrlEscapePlus);

// Used for the CEscape benchmarks
const char kStringValueNoEscape[] = "1234567890";
const char kStringValueSomeEscaped[] = "123\n56789\xA1";
const char kStringValueMostEscaped[] = "\xA1\xA2\ny\xA4\xA5\xA6z\b\r";

void CEscapeBenchmarkHelper(benchmark::State& state, const char* string_value,
                            int max_len) { __builtin_trap() /* STUB: not implemented */; }

void BM_CEscape_NoEscape(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CEscape_NoEscape)->Range(1, 1 << 14);

void BM_CEscape_SomeEscaped(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CEscape_SomeEscaped)->Range(1, 1 << 14);

void BM_CEscape_MostEscaped(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CEscape_MostEscaped)->Range(1, 1 << 14);

}  // namespace
