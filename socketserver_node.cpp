#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Byte.h"
#include "std_msgs/ByteMultiArray.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"

#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "socketbasic.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "socketserver_node");
    ros::NodeHandle nh;

    ros::Publisher chatter_pub = nh.advertise<std_msgs::Float64MultiArray>("socket", 1000);

    ros::Rate loop_rate(1);

    while (ros::ok())
    {
        std_msgs::Float64MultiArray msg;

        //socketserver
        receivemessage receivemsg;
        receivemsg.init();
        receivemsg.receive();

        //put the data received into the msg of topic
        msg.data.resize(num);
        msg.data[0] = receivemsg.recvmsg[0];
        msg.data[1] = receivemsg.recvmsg[1];
        msg.data[2] = receivemsg.recvmsg[2];


        chatter_pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}
