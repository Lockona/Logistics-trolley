#include <ros/ros.h>
#include <car/move.h>
#include <car/serial_port.hpp>
#include <iostream>
#include <string>

serial_port *serial;
void callback(const car::move::ConstPtr &msg)
{
    char buf[16];
    // ROS_INFO("speed:%d,angle:%d\n", msg->speed,msg->angle);
    std::stringstream s;
    sprintf(buf,"M%d\r\n",msg->speed);
    std::cout<<buf<<std::endl;
    serial->send(buf,strlen(buf));
}

int main(int argc, char** argv) {
    ros::init(argc,argv,"move_subscriber");
    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe<car::move>("move",10,callback);
    serial = new serial_port("/dev/ttyUSB0",115200);
    ROS_INFO("move_subscriber Init OK!!!");
    ros::spin();
    return 0;
}