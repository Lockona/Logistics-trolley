#include <ros/ros.h>
#include <test/test.h>
#include "test/serial_port.hpp"

int flag = 1;

int main(int argc, char** argv) {
    ros::init(argc,argv,"client");
    ros::NodeHandle node;
    ros::service::waitForService("control");
    ros::ServiceClient test_clt = node.serviceClient<test::test>("control");
    test::test srv;
    serial_port *serial = new serial_port("/dev/ttyUSB0",115200);
    char buf[64];
    while (ros::ok)
    {
        serial->recv(buf,64);
        if(flag)
            srv.request.status = srv.request.open;
        else
            srv.request.status = srv.request.close;
        test_clt.call(srv);
        flag = 1 - flag;
    }
    ROS_INFO("%d\n",srv.response.result);
    return 0;
}