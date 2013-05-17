/* Auto-generated by genmsg_cpp for file /home/meka/mekabot/m3meka/ros/shm_led_x2xn/msg/LEDX2XNRGB.msg */
#ifndef SHM_LED_X2XN_MESSAGE_LEDX2XNRGB_H
#define SHM_LED_X2XN_MESSAGE_LEDX2XNRGB_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace shm_led_x2xn
{
template <class ContainerAllocator>
struct LEDX2XNRGB_ {
  typedef LEDX2XNRGB_<ContainerAllocator> Type;

  LEDX2XNRGB_()
  : r(0)
  , g(0)
  , b(0)
  {
  }

  LEDX2XNRGB_(const ContainerAllocator& _alloc)
  : r(0)
  , g(0)
  , b(0)
  {
  }

  typedef uint32_t _r_type;
  uint32_t r;

  typedef uint32_t _g_type;
  uint32_t g;

  typedef uint32_t _b_type;
  uint32_t b;


  typedef boost::shared_ptr< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct LEDX2XNRGB
typedef  ::shm_led_x2xn::LEDX2XNRGB_<std::allocator<void> > LEDX2XNRGB;

typedef boost::shared_ptr< ::shm_led_x2xn::LEDX2XNRGB> LEDX2XNRGBPtr;
typedef boost::shared_ptr< ::shm_led_x2xn::LEDX2XNRGB const> LEDX2XNRGBConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace shm_led_x2xn

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> > {
  static const char* value() 
  {
    return "1d502d8fbb4c6ae56a393ae619466e53";
  }

  static const char* value(const  ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x1d502d8fbb4c6ae5ULL;
  static const uint64_t static_value2 = 0x6a393ae619466e53ULL;
};

template<class ContainerAllocator>
struct DataType< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> > {
  static const char* value() 
  {
    return "shm_led_x2xn/LEDX2XNRGB";
  }

  static const char* value(const  ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> > {
  static const char* value() 
  {
    return "uint32 r\n\
uint32 g\n\
uint32 b\n\
";
  }

  static const char* value(const  ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.r);
    stream.next(m.g);
    stream.next(m.b);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct LEDX2XNRGB_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::shm_led_x2xn::LEDX2XNRGB_<ContainerAllocator> & v) 
  {
    s << indent << "r: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.r);
    s << indent << "g: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.g);
    s << indent << "b: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.b);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SHM_LED_X2XN_MESSAGE_LEDX2XNRGB_H

