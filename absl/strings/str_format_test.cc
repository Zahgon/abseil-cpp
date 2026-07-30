// Copyright 2020 The Abseil Authors.
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

#include "absl/strings/str_format.h"

#include <cerrno>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "gtest/gtest.h"
#include "absl/base/config.h"
#include "absl/base/macros.h"
#include "absl/strings/cord.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace
ABSL_NAMESPACE_END
}  // namespace absl

namespace {
using FormatExtensionTest = ::testing::Test;

struct Point {
  friend absl::FormatConvertResult<absl::FormatConversionCharSet::kString |
                                   absl::FormatConversionCharSet::kIntegral |
                                   absl::FormatConversionCharSet::v>
  AbslFormatConvert(const Point& p, const absl::FormatConversionSpec& spec,
                    absl::FormatSink* s) { __builtin_trap() /* STUB: not implemented */; }

  int x = 10;
  int y = 20;
};

TEST_F(FormatExtensionTest, AbslFormatConvertExample) {
  Point p;
  EXPECT_EQ(absl::StrFormat("a %s z", p), "a x=10 y=20 z");
  EXPECT_EQ(absl::StrFormat("a %d z", p), "a 10,20 z");
  EXPECT_EQ(absl::StrFormat("a %v z", p), "a 10,20 z");

  // Typed formatting will fail to compile an invalid format.
  // StrFormat("%f", p);  // Does not compile.
  std::string actual;
  absl::UntypedFormatSpec f1("%f");
  // FormatUntyped will return false for bad character.
  EXPECT_FALSE(absl::FormatUntyped(&actual, f1, {absl::FormatArg(p)}));
}

struct PointStringify {
  template <typename FormatSink>
  friend void AbslStringify(FormatSink& sink, const PointStringify& p) { __builtin_trap() /* STUB: not implemented */; }

  double x = 10.0;
  double y = 20.0;
};

TEST_F(FormatExtensionTest, AbslStringifyExample) {
  PointStringify p;
  EXPECT_EQ(absl::StrFormat("a %v z", p), "a (10, 20) z");
}

struct PointStringifyUsingFormat {
  template <typename FormatSink>
  friend void AbslStringify(FormatSink& sink,
                            const PointStringifyUsingFormat& p) { __builtin_trap() /* STUB: not implemented */; }

  double x = 10.0;
  double y = 20.0;
};

TEST_F(FormatExtensionTest, AbslStringifyExampleUsingFormat) {
  PointStringifyUsingFormat p;
  EXPECT_EQ(absl::StrFormat("a %v z", p), "a (10, 20) z");
}

enum class EnumClassWithStringify { Many = 0, Choices = 1 };

template <typename Sink>
void AbslStringify(Sink& sink, EnumClassWithStringify e) { __builtin_trap() /* STUB: not implemented */; }

enum EnumWithStringify { Many, Choices };

template <typename Sink>
void AbslStringify(Sink& sink, EnumWithStringify e) { __builtin_trap() /* STUB: not implemented */; }

TEST_F(FormatExtensionTest, AbslStringifyWithEnumWithV) {
  const auto e_class = EnumClassWithStringify::Choices;
  EXPECT_EQ(absl::StrFormat("My choice is %v", e_class),
            "My choice is Choices");

  const auto e = EnumWithStringify::Choices;
  EXPECT_EQ(absl::StrFormat("My choice is %v", e), "My choice is Choices");
}

TEST_F(FormatExtensionTest, AbslStringifyEnumWithD) {
  const auto e_class = EnumClassWithStringify::Many;
  EXPECT_EQ(absl::StrFormat("My choice is %d", e_class), "My choice is 0");

  const auto e = EnumWithStringify::Choices;
  EXPECT_EQ(absl::StrFormat("My choice is %d", e), "My choice is 1");
}

enum class EnumWithLargerValue { x = 32 };

template <typename Sink>
void AbslStringify(Sink& sink, EnumWithLargerValue e) { __builtin_trap() /* STUB: not implemented */; }

TEST_F(FormatExtensionTest, AbslStringifyEnumOtherSpecifiers) {
  const auto e = EnumWithLargerValue::x;
  EXPECT_EQ(absl::StrFormat("My choice is %g", e), "My choice is 32");
  EXPECT_EQ(absl::StrFormat("My choice is %x", e), "My choice is 20");
}

}  // namespace

// Some codegen thunks that we can use to easily dump the generated assembly for
// different StrFormat calls.

std::string CodegenAbslStrFormatInt(int i) { __builtin_trap() /* STUB: not implemented */; }

std::string CodegenAbslStrFormatIntStringInt64(int i, const std::string& s,
                                               int64_t i64) { __builtin_trap() /* STUB: not implemented */; }

void CodegenAbslStrAppendFormatInt(std::string* out, int i) { __builtin_trap() /* STUB: not implemented */; }

void CodegenAbslStrAppendFormatIntStringInt64(std::string* out, int i,
                                              const std::string& s,
                                              int64_t i64) { __builtin_trap() /* STUB: not implemented */; }
