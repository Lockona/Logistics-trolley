#include <ros/ros.h>
#include <std_msgs/String.h>
#include <test/person.h>
// int main(int argc, char **argv)
// {
//     ros::init(argc, argv, "publisher");
//     ROS_INFO("ok");
//     ros:: NodeHandle n;
//     ros::Publisher pub = n.advertise<std_msgs::String>("msg",10);
//     ros::Rate rate(10);
//     while (ros::ok)
//     {
//         std_msgs::String msg;
//         msg.data = "Hello ROS!!!";
//         pub.publish(msg);
//         rate.sleep();
//     }
//     return 0;
// }
int main(int argc, char **argv)
{
    ros::init(argc, argv, "publisher");
    ROS_INFO("ok");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<test::person>("msg",10);
    ros::Rate rate(10);
    while (ros::ok)
    {
        test::person msg;
        msg.name = "Ros";
        msg.sex = msg.male;
        msg.age = 100;
        pub.publish(msg);
        rate.sleep();
    }
    return 0;
}