#include <geometry_msgs/Twist.h>
#include <iostream>
#include <ros/ros.h>
#include <string>

void callback(const geometry_msgs::Twist::ConstPtr &msg) {
  ROS_INFO("x:%.2f,y:%.2f,z:%.2f", msg->angular.x, msg->angular.y,
           msg->angular.z);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "imu_subscriber");
  ros::NodeHandle imu_node;
  ros::Subscriber imu_sub =
      imu_node.subscribe<geometry_msgs::Twist>("imu", 10, callback);
  ROS_INFO("imu_subscriber Init OK!!!");
  ros::spin();
  return 0;
}