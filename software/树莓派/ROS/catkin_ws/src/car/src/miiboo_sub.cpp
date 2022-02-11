#include <car/miiboo.h>
#include <car/odom.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <ros/ros.h>
#include <string>
#include <tf/tf.h>
car::odom myodomdata;
nav_msgs::Odometry odom;
geometry_msgs::Twist send_msg;
geometry_msgs::TransformStamped odom_trans;
geometry_msgs::Quaternion odom_quat;
ros::Publisher odom_pub;

float delta_d, delta_theta, delta_x, delta_y;
void callback(const car::miiboo::ConstPtr &msg) {
  if (msg->frame_id) {
    delta_d = 3.14 * 6.5 *
              (float)(msg->left_wheel_speed + msg->right_wheel_speed) / 2 /
              780 / 10;
    delta_theta = (msg->angle.yaw - delta_theta) * (3.14159 / 180);
    delta_x = delta_d * cos(myodomdata.oriention + delta_theta * 0.5);
    delta_y = delta_d * sin(myodomdata.oriention + delta_theta * 0.5);

    myodomdata.position_x += delta_x;
    myodomdata.position_y += delta_y;
    myodomdata.oriention += delta_theta;
    myodomdata.velocity_linear = delta_d * 10;
    myodomdata.velocity_angular = delta_theta * 10;

    send_msg.linear.x = myodomdata.velocity_linear;
    // send_msg.angular.x = (float)(msg->angle.roll - x) / 0.1;
    // send_msg.angular.y = (float)(msg->angle.pitch - y) / 0.1;
    send_msg.angular.z = myodomdata.velocity_angular;
    // odom_quat = tf::createQuaternionMsgFromYaw(myodomdata.oriention);
    // odom_trans.header.stamp = ros::Time::now();
    // odom_trans.header.frame_id = "odom";
    // odom_trans.child_frame_id = "miiboo";
    // odom_trans.transform.translation.x = myodomdata.position_x;
    // odom_trans.transform.translation.y = myodomdata.position_y;
    // odom_trans.transform.translation.z = 0.0;
    // odom_trans.transform.rotation = odom_quat;

    // odom.header.stamp = ros::Time::now();
    // odom.header.frame_id = "odom";
    // odom.child_frame_id = "miiboo";
    // odom.pose.pose.position.x = myodomdata.position_x;
    // odom.pose.pose.position.y = myodomdata.position_y;
    // odom.pose.pose.position.z = 0.0;
    // odom.pose.pose.orientation = odom_quat;
    // odom.twist.twist.linear.x = myodomdata.velocity_linear;
    // odom.twist.twist.angular.z = myodomdata.velocity_angular;
    delta_theta = msg->angle.yaw;
    odom_pub.publish(send_msg);
    ROS_INFO("frame_id:%d,speed:%.2f,yaw:%.2f", msg->frame_id,
             send_msg.linear.x, send_msg.angular.z);
  } else {
    delta_theta = msg->angle.yaw;
    myodomdata.oriention = delta_theta * (3.14159 / 180);
  }
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