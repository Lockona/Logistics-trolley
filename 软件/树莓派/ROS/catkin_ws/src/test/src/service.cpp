#include <ros/ros.h>
#include <test/test.h>
#include "test/duoji.h"

bool call_back(test::test::Request &req,test::test::Response &res)
{
    ROS_INFO("%d\n",req.status);
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

int main(int argc,char **argv)
{
    ros::init(argc,argv,"service");
    ros::NodeHandle n;
    ros::ServiceServer test_srv = n.advertiseService("control",call_back);
    int ret = duoji_Init();
    if(ret<0)
    {
        return -1;
    }
    ROS_INFO("OK");
    ros::spin();
    return 0;
}