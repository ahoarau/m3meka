// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "smoothing_mode.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::EnumDescriptor* SMOOTHING_MODE_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_smoothing_5fmode_2eproto() {
  protobuf_AddDesc_smoothing_5fmode_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "smoothing_mode.proto");
  GOOGLE_CHECK(file != NULL);
  SMOOTHING_MODE_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_smoothing_5fmode_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_smoothing_5fmode_2eproto() {
}

void protobuf_AddDesc_smoothing_5fmode_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024smoothing_mode.proto*^\n\016SMOOTHING_MODE"
    "\022\026\n\022SMOOTHING_MODE_OFF\020\000\022\027\n\023SMOOTHING_MO"
    "DE_SLEW\020\001\022\033\n\027SMOOTHING_MODE_MIN_JERK\020\002B\002"
    "H\001", 122);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "smoothing_mode.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_smoothing_5fmode_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_smoothing_5fmode_2eproto {
  StaticDescriptorInitializer_smoothing_5fmode_2eproto() {
    protobuf_AddDesc_smoothing_5fmode_2eproto();
  }
} static_descriptor_initializer_smoothing_5fmode_2eproto_;

const ::google::protobuf::EnumDescriptor* SMOOTHING_MODE_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SMOOTHING_MODE_descriptor_;
}
bool SMOOTHING_MODE_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
