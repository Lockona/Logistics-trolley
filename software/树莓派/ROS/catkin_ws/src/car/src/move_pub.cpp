#include <ros/ros.h>
#include <car/move.h>
#include <car/serial_port.hpp>

int main(int argc, char** argv) {
    ros::init(argc,argv,"move_publiser");
    ros::NodeHandle node;
    ros::Publisher pub = node.advertise<car::move>("move",10);
    serial_port *serial = new serial_port("/dev/miiboo",115200);
    ROS_INFO("move_publiser Init OK!!!");
    // ros::Rate rate(10);
    char buf[32];
    int speed = 0;
    while (ros::ok)
    {
        scanf("%d",&speed);
        car::move msg;
        msg.angle = 0;
        msg.speed = speed;
        serial->recv(buf,32);
        pub.publish(msg);
        // rate.sleep();
    }    
    return 0;
}