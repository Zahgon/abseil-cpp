//
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
//
#ifndef ABSL_STRINGS_INTERNAL_STR_FORMAT_EXTENSION_H_
#define ABSL_STRINGS_INTERNAL_STR_FORMAT_EXTENSION_H_


#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ostream>
#include <string>

#include "absl/base/config.h"
#include "absl/strings/internal/str_format/output.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

enum class FormatConversionChar : uint8_t;
enum class FormatConversionCharSet : uint64_t;
enum class LengthMod : std::uint8_t { h, hh, l, ll, L, j, z, t, q, none };

namespace str_format_internal {

class FormatRawSinkImpl {
 public:
  // Implicitly convert from any type that provides the hook function as
  // described above.
  template <typename T, decltype(str_format_internal::InvokeFlush(
                            std::declval<T*>(), string_view()))* = nullptr>
  FormatRawSinkImpl(T* raw)  // NOLINT
      : sink_(raw), write_(&FormatRawSinkImpl::Flush<T>) { __builtin_trap() /* STUB: not implemented */; }

  void Write(string_view s) { __builtin_trap() /* STUB: not implemented */; }

  template <typename T>
  static FormatRawSinkImpl Extract(T s) { __builtin_trap() /* STUB: not implemented */; }

 private:
  template <typename T>
  static void Flush(void* r, string_view s) { __builtin_trap() /* STUB: not implemented */; }

  void* sink_;
  void (*write_)(void*, string_view);
};

// An abstraction to which conversions write their string data.
class FormatSinkImpl {
 public:
  explicit FormatSinkImpl(FormatRawSinkImpl raw) : raw_(raw) { __builtin_trap() /* STUB: not implemented */; }

  ~FormatSinkImpl() { __builtin_trap() /* STUB: not implemented */; }

  void Flush() { __builtin_trap() /* STUB: not implemented */; }

  void Append(size_t n, char c) { __builtin_trap() /* STUB: not implemented */; }

  void Append(string_view v) { __builtin_trap() /* STUB: not implemented */; }

  size_t size() const { __builtin_trap() /* STUB: not implemented */; }

  // Put 'v' to 'sink' with specified width, precision, and left flag.
  bool PutPaddedString(string_view v, int width, int precision, bool left);

  template <typename T>
  T Wrap() { __builtin_trap() /* STUB: not implemented */; }

  template <typename T>
  static FormatSinkImpl* Extract(T* s) { __builtin_trap() /* STUB: not implemented */; }

 private:
  size_t Avail() const { __builtin_trap() /* STUB: not implemented */; }

  FormatRawSinkImpl raw_;
  size_t size_ = 0;
  char* pos_ = buf_;
  char buf_[1024];
};

enum class Flags : uint8_t {
  kBasic = 0,
  kLeft = 1 << 0,
  kShowPos = 1 << 1,
  kSignCol = 1 << 2,
  kAlt = 1 << 3,
  kZero = 1 << 4,
  // This is not a real flag. It just exists to turn off kBasic when no other
  // flags are set. This is for when width/precision are specified, or a length
  // modifier affects the behavior ("%lc").
  kNonBasic = 1 << 5,
};

constexpr Flags operator|(Flags a, Flags b) { return {}; }

constexpr bool FlagsContains(Flags haystack, Flags needle) { return {}; }

std::string FlagsToString(Flags v);

inline std::ostream& operator<<(std::ostream& os, Flags v) { __builtin_trap() /* STUB: not implemented */; }

// clang-format off
#define ABSL_INTERNAL_CONVERSION_CHARS_EXPAND_(X_VAL, X_SEP) \
  /* text */ \
  X_VAL(c) X_SEP X_VAL(s) X_SEP \
  /* ints */ \
  X_VAL(d) X_SEP X_VAL(i) X_SEP X_VAL(o) X_SEP \
  X_VAL(u) X_SEP X_VAL(x) X_SEP X_VAL(X) X_SEP \
  /* floats */ \
  X_VAL(f) X_SEP X_VAL(F) X_SEP X_VAL(e) X_SEP X_VAL(E) X_SEP \
  X_VAL(g) X_SEP X_VAL(G) X_SEP X_VAL(a) X_SEP X_VAL(A) X_SEP \
  /* misc */ \
  X_VAL(n) X_SEP X_VAL(p) X_SEP X_VAL(v)
// clang-format on

// This type should not be referenced, it exists only to provide labels
// internally that match the values declared in FormatConversionChar in
// str_format.h. This is meant to allow internal libraries to use the same
// declared interface type as the public interface
// (absl::StrFormatConversionChar) while keeping the definition in a public
// header.
// Internal libraries should use the form
// `FormatConversionCharInternal::c`, `FormatConversionCharInternal::kNone` for
// comparisons.  Use in switch statements is not recommended due to a bug in how
// gcc 4.9 -Wswitch handles declared but undefined enums.
struct FormatConversionCharInternal {
  FormatConversionCharInternal() = delete;

 private:
  // clang-format off
  enum class Enum : uint8_t {
    c, s,                    // text
    d, i, o, u, x, X,        // int
    f, F, e, E, g, G, a, A,  // float
    n, p, v,                    // misc
    kNone
  };
  // clang-format on
 public:
#define ABSL_INTERNAL_X_VAL(id)              \
  static constexpr FormatConversionChar id = \
      static_cast<FormatConversionChar>(Enum::id);
  ABSL_INTERNAL_CONVERSION_CHARS_EXPAND_(ABSL_INTERNAL_X_VAL, )
#undef ABSL_INTERNAL_X_VAL
  static constexpr FormatConversionChar kNone =
      static_cast<FormatConversionChar>(Enum::kNone);
};
// clang-format on

inline FormatConversionChar FormatConversionCharFromChar(char c) { __builtin_trap() /* STUB: not implemented */; }

inline bool FormatConversionCharIsUpper(FormatConversionChar c) { __builtin_trap() /* STUB: not implemented */; }

inline bool FormatConversionCharIsFloat(FormatConversionChar c) { __builtin_trap() /* STUB: not implemented */; }

inline char FormatConversionCharToChar(FormatConversionChar c) { __builtin_trap() /* STUB: not implemented */; }

// The associated char.
inline std::ostream& operator<<(std::ostream& os, FormatConversionChar v) { __builtin_trap() /* STUB: not implemented */; }

struct FormatConversionSpecImplFriend;

class FormatConversionSpecImpl {
 public:
  // Width and precision are not specified, no flags are set.
  bool is_basic() const { __builtin_trap() /* STUB: not implemented */; }
  bool has_left_flag() const { __builtin_trap() /* STUB: not implemented */; }
  bool has_show_pos_flag() const { __builtin_trap() /* STUB: not implemented */; }
  bool has_sign_col_flag() const { __builtin_trap() /* STUB: not implemented */; }
  bool has_alt_flag() const { __builtin_trap() /* STUB: not implemented */; }
  bool has_zero_flag() const { __builtin_trap() /* STUB: not implemented */; }

  LengthMod length_mod() const { __builtin_trap() /* STUB: not implemented */; }

  FormatConversionChar conversion_char() const { __builtin_trap() /* STUB: not implemented */; }

  void set_conversion_char(FormatConversionChar c) { __builtin_trap() /* STUB: not implemented */; }

  // Returns the specified width. If width is unspecfied, it returns a negative
  // value.
  int width() const { __builtin_trap() /* STUB: not implemented */; }
  // Returns the specified precision. If precision is unspecfied, it returns a
  // negative value.
  int precision() const { __builtin_trap() /* STUB: not implemented */; }

  template <typename T>
  T Wrap() { __builtin_trap() /* STUB: not implemented */; }

 private:
  friend struct str_format_internal::FormatConversionSpecImplFriend;
  FormatConversionChar conv_ = FormatConversionCharInternal::kNone;
  Flags flags_;
  LengthMod length_mod_ = LengthMod::none;
  int width_;
  int precision_;
};

struct FormatConversionSpecImplFriend final {
  static void SetFlags(Flags f, FormatConversionSpecImpl* conv) { __builtin_trap() /* STUB: not implemented */; }
  static void SetLengthMod(LengthMod l, FormatConversionSpecImpl* conv) { __builtin_trap() /* STUB: not implemented */; }
  static void SetConversionChar(FormatConversionChar c,
                                FormatConversionSpecImpl* conv) { __builtin_trap() /* STUB: not implemented */; }
  static void SetWidth(int w, FormatConversionSpecImpl* conv) { __builtin_trap() /* STUB: not implemented */; }
  static void SetPrecision(int p, FormatConversionSpecImpl* conv) { __builtin_trap() /* STUB: not implemented */; }
  static std::string FlagsToString(const FormatConversionSpecImpl& spec) { __builtin_trap() /* STUB: not implemented */; }
};

// Type safe OR operator.
// We need this for two reasons:
//  1. operator| on enums makes them decay to integers and the result is an
//     integer. We need the result to stay as an enum.
//  2. We use "enum class" which would not work even if we accepted the decay.
constexpr FormatConversionCharSet FormatConversionCharSetUnion(
    FormatConversionCharSet a) { return {}; }

template <typename... CharSet>
constexpr FormatConversionCharSet FormatConversionCharSetUnion(
    FormatConversionCharSet a, CharSet... rest) { return {}; }

constexpr uint64_t FormatConversionCharToConvInt(FormatConversionChar c) { return {}; }

constexpr uint64_t FormatConversionCharToConvInt(char conv) { return {}; }

constexpr FormatConversionCharSet FormatConversionCharToConvValue(char conv) { return {}; }

struct FormatConversionCharSetInternal {
#define ABSL_INTERNAL_CHAR_SET_CASE(c)         \
  static constexpr FormatConversionCharSet c = \
      FormatConversionCharToConvValue(#c[0]);
  ABSL_INTERNAL_CONVERSION_CHARS_EXPAND_(ABSL_INTERNAL_CHAR_SET_CASE, )
#undef ABSL_INTERNAL_CHAR_SET_CASE

  // Used for width/precision '*' specification.
  static constexpr FormatConversionCharSet kStar =
      FormatConversionCharToConvValue('*');

  static constexpr FormatConversionCharSet kIntegral =
      FormatConversionCharSetUnion(d, i, u, o, x, X);
  static constexpr FormatConversionCharSet kFloating =
      FormatConversionCharSetUnion(a, e, f, g, A, E, F, G);
  static constexpr FormatConversionCharSet kNumeric =
      FormatConversionCharSetUnion(kIntegral, kFloating);
  static constexpr FormatConversionCharSet kPointer = p;
};

// Type safe OR operator.
// We need this for two reasons:
//  1. operator| on enums makes them decay to integers and the result is an
//     integer. We need the result to stay as an enum.
//  2. We use "enum class" which would not work even if we accepted the decay.
constexpr FormatConversionCharSet operator|(FormatConversionCharSet a,
                                            FormatConversionCharSet b) { return {}; }

// Overloaded conversion functions to support absl::ParsedFormat.
// Get a conversion with a single character in it.
constexpr FormatConversionCharSet ToFormatConversionCharSet(char c) { return {}; }

// Get a conversion with a single character in it.
constexpr FormatConversionCharSet ToFormatConversionCharSet(
    FormatConversionCharSet c) { return {}; }

template <typename T>
void ToFormatConversionCharSet(T) = delete;

// Checks whether `c` exists in `set`.
constexpr bool Contains(FormatConversionCharSet set, char c) { return {}; }

// Checks whether all the characters in `c` are contained in `set`
constexpr bool Contains(FormatConversionCharSet set,
                        FormatConversionCharSet c) { return {}; }

// Checks whether all the characters in `c` are contained in `set`
constexpr bool Contains(FormatConversionCharSet set, FormatConversionChar c) { return {}; }

// Return capacity - used, clipped to a minimum of 0.
inline size_t Excess(size_t used, size_t capacity) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace str_format_internal

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_STRINGS_INTERNAL_STR_FORMAT_EXTENSION_H_
