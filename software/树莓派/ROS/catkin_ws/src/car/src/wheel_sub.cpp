#include <geometry_msgs/Twist.h>
#include <iostream>
#include <ros/ros.h>
#include <string>

void callback(const geometry_msgs::Twist::ConstPtr &msg) {
  ROS_INFO("left_wheel:%d,right_wheel:%d", (int)msg->linear.x,
           (int)msg->linear.y);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "wheel_subscriber");
  ros::NodeHandle wheel_node;
  ros::Subscriber wheel_sub =
      wheel_node.subscribe<geometry_msgs::Twist>("wheel", 10, callback);
  ROS_INFO("wheel_subscriber Init OK!!!");
  ros::spin();
  return 0;
}