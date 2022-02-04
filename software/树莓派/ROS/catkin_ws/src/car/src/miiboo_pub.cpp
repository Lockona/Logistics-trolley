#include "car/serial_port.hpp"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <stdio.h>
struct messages {
  char top;
  char type;
  char length;
  unsigned char *data;
  char checksum;
};
struct messages uart_msg;
int main(int argc, char **argv) {
  ros::init(argc, argv, "miiboo_publisher");
  ros::NodeHandle wheel_node;
  ros::NodeHandle imu_node;
  ros::Publisher imu_pub = imu_node.advertise<geometry_msgs::Twist>("imu", 10);
  ros::Publisher wheel_pub =
      wheel_node.advertise<geometry_msgs::Twist>("wheel", 10);
  serial_port *serial = new serial_port("/dev/miiboo", 115200);
  ROS_INFO("miiboo_publiser Init OK!!!");
  // ros::Rate rate(10);
  char buf[32];
  char checksum = 0;
  float x, y, z;
  geometry_msgs::Twist imu_msg;
  geometry_msgs::Twist wheel_msg;
  while (ros::ok) {
    serial->recv((char *)&uart_msg, 3);
    if (uart_msg.top == 0xff) {
      uart_msg.data = (unsigned char *)malloc(uart_msg.length);
      serial->recv((char *)uart_msg.data, uart_msg.length);
      serial->recv((char *)&uart_msg.checksum, 1);
      checksum = uart_msg.top + uart_msg.type + uart_msg.length;
      for (int i = 0; i < uart_msg.length; i++) {
        checksum += uart_msg.data[i];
      }
      if (checksum == uart_msg.checksum) {
        if (uart_msg.type == 'A') {
          x = (float)(uart_msg.data[1] * 100 + uart_msg.data[2]) / 100;
          x *= uart_msg.data[0] > 0 ? 1 : -1;
          y = (float)(uart_msg.data[4] * 100 + uart_msg.data[5]) / 100;
          y *= uart_msg.data[3] > 0 ? 1 : -1;
          z = (float)(uart_msg.data[7] * 100 + uart_msg.data[8]) / 100;
          z *= uart_msg.data[6] > 0 ? 1 : -1;
          imu_msg.angular.x = x;
          imu_msg.angular.y = y;
          imu_msg.angular.z = z;
          imu_pub.publish(imu_msg);
        } else if (uart_msg.type == 'W') {
          wheel_msg.linear.x = (int)uart_msg.data[0];
          wheel_msg.linear.y = (int)uart_msg.data[1];
          ROS_INFO("length:%d,%d,%d", uart_msg.length, uart_msg.data[0],
                   uart_msg.data[1]);
          wheel_pub.publish(wheel_msg);
        }
      }
      free(uart_msg.data);
    }
  }
  return 0;
}