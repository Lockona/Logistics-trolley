#include "car/serial_port.hpp"
#include <car/miiboo.h>
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
  ros::NodeHandle miiboo_node;
  ros::Publisher miiboo_pub = miiboo_node.advertise<car::miiboo>("miiboo", 10);
  serial_port *serial = new serial_port("/dev/miiboo", 115200);
  ROS_INFO("miiboo_publiser Init OK!!!");
  // ros::Rate rate(10);
  char checksum = 0, recv_flag = 0;
  car::miiboo msg;
  msg.frame_id = 0;
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
          msg.angle.roll = (uart_msg.data[0] > 0 ? 1 : -1) *
                           (float)(uart_msg.data[1] * 100 + uart_msg.data[2]) /
                           100;
          msg.angle.pitch = (uart_msg.data[3] > 0 ? 1 : -1) *
                            (float)(uart_msg.data[4] * 100 + uart_msg.data[5]) /
                            100;
          msg.angle.yaw = (uart_msg.data[6] > 0 ? 1 : -1) *
                          (float)(uart_msg.data[7] * 100 + uart_msg.data[8]) /
                          100;
          recv_flag |= 0x01;
        } else if (uart_msg.type == 'W') {
          msg.left_wheel_speed =
              (((int)uart_msg.data[0] << 8) | uart_msg.data[1]);
          msg.right_wheel_speed =
              (((int)uart_msg.data[2] << 8) | uart_msg.data[3]);
          recv_flag |= 0x10;
        }
      }
      if (recv_flag == 0x11) {
        msg.frame_id++;
        miiboo_pub.publish(msg);
        recv_flag = 0;
      }
      free(uart_msg.data);
    }
  }
  return 0;
}