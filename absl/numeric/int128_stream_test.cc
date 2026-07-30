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

#include "absl/numeric/int128.h"

#include <sstream>
#include <string>

#include "gtest/gtest.h"
#include "absl/strings/str_cat.h"

namespace {

struct Uint128TestCase {
  absl::uint128 value;
  std::ios_base::fmtflags flags;
  std::streamsize width;
  const char* expected;
};

constexpr char kFill = '_';

std::string StreamFormatToString(std::ios_base::fmtflags flags,
                                 std::streamsize width) { __builtin_trap() /* STUB: not implemented */; }

constexpr std::ios::fmtflags kDec = std::ios::dec;
constexpr std::ios::fmtflags kOct = std::ios::oct;
constexpr std::ios::fmtflags kHex = std::ios::hex;
constexpr std::ios::fmtflags kLeft = std::ios::left;
constexpr std::ios::fmtflags kInt = std::ios::internal;
constexpr std::ios::fmtflags kRight = std::ios::right;
constexpr std::ios::fmtflags kUpper = std::ios::uppercase;
constexpr std::ios::fmtflags kBase = std::ios::showbase;
constexpr std::ios::fmtflags kPos = std::ios::showpos;

void CheckUint128Case(const Uint128TestCase& test_case) { __builtin_trap() /* STUB: not implemented */; }

TEST(Uint128, OStreamValueTest) {
  CheckUint128Case({1, kDec, /*width = */ 0, "1"});
  CheckUint128Case({1, kOct, /*width = */ 0, "1"});
  CheckUint128Case({1, kHex, /*width = */ 0, "1"});
  CheckUint128Case({9, kDec, /*width = */ 0, "9"});
  CheckUint128Case({9, kOct, /*width = */ 0, "11"});
  CheckUint128Case({9, kHex, /*width = */ 0, "9"});
  CheckUint128Case({12345, kDec, /*width = */ 0, "12345"});
  CheckUint128Case({12345, kOct, /*width = */ 0, "30071"});
  CheckUint128Case({12345, kHex, /*width = */ 0, "3039"});
  CheckUint128Case(
      {0x8000000000000000, kDec, /*width = */ 0, "9223372036854775808"});
  CheckUint128Case(
      {0x8000000000000000, kOct, /*width = */ 0, "1000000000000000000000"});
  CheckUint128Case(
      {0x8000000000000000, kHex, /*width = */ 0, "8000000000000000"});
  CheckUint128Case({std::numeric_limits<uint64_t>::max(), kDec,
                    /*width = */ 0, "18446744073709551615"});
  CheckUint128Case({std::numeric_limits<uint64_t>::max(), kOct,
                    /*width = */ 0, "1777777777777777777777"});
  CheckUint128Case({std::numeric_limits<uint64_t>::max(), kHex,
                    /*width = */ 0, "ffffffffffffffff"});
  CheckUint128Case(
      {absl::MakeUint128(1, 0), kDec, /*width = */ 0, "18446744073709551616"});
  CheckUint128Case({absl::MakeUint128(1, 0), kOct, /*width = */ 0,
                    "2000000000000000000000"});
  CheckUint128Case(
      {absl::MakeUint128(1, 0), kHex, /*width = */ 0, "10000000000000000"});
  CheckUint128Case({absl::MakeUint128(0x8000000000000000, 0), kDec,
                    /*width = */ 0, "170141183460469231731687303715884105728"});
  CheckUint128Case({absl::MakeUint128(0x8000000000000000, 0), kOct,
                    /*width = */ 0,
                    "2000000000000000000000000000000000000000000"});
  CheckUint128Case({absl::MakeUint128(0x8000000000000000, 0), kHex,
                    /*width = */ 0, "80000000000000000000000000000000"});
  CheckUint128Case({absl::Uint128Max(), kDec, /*width = */ 0,
                    "340282366920938463463374607431768211455"});
  CheckUint128Case({absl::Uint128Max(), kOct, /*width = */ 0,
                    "3777777777777777777777777777777777777777777"});
  CheckUint128Case({absl::Uint128Max(), kHex, /*width = */ 0,
                    "ffffffffffffffffffffffffffffffff"});
}

std::vector<Uint128TestCase> GetUint128FormatCases();

TEST(Uint128, OStreamFormatTest) {
  for (const Uint128TestCase& test_case : GetUint128FormatCases()) {
    CheckUint128Case(test_case);
  }
}

struct Int128TestCase {
  absl::int128 value;
  std::ios_base::fmtflags flags;
  std::streamsize width;
  const char* expected;
};

void CheckInt128Case(const Int128TestCase& test_case) { __builtin_trap() /* STUB: not implemented */; }

TEST(Int128, OStreamValueTest) {
  CheckInt128Case({1, kDec, /*width = */ 0, "1"});
  CheckInt128Case({1, kOct, /*width = */ 0, "1"});
  CheckInt128Case({1, kHex, /*width = */ 0, "1"});
  CheckInt128Case({9, kDec, /*width = */ 0, "9"});
  CheckInt128Case({9, kOct, /*width = */ 0, "11"});
  CheckInt128Case({9, kHex, /*width = */ 0, "9"});
  CheckInt128Case({12345, kDec, /*width = */ 0, "12345"});
  CheckInt128Case({12345, kOct, /*width = */ 0, "30071"});
  CheckInt128Case({12345, kHex, /*width = */ 0, "3039"});
  CheckInt128Case(
      {0x8000000000000000, kDec, /*width = */ 0, "9223372036854775808"});
  CheckInt128Case(
      {0x8000000000000000, kOct, /*width = */ 0, "1000000000000000000000"});
  CheckInt128Case(
      {0x8000000000000000, kHex, /*width = */ 0, "8000000000000000"});
  CheckInt128Case({std::numeric_limits<uint64_t>::max(), kDec,
                   /*width = */ 0, "18446744073709551615"});
  CheckInt128Case({std::numeric_limits<uint64_t>::max(), kOct,
                   /*width = */ 0, "1777777777777777777777"});
  CheckInt128Case({std::numeric_limits<uint64_t>::max(), kHex,
                   /*width = */ 0, "ffffffffffffffff"});
  CheckInt128Case(
      {absl::MakeInt128(1, 0), kDec, /*width = */ 0, "18446744073709551616"});
  CheckInt128Case(
      {absl::MakeInt128(1, 0), kOct, /*width = */ 0, "2000000000000000000000"});
  CheckInt128Case(
      {absl::MakeInt128(1, 0), kHex, /*width = */ 0, "10000000000000000"});
  CheckInt128Case({absl::MakeInt128(std::numeric_limits<int64_t>::max(),
                                    std::numeric_limits<uint64_t>::max()),
                   kDec, /*width = */ 0,
                   "170141183460469231731687303715884105727"});
  CheckInt128Case({absl::MakeInt128(std::numeric_limits<int64_t>::max(),
                                    std::numeric_limits<uint64_t>::max()),
                   kOct, /*width = */ 0,
                   "1777777777777777777777777777777777777777777"});
  CheckInt128Case({absl::MakeInt128(std::numeric_limits<int64_t>::max(),
                                    std::numeric_limits<uint64_t>::max()),
                   kHex, /*width = */ 0, "7fffffffffffffffffffffffffffffff"});
  CheckInt128Case({absl::MakeInt128(std::numeric_limits<int64_t>::min(), 0),
                   kDec, /*width = */ 0,
                   "-170141183460469231731687303715884105728"});
  CheckInt128Case({absl::MakeInt128(std::numeric_limits<int64_t>::min(), 0),
                   kOct, /*width = */ 0,
                   "2000000000000000000000000000000000000000000"});
  CheckInt128Case({absl::MakeInt128(std::numeric_limits<int64_t>::min(), 0),
                   kHex, /*width = */ 0, "80000000000000000000000000000000"});
  CheckInt128Case({-1, kDec, /*width = */ 0, "-1"});
  CheckInt128Case({-1, kOct, /*width = */ 0,
                   "3777777777777777777777777777777777777777777"});
  CheckInt128Case(
      {-1, kHex, /*width = */ 0, "ffffffffffffffffffffffffffffffff"});
  CheckInt128Case({-12345, kDec, /*width = */ 0, "-12345"});
  CheckInt128Case({-12345, kOct, /*width = */ 0,
                   "3777777777777777777777777777777777777747707"});
  CheckInt128Case(
      {-12345, kHex, /*width = */ 0, "ffffffffffffffffffffffffffffcfc7"});
}

std::vector<Int128TestCase> GetInt128FormatCases();
TEST(Int128, OStreamFormatTest) {
  for (const Int128TestCase& test_case : GetInt128FormatCases()) {
    CheckInt128Case(test_case);
  }
}

std::vector<Int128TestCase> GetInt128FormatCases() { __builtin_trap() /* STUB: not implemented */; }

std::vector<Uint128TestCase> GetUint128FormatCases() { __builtin_trap() /* STUB: not implemented */; }

}  // namespace
