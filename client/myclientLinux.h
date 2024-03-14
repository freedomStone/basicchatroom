//Author:freedomStone
//CreateTime:March 14th,2024
//BasicChatroom Client Class

#ifndef MYCLIENTLINUX_H 
#define MYCLIENTLINUX_H

#include "./myclient.h"

const int BUFFER_SIZE = 64;

//Linux实现
class MyClientLinux:public MyClient{
public:
    MyClientLinux(const std::string &ipstr,int port):MyClient(ipstr,port){}
    virtual ~MyClientLinux(){};

    void run() override{
        int sockfd = connectSocket();
        clientChat(sockfd);
    }

protected:
    int connectSocket() override{}
    int clientChat(int sockfd) override{}; 
};


#endif