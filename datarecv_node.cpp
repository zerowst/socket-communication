#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"

#include <iostream>
#include <string.h>
#include "socketbasic.h"

void chatterCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
    ROS_INFO("%f %f %f", msg->data[0], msg->data[1], msg->data[2]);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "datarecv_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("socket", 1000, chatterCallback);

    ros::spin();

    return 0;
}
