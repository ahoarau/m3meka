// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: omnibase_shm.proto

#ifndef PROTOBUF_omnibase_5fshm_2eproto__INCLUDED
#define PROTOBUF_omnibase_5fshm_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include "component_base.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_omnibase_5fshm_2eproto();
void protobuf_AssignDesc_omnibase_5fshm_2eproto();
void protobuf_ShutdownFile_omnibase_5fshm_2eproto();

class M3OmnibaseShmStatus;
class M3OmnibaseShmCommand;
class M3OmnibaseShmParam;

// ===================================================================

class M3OmnibaseShmStatus : public ::google::protobuf::Message {
 public:
  M3OmnibaseShmStatus();
  virtual ~M3OmnibaseShmStatus();
  
  M3OmnibaseShmStatus(const M3OmnibaseShmStatus& from);
  
  inline M3OmnibaseShmStatus& operator=(const M3OmnibaseShmStatus& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const M3OmnibaseShmStatus& default_instance();
  
  void Swap(M3OmnibaseShmStatus* other);
  
  // implements Message ----------------------------------------------
  
  M3OmnibaseShmStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const M3OmnibaseShmStatus& from);
  void MergeFrom(const M3OmnibaseShmStatus& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional .M3BaseStatus base = 1;
  inline bool has_base() const;
  inline void clear_base();
  static const int kBaseFieldNumber = 1;
  inline const ::M3BaseStatus& base() const;
  inline ::M3BaseStatus* mutable_base();
  inline ::M3BaseStatus* release_base();
  
  // optional double test = 2;
  inline bool has_test() const;
  inline void clear_test();
  static const int kTestFieldNumber = 2;
  inline double test() const;
  inline void set_test(double value);
  
  // @@protoc_insertion_point(class_scope:M3OmnibaseShmStatus)
 private:
  inline void set_has_base();
  inline void clear_has_base();
  inline void set_has_test();
  inline void clear_has_test();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::M3BaseStatus* base_;
  double test_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_omnibase_5fshm_2eproto();
  friend void protobuf_AssignDesc_omnibase_5fshm_2eproto();
  friend void protobuf_ShutdownFile_omnibase_5fshm_2eproto();
  
  void InitAsDefaultInstance();
  static M3OmnibaseShmStatus* default_instance_;
};
// -------------------------------------------------------------------

class M3OmnibaseShmCommand : public ::google::protobuf::Message {
 public:
  M3OmnibaseShmCommand();
  virtual ~M3OmnibaseShmCommand();
  
  M3OmnibaseShmCommand(const M3OmnibaseShmCommand& from);
  
  inline M3OmnibaseShmCommand& operator=(const M3OmnibaseShmCommand& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const M3OmnibaseShmCommand& default_instance();
  
  void Swap(M3OmnibaseShmCommand* other);
  
  // implements Message ----------------------------------------------
  
  M3OmnibaseShmCommand* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const M3OmnibaseShmCommand& from);
  void MergeFrom(const M3OmnibaseShmCommand& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional double test = 1;
  inline bool has_test() const;
  inline void clear_test();
  static const int kTestFieldNumber = 1;
  inline double test() const;
  inline void set_test(double value);
  
  // @@protoc_insertion_point(class_scope:M3OmnibaseShmCommand)
 private:
  inline void set_has_test();
  inline void clear_has_test();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double test_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_omnibase_5fshm_2eproto();
  friend void protobuf_AssignDesc_omnibase_5fshm_2eproto();
  friend void protobuf_ShutdownFile_omnibase_5fshm_2eproto();
  
  void InitAsDefaultInstance();
  static M3OmnibaseShmCommand* default_instance_;
};
// -------------------------------------------------------------------

class M3OmnibaseShmParam : public ::google::protobuf::Message {
 public:
  M3OmnibaseShmParam();
  virtual ~M3OmnibaseShmParam();
  
  M3OmnibaseShmParam(const M3OmnibaseShmParam& from);
  
  inline M3OmnibaseShmParam& operator=(const M3OmnibaseShmParam& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const M3OmnibaseShmParam& default_instance();
  
  void Swap(M3OmnibaseShmParam* other);
  
  // implements Message ----------------------------------------------
  
  M3OmnibaseShmParam* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const M3OmnibaseShmParam& from);
  void MergeFrom(const M3OmnibaseShmParam& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional double test = 1;
  inline bool has_test() const;
  inline void clear_test();
  static const int kTestFieldNumber = 1;
  inline double test() const;
  inline void set_test(double value);
  
  // @@protoc_insertion_point(class_scope:M3OmnibaseShmParam)
 private:
  inline void set_has_test();
  inline void clear_has_test();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double test_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_omnibase_5fshm_2eproto();
  friend void protobuf_AssignDesc_omnibase_5fshm_2eproto();
  friend void protobuf_ShutdownFile_omnibase_5fshm_2eproto();
  
  void InitAsDefaultInstance();
  static M3OmnibaseShmParam* default_instance_;
};
// ===================================================================


// ===================================================================

// M3OmnibaseShmStatus

// optional .M3BaseStatus base = 1;
inline bool M3OmnibaseShmStatus::has_base() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void M3OmnibaseShmStatus::set_has_base() {
  _has_bits_[0] |= 0x00000001u;
}
inline void M3OmnibaseShmStatus::clear_has_base() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void M3OmnibaseShmStatus::clear_base() {
  if (base_ != NULL) base_->::M3BaseStatus::Clear();
  clear_has_base();
}
inline const ::M3BaseStatus& M3OmnibaseShmStatus::base() const {
  return base_ != NULL ? *base_ : *default_instance_->base_;
}
inline ::M3BaseStatus* M3OmnibaseShmStatus::mutable_base() {
  set_has_base();
  if (base_ == NULL) base_ = new ::M3BaseStatus;
  return base_;
}
inline ::M3BaseStatus* M3OmnibaseShmStatus::release_base() {
  clear_has_base();
  ::M3BaseStatus* temp = base_;
  base_ = NULL;
  return temp;
}

// optional double test = 2;
inline bool M3OmnibaseShmStatus::has_test() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void M3OmnibaseShmStatus::set_has_test() {
  _has_bits_[0] |= 0x00000002u;
}
inline void M3OmnibaseShmStatus::clear_has_test() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void M3OmnibaseShmStatus::clear_test() {
  test_ = 0;
  clear_has_test();
}
inline double M3OmnibaseShmStatus::test() const {
  return test_;
}
inline void M3OmnibaseShmStatus::set_test(double value) {
  set_has_test();
  test_ = value;
}

// -------------------------------------------------------------------

// M3OmnibaseShmCommand

// optional double test = 1;
inline bool M3OmnibaseShmCommand::has_test() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void M3OmnibaseShmCommand::set_has_test() {
  _has_bits_[0] |= 0x00000001u;
}
inline void M3OmnibaseShmCommand::clear_has_test() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void M3OmnibaseShmCommand::clear_test() {
  test_ = 0;
  clear_has_test();
}
inline double M3OmnibaseShmCommand::test() const {
  return test_;
}
inline void M3OmnibaseShmCommand::set_test(double value) {
  set_has_test();
  test_ = value;
}

// -------------------------------------------------------------------

// M3OmnibaseShmParam

// optional double test = 1;
inline bool M3OmnibaseShmParam::has_test() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void M3OmnibaseShmParam::set_has_test() {
  _has_bits_[0] |= 0x00000001u;
}
inline void M3OmnibaseShmParam::clear_has_test() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void M3OmnibaseShmParam::clear_test() {
  test_ = 0;
  clear_has_test();
}
inline double M3OmnibaseShmParam::test() const {
  return test_;
}
inline void M3OmnibaseShmParam::set_test(double value) {
  set_has_test();
  test_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_omnibase_5fshm_2eproto__INCLUDED
