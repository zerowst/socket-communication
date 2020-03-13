#ifndef SOCKETBASIC_H
#define SOCKETBASIC_H
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"

#include <iostream>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include "socketbasic.h"
#define MAXBYTE 255
#define num 3

using namespace std;

//socketclient ------------------------------------------------------------------------------------------------------

class sendmessage{
private:
    int client;  //socket client
public:
    char szbuffer[MAXBYTE];  //send data in function"send"
    void init();
    void pub(double data[num]);

};

void sendmessage::pub(double data[num]){

    memset(szbuffer, 0, sizeof(szbuffer));
    memcpy(szbuffer, data, sizeof(double)*num);  //transform data type from double to char

    send(client, szbuffer, sizeof(szbuffer), MSG_NOSIGNAL);
    close(client);
}

void sendmessage::init(){

    //init of socket parameter
    client= socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");    //ip number
    sockAddr.sin_port = htons(8888);
    connect(client, (sockaddr*)& sockAddr, sizeof(sockaddr));
}


//socketserver-----------------------------------------------------------------------------------------------
class receivemessage{
private:
    int server;         //main socket
    int clntsock;       //recv socket
public:
    double recvmsg[MAXBYTE]; //receive data in the function"memcpy"
    char recvchar[MAXBYTE];  //receive data in the function"recv"
    void init();
    void receive();
};

void receivemessage::init(){
    //socketserver init-------------------------------------create a socket to connect with transport layer as the main socket------------------------
    server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//ip number
    sockAddr.sin_port = htons(8888);
    bind(server, (sockaddr*)& sockAddr, sizeof(sockaddr));
    listen(server, 20);
}

void receivemessage::receive(){
    //socketserver loop--------------------------------------create a socket to connect with client to receive message-----------------
    sockaddr clntAddr;
    unsigned int nSize = sizeof(sockaddr);
    clntsock = accept(server, (sockaddr*)& clntAddr, &nSize);

    memset(recvchar, 0, MAXBYTE);
    recv(clntsock, recvchar, MAXBYTE, MSG_NOSIGNAL);
    memcpy(recvmsg, recvchar, MAXBYTE);  //transform data type from char to double

/*    cout << recvmsg[0] <<endl;    //this part is used to verify the data received
    cout << recvmsg[1] <<endl;
    cout << recvmsg[2] <<endl;*/

    close(clntsock);
    close(server);

    //serverloop---------------------------------------------------------------
}

#endif // SOCKETBASIC_H
