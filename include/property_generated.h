// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PROPERTY_H_
#define FLATBUFFERS_GENERATED_PROPERTY_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 3 &&
              FLATBUFFERS_VERSION_REVISION == 3,
             "Non-compatible flatbuffers version included");

struct Property;
struct PropertyBuilder;

struct Property FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef PropertyBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_VALUE = 6,
    VT_TYPE = 8,
    VT_SUB_PROPERTIES = 10
  };
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  ::flatbuffers::String *mutable_name() {
    return GetPointer<::flatbuffers::String *>(VT_NAME);
  }
  const ::flatbuffers::String *value() const {
    return GetPointer<const ::flatbuffers::String *>(VT_VALUE);
  }
  ::flatbuffers::String *mutable_value() {
    return GetPointer<::flatbuffers::String *>(VT_VALUE);
  }
  const ::flatbuffers::String *type() const {
    return GetPointer<const ::flatbuffers::String *>(VT_TYPE);
  }
  ::flatbuffers::String *mutable_type() {
    return GetPointer<::flatbuffers::String *>(VT_TYPE);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<Property>> *sub_properties() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<Property>> *>(VT_SUB_PROPERTIES);
  }
  ::flatbuffers::Vector<::flatbuffers::Offset<Property>> *mutable_sub_properties() {
    return GetPointer<::flatbuffers::Vector<::flatbuffers::Offset<Property>> *>(VT_SUB_PROPERTIES);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_VALUE) &&
           verifier.VerifyString(value()) &&
           VerifyOffset(verifier, VT_TYPE) &&
           verifier.VerifyString(type()) &&
           VerifyOffset(verifier, VT_SUB_PROPERTIES) &&
           verifier.VerifyVector(sub_properties()) &&
           verifier.VerifyVectorOfTables(sub_properties()) &&
           verifier.EndTable();
  }
};

struct PropertyBuilder {
  typedef Property Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(Property::VT_NAME, name);
  }
  void add_value(::flatbuffers::Offset<::flatbuffers::String> value) {
    fbb_.AddOffset(Property::VT_VALUE, value);
  }
  void add_type(::flatbuffers::Offset<::flatbuffers::String> type) {
    fbb_.AddOffset(Property::VT_TYPE, type);
  }
  void add_sub_properties(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Property>>> sub_properties) {
    fbb_.AddOffset(Property::VT_SUB_PROPERTIES, sub_properties);
  }
  explicit PropertyBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Property> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Property>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Property> CreateProperty(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> value = 0,
    ::flatbuffers::Offset<::flatbuffers::String> type = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<Property>>> sub_properties = 0) {
  PropertyBuilder builder_(_fbb);
  builder_.add_sub_properties(sub_properties);
  builder_.add_type(type);
  builder_.add_value(value);
  builder_.add_name(name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Property> CreatePropertyDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *value = nullptr,
    const char *type = nullptr,
    const std::vector<::flatbuffers::Offset<Property>> *sub_properties = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto value__ = value ? _fbb.CreateString(value) : 0;
  auto type__ = type ? _fbb.CreateString(type) : 0;
  auto sub_properties__ = sub_properties ? _fbb.CreateVector<::flatbuffers::Offset<Property>>(*sub_properties) : 0;
  return CreateProperty(
      _fbb,
      name__,
      value__,
      type__,
      sub_properties__);
}

inline const Property *GetProperty(const void *buf) {
  return ::flatbuffers::GetRoot<Property>(buf);
}

inline const Property *GetSizePrefixedProperty(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<Property>(buf);
}

inline Property *GetMutableProperty(void *buf) {
  return ::flatbuffers::GetMutableRoot<Property>(buf);
}

inline Property *GetMutableSizePrefixedProperty(void *buf) {
  return ::flatbuffers::GetMutableSizePrefixedRoot<Property>(buf);
}

inline bool VerifyPropertyBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Property>(nullptr);
}

inline bool VerifySizePrefixedPropertyBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Property>(nullptr);
}

inline void FinishPropertyBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<Property> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedPropertyBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<Property> root) {
  fbb.FinishSizePrefixed(root);
}

#endif  // FLATBUFFERS_GENERATED_PROPERTY_H_