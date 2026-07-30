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

#include "absl/strings/cord.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/endian.h"
#include "absl/base/internal/hardening.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/macros.h"
#include "absl/base/nullability.h"
#include "absl/base/optimization.h"
#include "absl/container/inlined_vector.h"
#include "absl/crc/crc32c.h"
#include "absl/crc/internal/crc_cord_state.h"
#include "absl/functional/function_ref.h"
#include "absl/strings/cord_buffer.h"
#include "absl/strings/escaping.h"
#include "absl/strings/internal/append_and_overwrite.h"
#include "absl/strings/internal/cord_data_edge.h"
#include "absl/strings/internal/cord_internal.h"
#include "absl/strings/internal/cord_rep_btree.h"
#include "absl/strings/internal/cord_rep_crc.h"
#include "absl/strings/internal/cord_rep_flat.h"
#include "absl/strings/internal/cordz_update_tracker.h"
#include "absl/strings/match.h"
#include "absl/strings/resize_and_overwrite.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "absl/types/span.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

using ::absl::cord_internal::CordRep;
using ::absl::cord_internal::CordRepBtree;
using ::absl::cord_internal::CordRepCrc;
using ::absl::cord_internal::CordRepExternal;
using ::absl::cord_internal::CordRepFlat;
using ::absl::cord_internal::CordRepSubstring;
using ::absl::cord_internal::CordzUpdateTracker;
using ::absl::cord_internal::InlineData;
using ::absl::cord_internal::kMaxBytesToCopy;
using ::absl::cord_internal::kMaxFlatLength;
using ::absl::cord_internal::kMinFlatLength;

static void DumpNode(CordRep* absl_nonnull nonnull_rep, bool include_data,
                     std::ostream* absl_nonnull os, int indent = 0);
static bool VerifyNode(CordRep* absl_nonnull root,
                       CordRep* absl_nonnull start_node);

static inline CordRep* absl_nullable VerifyTree(CordRep* absl_nullable node) { __builtin_trap() /* STUB: not implemented */; }

static CordRepFlat* absl_nonnull CreateFlat(const char* absl_nonnull data,
                                            size_t length, size_t alloc_hint) { __builtin_trap() /* STUB: not implemented */; }

// Creates a new flat or Btree out of the specified array.
// The returned node has a refcount of 1.
static CordRep* absl_nonnull NewBtree(const char* absl_nonnull data,
                                      size_t length, size_t alloc_hint) { __builtin_trap() /* STUB: not implemented */; }

// Create a new tree out of the specified array.
// The returned node has a refcount of 1.
static CordRep* absl_nullable NewTree(const char* absl_nullable data,
                                      size_t length, size_t alloc_hint) { __builtin_trap() /* STUB: not implemented */; }

namespace cord_internal {

void InitializeCordRepExternal(absl::string_view data,
                               CordRepExternal* absl_nonnull rep) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace cord_internal

// Creates a CordRep from the provided string. If the string is large enough,
// and not wasteful, we move the string into an external cord rep, preserving
// the already allocated string contents.
// Requires the provided string length to be larger than `kMaxInline`.
static CordRep* absl_nonnull CordRepFromString(std::string&& src) { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------
// Cord::InlineRep functions

// Returns `rep` converted into a CordRepBtree.
// Directly returns `rep` if `rep` is already a CordRepBtree.
static CordRepBtree* absl_nonnull ForceBtree(CordRep* rep) { __builtin_trap() /* STUB: not implemented */; }

void Cord::InlineRep::AppendTreeToInlined(CordRep* absl_nonnull tree,
                                          MethodIdentifier method) {
  assert(!is_tree());
  if (!data_.is_empty()) {
    CordRepFlat* flat = MakeFlatWithExtraCapacity(0);
    tree = CordRepBtree::Append(CordRepBtree::Create(flat), tree);
  }
  EmplaceTree(tree, method);
}

void Cord::InlineRep::AppendTreeToTree(CordRep* absl_nonnull tree,
                                       MethodIdentifier method) {
  assert(is_tree());
  const CordzUpdateScope scope(data_.cordz_info(), method);
  tree = CordRepBtree::Append(ForceBtree(data_.as_tree()), tree);
  SetTree(tree, scope);
}

void Cord::InlineRep::AppendTree(CordRep* absl_nonnull tree,
                                 MethodIdentifier method) {
  assert(tree != nullptr);
  assert(tree->length != 0);
  assert(!tree->IsCrc());
  if (data_.is_tree()) {
    AppendTreeToTree(tree, method);
  } else {
    AppendTreeToInlined(tree, method);
  }
}

void Cord::InlineRep::PrependTreeToInlined(CordRep* absl_nonnull tree,
                                           MethodIdentifier method) {
  assert(!is_tree());
  if (!data_.is_empty()) {
    CordRepFlat* flat = MakeFlatWithExtraCapacity(0);
    tree = CordRepBtree::Prepend(CordRepBtree::Create(flat), tree);
  }
  EmplaceTree(tree, method);
}

void Cord::InlineRep::PrependTreeToTree(CordRep* absl_nonnull tree,
                                        MethodIdentifier method) {
  assert(is_tree());
  const CordzUpdateScope scope(data_.cordz_info(), method);
  tree = CordRepBtree::Prepend(ForceBtree(data_.as_tree()), tree);
  SetTree(tree, scope);
}

void Cord::InlineRep::PrependTree(CordRep* absl_nonnull tree,
                                  MethodIdentifier method) {
  assert(tree != nullptr);
  assert(tree->length != 0);
  assert(!tree->IsCrc());
  if (data_.is_tree()) {
    PrependTreeToTree(tree, method);
  } else {
    PrependTreeToInlined(tree, method);
  }
}

// Searches for a non-full flat node at the rightmost leaf of the tree. If a
// suitable leaf is found, the function will update the length field for all
// nodes to account for the size increase. The append region address will be
// written to region and the actual size increase will be written to size.
static inline bool PrepareAppendRegion(CordRep* absl_nonnull root,
                                       char* absl_nullable* absl_nonnull region,
                                       size_t* absl_nonnull size,
                                       size_t max_length) {
  if (root->IsBtree() && root->refcount.IsOne()) {
    Span<char> span = root->btree()->GetAppendBuffer(max_length);
    if (!span.empty()) {
      *region = span.data();
      *size = span.size();
      return true;
    }
  }

  CordRep* dst = root;
  if (!dst->IsFlat() || !dst->refcount.IsOne()) {
    *region = nullptr;
    *size = 0;
    return false;
  }

  const size_t in_use = dst->length;
  const size_t capacity = dst->flat()->Capacity();
  if (in_use == capacity) {
    *region = nullptr;
    *size = 0;
    return false;
  }

  const size_t size_increase = std::min(capacity - in_use, max_length);
  dst->length += size_increase;

  *region = dst->flat()->Data() + in_use;
  *size = size_increase;
  return true;
}

void Cord::InlineRep::AssignSlow(const Cord::InlineRep& src) { __builtin_trap() /* STUB: not implemented */; }

void Cord::InlineRep::UnrefTree() { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------
// Constructors and destructors

Cord::Cord(absl::string_view src, MethodIdentifier method)
    : contents_(InlineData::kDefaultInit) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, Cord::EnableIfString<T>>
Cord::Cord(T&& src) : contents_(InlineData::kDefaultInit) { __builtin_trap() /* STUB: not implemented */; }

template Cord::Cord(std::string&& src);

// The destruction code is separate so that the compiler can determine
// that it does not need to call the destructor on a moved-from Cord.
void Cord::DestroyCordSlow() { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------
// Mutators

void Cord::Clear() { __builtin_trap() /* STUB: not implemented */; }

Cord& Cord::AssignLargeString(std::string&& src) { __builtin_trap() /* STUB: not implemented */; }

Cord& Cord::operator=(absl::string_view src) { __builtin_trap() /* STUB: not implemented */; }

// TODO(sanjay): Move to Cord::InlineRep section of file.  For now,
// we keep it here to make diffs easier.
void Cord::InlineRep::AppendArray(absl::string_view src,
                                  MethodIdentifier method) { __builtin_trap() /* STUB: not implemented */; }

inline CordRep* absl_nonnull Cord::TakeRep() const& { __builtin_trap() /* STUB: not implemented */; }

inline CordRep* absl_nonnull Cord::TakeRep() && { __builtin_trap() /* STUB: not implemented */; }

template <typename C>
inline void Cord::AppendImpl(C&& src) { __builtin_trap() /* STUB: not implemented */; }

static CordRep::ExtractResult ExtractAppendBuffer(CordRep* absl_nonnull rep,
                                                  size_t min_capacity) {
  switch (rep->tag) {
    case cord_internal::BTREE:
      return CordRepBtree::ExtractAppendBuffer(rep->btree(), min_capacity);
    default:
      if (rep->IsFlat() && rep->refcount.IsOne() &&
          rep->flat()->Capacity() - rep->length >= min_capacity) {
        return {nullptr, rep};
      }
      return {rep, nullptr};
  }
}

static CordBuffer CreateAppendBuffer(InlineData& data, size_t block_size,
                                     size_t capacity) { __builtin_trap() /* STUB: not implemented */; }

CordBuffer Cord::GetAppendBufferSlowPath(size_t block_size, size_t capacity,
                                         size_t min_capacity) { __builtin_trap() /* STUB: not implemented */; }

void Cord::Append(const Cord& src) { __builtin_trap() /* STUB: not implemented */; }

void Cord::Append(Cord&& src) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, Cord::EnableIfString<T>>
void Cord::Append(T&& src) { __builtin_trap() /* STUB: not implemented */; }

template void Cord::Append(std::string&& src);

void Cord::Prepend(const Cord& src) { __builtin_trap() /* STUB: not implemented */; }

void Cord::PrependArray(absl::string_view src, MethodIdentifier method) { __builtin_trap() /* STUB: not implemented */; }

void Cord::AppendPrecise(absl::string_view src, MethodIdentifier method) { __builtin_trap() /* STUB: not implemented */; }

void Cord::PrependPrecise(absl::string_view src, MethodIdentifier method) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, Cord::EnableIfString<T>>
inline void Cord::Prepend(T&& src) { __builtin_trap() /* STUB: not implemented */; }

template void Cord::Prepend(std::string&& src);

void Cord::RemovePrefix(size_t n) { __builtin_trap() /* STUB: not implemented */; }

void Cord::RemoveSuffix(size_t n) { __builtin_trap() /* STUB: not implemented */; }

Cord Cord::Subcord(size_t pos, size_t new_size) const { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------
// Comparators

namespace {

int ClampResult(int memcmp_res) { __builtin_trap() /* STUB: not implemented */; }

int CompareChunks(absl::string_view* absl_nonnull lhs,
                  absl::string_view* absl_nonnull rhs,
                  size_t* absl_nonnull size_to_compare) { __builtin_trap() /* STUB: not implemented */; }

// This overload set computes comparison results from memcmp result. This
// interface is used inside GenericCompare below. Different implementations
// are specialized for int and bool. For int we clamp result to {-1, 0, 1}
// set. For bool we just interested in "value == 0".
template <typename ResultType>
ResultType ComputeCompareResult(int memcmp_res) { __builtin_trap() /* STUB: not implemented */; }
template <>
bool ComputeCompareResult<bool>(int memcmp_res) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

// Helper routine. Locates the first flat or external chunk of the Cord without
// initializing the iterator, and returns a string_view referencing the data.
inline absl::string_view Cord::InlineRep::FindFlatStartPiece() const { __builtin_trap() /* STUB: not implemented */; }

void Cord::SetCrcCordState(crc_internal::CrcCordState state) { __builtin_trap() /* STUB: not implemented */; }

void Cord::SetExpectedChecksum(uint32_t crc) { __builtin_trap() /* STUB: not implemented */; }

const crc_internal::CrcCordState* absl_nullable Cord::MaybeGetCrcCordState()
    const { __builtin_trap() /* STUB: not implemented */; }

std::optional<uint32_t> Cord::ExpectedChecksum() const { __builtin_trap() /* STUB: not implemented */; }

inline int Cord::CompareSlowPath(absl::string_view rhs, size_t compared_size,
                                 size_t size_to_compare) const { __builtin_trap() /* STUB: not implemented */; }

inline int Cord::CompareSlowPath(const Cord& rhs, size_t compared_size,
                                 size_t size_to_compare) const { __builtin_trap() /* STUB: not implemented */; }

inline absl::string_view Cord::GetFirstChunk(const Cord& c) { __builtin_trap() /* STUB: not implemented */; }
inline absl::string_view Cord::GetFirstChunk(absl::string_view sv) { __builtin_trap() /* STUB: not implemented */; }

// Compares up to 'size_to_compare' bytes of 'lhs' with 'rhs'. It is assumed
// that 'size_to_compare' is greater that size of smallest of first chunks.
template <typename ResultType, typename RHS>
ResultType GenericCompare(const Cord& lhs, const RHS& rhs,
                          size_t size_to_compare) { __builtin_trap() /* STUB: not implemented */; }

bool Cord::EqualsImpl(absl::string_view rhs, size_t size_to_compare) const { __builtin_trap() /* STUB: not implemented */; }

bool Cord::EqualsImpl(const Cord& rhs, size_t size_to_compare) const { __builtin_trap() /* STUB: not implemented */; }

template <typename RHS>
inline int SharedCompareImpl(const Cord& lhs, const RHS& rhs) { __builtin_trap() /* STUB: not implemented */; }

int Cord::Compare(absl::string_view rhs) const { __builtin_trap() /* STUB: not implemented */; }

int Cord::CompareImpl(const Cord& rhs) const { __builtin_trap() /* STUB: not implemented */; }

bool Cord::EndsWith(absl::string_view rhs) const { __builtin_trap() /* STUB: not implemented */; }

bool Cord::EndsWith(const Cord& rhs) const { __builtin_trap() /* STUB: not implemented */; }

// --------------------------------------------------------------------
// Misc.

Cord::operator std::string() const { __builtin_trap() /* STUB: not implemented */; }

void CopyCordToString(const Cord& src, std::string* absl_nonnull dst) { __builtin_trap() /* STUB: not implemented */; }

void AppendCordToString(const Cord& src, std::string* absl_nonnull dst) { __builtin_trap() /* STUB: not implemented */; }

void Cord::CopyToArraySlowPath(char* absl_nonnull dst) const { __builtin_trap() /* STUB: not implemented */; }

size_t CopyCordToSpan(const Cord& src, absl::Span<char> dst) { __builtin_trap() /* STUB: not implemented */; }

Cord Cord::ChunkIterator::AdvanceAndReadBytes(size_t n) { __builtin_trap() /* STUB: not implemented */; }

char Cord::operator[](size_t i) const { __builtin_trap() /* STUB: not implemented */; }

namespace {

// Tests whether the sequence of chunks beginning at `position` starts with
// `needle`.
//
// REQUIRES: remaining `absl::Cord` starting at `position` is greater than or
// equal to `needle.size()`.
bool IsSubstringInCordAt(absl::Cord::CharIterator position,
                         absl::string_view needle) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

// A few options how this could be implemented:
// (a) Flatten the Cord and find, i.e.
//       haystack.Flatten().find(needle)
//     For large 'haystack' (where Cord makes sense to be used), this copies
//     the whole 'haystack' and can be slow.
// (b) Use std::search, i.e.
//       std::search(haystack.char_begin(), haystack.char_end(),
//                   needle.begin(), needle.end())
//     This avoids the copy, but compares one byte at a time, and branches a
//     lot every time it has to advance. It is also not possible to use
//     std::search as is, because CharIterator is only an input iterator, not a
//     forward iterator.
// (c) Use string_view::find in each fragment, and specifically handle fragment
//     boundaries.
//
// This currently implements option (b).
absl::Cord::CharIterator absl::Cord::FindImpl(CharIterator it,
                                              absl::string_view needle) const { __builtin_trap() /* STUB: not implemented */; }

absl::Cord::CharIterator absl::Cord::Find(absl::string_view needle) const { __builtin_trap() /* STUB: not implemented */; }

namespace {

// Tests whether the sequence of chunks beginning at `haystack` starts with the
// sequence of chunks beginning at `needle_begin` and extending to `needle_end`.
//
// REQUIRES: remaining `absl::Cord` starting at `position` is greater than or
// equal to `needle_end - needle_begin` and `advance`.
bool IsSubcordInCordAt(absl::Cord::CharIterator haystack,
                       absl::Cord::CharIterator needle_begin,
                       absl::Cord::CharIterator needle_end) { __builtin_trap() /* STUB: not implemented */; }

// Tests whether the sequence of chunks beginning at `position` starts with the
// cord `needle`.
//
// REQUIRES: remaining `absl::Cord` starting at `position` is greater than or
// equal to `needle.size()`.
bool IsSubcordInCordAt(absl::Cord::CharIterator position,
                       const absl::Cord& needle) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

absl::Cord::CharIterator absl::Cord::Find(const absl::Cord& needle) const { __builtin_trap() /* STUB: not implemented */; }

bool Cord::Contains(absl::string_view rhs) const { __builtin_trap() /* STUB: not implemented */; }

bool Cord::Contains(const absl::Cord& rhs) const { __builtin_trap() /* STUB: not implemented */; }

absl::string_view Cord::FlattenSlowPath() { __builtin_trap() /* STUB: not implemented */; }

/* static */ bool Cord::GetFlatAux(CordRep* absl_nonnull rep,
                                   absl::string_view* absl_nonnull fragment) {
  assert(rep != nullptr);
  if (rep->length == 0) {
    *fragment = absl::string_view();
    return true;
  }
  rep = cord_internal::SkipCrcNode(rep);
  if (rep->IsFlat()) {
    *fragment = absl::string_view(rep->flat()->Data(), rep->length);
    return true;
  } else if (rep->IsExternal()) {
    *fragment = absl::string_view(rep->external()->base, rep->length);
    return true;
  } else if (rep->IsBtree()) {
    return rep->btree()->IsFlat(fragment);
  } else if (rep->IsSubstring()) {
    CordRep* child = rep->substring()->child;
    if (child->IsFlat()) {
      *fragment = absl::string_view(
          child->flat()->Data() + rep->substring()->start, rep->length);
      return true;
    } else if (child->IsExternal()) {
      *fragment = absl::string_view(
          child->external()->base + rep->substring()->start, rep->length);
      return true;
    } else if (child->IsBtree()) {
      return child->btree()->IsFlat(rep->substring()->start, rep->length,
                                    fragment);
    }
  }
  return false;
}

/* static */ void Cord::ForEachChunkAux(
    absl::cord_internal::CordRep* absl_nonnull rep,
    absl::FunctionRef<void(absl::string_view)> callback) { __builtin_trap() /* STUB: not implemented */; }

static void DumpNode(CordRep* absl_nonnull nonnull_rep, bool include_data,
                     std::ostream* absl_nonnull os, int indent) {
  CordRep* rep = nonnull_rep;
  const int kIndentStep = 1;
  for (;;) {
    *os << std::setw(3) << (rep == nullptr ? 0 : rep->refcount.Get());
    *os << " " << std::setw(7) << (rep == nullptr ? 0 : rep->length);
    *os << " [";
    if (include_data) *os << static_cast<void*>(rep);
    *os << "]";
    *os << " " << std::setw(indent) << "";
    bool leaf = false;
    if (rep == nullptr) {
      *os << "NULL\n";
      leaf = true;
    } else if (rep->IsCrc()) {
      *os << "CRC crc=" << rep->crc()->crc_cord_state.Checksum() << "\n";
      indent += kIndentStep;
      rep = rep->crc()->child;
    } else if (rep->IsSubstring()) {
      *os << "SUBSTRING @ " << rep->substring()->start << "\n";
      indent += kIndentStep;
      rep = rep->substring()->child;
    } else {  // Leaf or ring
      leaf = true;
      if (rep->IsExternal()) {
        *os << "EXTERNAL [";
        if (include_data)
          *os << absl::CEscape(
              absl::string_view(rep->external()->base, rep->length));
        *os << "]\n";
      } else if (rep->IsFlat()) {
        *os << "FLAT cap=" << rep->flat()->Capacity() << " [";
        if (include_data)
          *os << absl::CEscape(
              absl::string_view(rep->flat()->Data(), rep->length));
        *os << "]\n";
      } else {
        CordRepBtree::Dump(rep, /*label=*/"", include_data, *os);
      }
    }
    if (leaf) {
      break;
    }
  }
}

static std::string ReportError(CordRep* absl_nonnull root,
                               CordRep* absl_nonnull node) {
  std::ostringstream buf;
  buf << "Error at node " << node << " in:";
  DumpNode(root, true, &buf);
  return buf.str();
}

static bool VerifyNode(CordRep* absl_nonnull root,
                       CordRep* absl_nonnull start_node) {
  absl::InlinedVector<CordRep* absl_nonnull, 2> worklist;
  worklist.push_back(start_node);
  do {
    CordRep* node = worklist.back();
    worklist.pop_back();

    ABSL_INTERNAL_CHECK(node != nullptr, ReportError(root, node));
    if (node != root) {
      ABSL_INTERNAL_CHECK(node->length != 0, ReportError(root, node));
      ABSL_INTERNAL_CHECK(!node->IsCrc(), ReportError(root, node));
    }

    if (node->IsFlat()) {
      ABSL_INTERNAL_CHECK(node->length <= node->flat()->Capacity(),
                          ReportError(root, node));
    } else if (node->IsExternal()) {
      ABSL_INTERNAL_CHECK(node->external()->base != nullptr,
                          ReportError(root, node));
    } else if (node->IsSubstring()) {
      ABSL_INTERNAL_CHECK(
          node->substring()->start < node->substring()->child->length,
          ReportError(root, node));
      ABSL_INTERNAL_CHECK(node->substring()->start + node->length <=
                              node->substring()->child->length,
                          ReportError(root, node));
    } else if (node->IsCrc()) {
      ABSL_INTERNAL_CHECK(
          node->crc()->child != nullptr || node->crc()->length == 0,
          ReportError(root, node));
      if (node->crc()->child != nullptr) {
        ABSL_INTERNAL_CHECK(node->crc()->length == node->crc()->child->length,
                            ReportError(root, node));
        worklist.push_back(node->crc()->child);
      }
    }
  } while (!worklist.empty());
  return true;
}

std::ostream& operator<<(std::ostream& out, const Cord& cord) { __builtin_trap() /* STUB: not implemented */; }

namespace strings_internal {
size_t CordTestAccess::FlatOverhead() { __builtin_trap() /* STUB: not implemented */; }
size_t CordTestAccess::MaxFlatLength() { __builtin_trap() /* STUB: not implemented */; }
size_t CordTestAccess::FlatTagToLength(uint8_t tag) { __builtin_trap() /* STUB: not implemented */; }
uint8_t CordTestAccess::LengthToTag(size_t s) { __builtin_trap() /* STUB: not implemented */; }
size_t CordTestAccess::SizeofCordRepExternal() { __builtin_trap() /* STUB: not implemented */; }
size_t CordTestAccess::SizeofCordRepSubstring() { __builtin_trap() /* STUB: not implemented */; }
}  // namespace strings_internal
ABSL_NAMESPACE_END
}  // namespace absl
