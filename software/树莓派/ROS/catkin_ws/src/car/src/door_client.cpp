#include <ros/ros.h>
#include <car/door.h>
#include <car/serial_port.hpp>

int flag = 1;

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"door_client");
    ros::service::waitForService("door");
    ros::NodeHandle node;
    ros::ServiceClient client = node.serviceClient<car::door>("door");
    serial_port *serial = new serial_port("/dev/qx1100",115200);
    car::door srv;
    char buf[32];
    ROS_INFO("door_client Init OK");
    while (ros::ok)
    {
        serial->recv(buf,32);
        if(flag)
            srv.request.status = car::door::Request::open;
        else
            srv.request.status = car::door::Request::close;
        client.call(srv);
        flag = 1 - flag;
    }
    
    return 0;
}
