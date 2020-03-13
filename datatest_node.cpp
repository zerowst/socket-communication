#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"

#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>

#define num 3

int main(int argc, char **argv)
{
    ros::init(argc, argv, "datatest_node");
    ros::NodeHandle nh;

    ros::Publisher chatter_pub = nh.advertise<std_msgs::Float64MultiArray>("datatest", 1000);

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        static double x = 0, y = 0, z = 0;
        std_msgs::Float64MultiArray msg;
        msg.data.resize(num);
        msg.data[0] = x;
        msg.data[1] = y;
        msg.data[2] = z;
        x++;
        y+=2;
        z+=3;
        chatter_pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
