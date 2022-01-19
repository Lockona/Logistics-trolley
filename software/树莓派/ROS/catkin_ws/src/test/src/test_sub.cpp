#include <ros/ros.h>
#include <std_msgs/String.h>
#include <test/person.h>
// void call_back(const std_msgs::String::ConstPtr &msg)
// {
//     ROS_INFO("%s\n",msg->data.c_str());
// }

// int main(int argc,char **argv)
// {
//     ros::init(argc,argv,"subliser");
//     ros::NodeHandle n;
//     ros::Subscriber sub = n.subscribe<std_msgs::String>("msg",10,call_back);
//     ros::spin();
//     return 0;
// }
void call_back(const test::person::ConstPtr &msg)
{
    ROS_INFO("name:%s,sex:%d,age:%d\n",msg->name.c_str(),msg->sex,msg->age);
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"subliser");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<test::person>("msg",10,call_back);
    ros::spin();
    return 0;
}