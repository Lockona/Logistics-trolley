#include <car/miiboo.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <string>

nav_msgs::Odometry odom;
geometry_msgs::Twist send_msg;
ros::Publisher odom_pub;
float x = 0, y = 0, z = 0;
void callback(const car::miiboo::ConstPtr &msg) {
  send_msg.linear.x = 3.14 * 6.5 *
                      (float)(msg->left_wheel_speed + msg->right_wheel_speed) /
                      5.0 / 780.0;
  // send_msg.angular.x = (float)(msg->angle.roll - x) / 0.1;
  // send_msg.angular.y = (float)(msg->angle.pitch - y) / 0.1;
  send_msg.angular.z = (float)(msg->angle.yaw - z) / 0.1 * (3.14159 / 180);
  // x = msg->angle.roll;
  // y = msg->angle.pitch;
  z = msg->angle.yaw;
  odom_pub.publish(send_msg);
  ROS_INFO("frame_id:%d,speed:%.2f,yaw:%.2f", msg->frame_id, send_msg.linear.x,
           send_msg.angular.z);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "odom_publisher");
  ros::NodeHandle miiboo_node, odom_node;
  odom_pub = odom_node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  ros::Subscriber miiboo_sub =
      miiboo_node.subscribe<car::miiboo>("miiboo", 10, callback);
  ROS_INFO("odom_publisher Init OK!!!");
  ros::spin();
  return 0;
}