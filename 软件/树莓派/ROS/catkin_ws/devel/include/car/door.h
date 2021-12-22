// Generated by gencpp from file car/door.msg
// DO NOT EDIT!


#ifndef CAR_MESSAGE_DOOR_H
#define CAR_MESSAGE_DOOR_H

#include <ros/service_traits.h>


#include <car/doorRequest.h>
#include <car/doorResponse.h>


namespace car
{

struct door
{

typedef doorRequest Request;
typedef doorResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct door
} // namespace car


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::car::door > {
  static const char* value()
  {
    return "561098128dce463abb21b321b22f8a07";
  }

  static const char* value(const ::car::door&) { return value(); }
};

template<>
struct DataType< ::car::door > {
  static const char* value()
  {
    return "car/door";
  }

  static const char* value(const ::car::door&) { return value(); }
};


// service_traits::MD5Sum< ::car::doorRequest> should match
// service_traits::MD5Sum< ::car::door >
template<>
struct MD5Sum< ::car::doorRequest>
{
  static const char* value()
  {
    return MD5Sum< ::car::door >::value();
  }
  static const char* value(const ::car::doorRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::car::doorRequest> should match
// service_traits::DataType< ::car::door >
template<>
struct DataType< ::car::doorRequest>
{
  static const char* value()
  {
    return DataType< ::car::door >::value();
  }
  static const char* value(const ::car::doorRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::car::doorResponse> should match
// service_traits::MD5Sum< ::car::door >
template<>
struct MD5Sum< ::car::doorResponse>
{
  static const char* value()
  {
    return MD5Sum< ::car::door >::value();
  }
  static const char* value(const ::car::doorResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::car::doorResponse> should match
// service_traits::DataType< ::car::door >
template<>
struct DataType< ::car::doorResponse>
{
  static const char* value()
  {
    return DataType< ::car::door >::value();
  }
  static const char* value(const ::car::doorResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // CAR_MESSAGE_DOOR_H
