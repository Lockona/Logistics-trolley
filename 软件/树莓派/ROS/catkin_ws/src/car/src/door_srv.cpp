#include <ros/ros.h>
#include <car/door.h>
#include <wiringPi.h>
#include "car/duoji.h"

bool callback(car::door::Request &req,car::door::Response &res)
{
    ROS_INFO("%d\r\n",req.status);
    if(req.status == req.open)
    {
        duoji_run(125);
    }
    else
    {
        duoji_run(25);
    }
    res.result = 0;
    return true;
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"door_service");
    ros::NodeHandle node;
    ros::ServiceServer srv = node.advertiseService("door",callback);
    duoji_Init();
    ROS_INFO("door_service Init OK!!!");
    ros::spin();
    return 0;
}
