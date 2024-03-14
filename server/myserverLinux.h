//Author:freedomStone
//CreateTime:March 14th,2024
//BasicChatroom Server Class for Linux

#ifndef MYSERVERLINUX_H 
#define MYSERVERLINUX_H

#include "./myserver.h"

//客户端功能基类
class MyServerLinux:public MyServer{ 
public:
    //构造函数
    MyServerLinux(){}

    //析构
    virtual ~MyServerLinux(){};

    //客户端运行实现
    void run(){};
    
protected:

    //创建socket
    int createSocket(){};
    //绑定socket
    void bindSocket(int sockfd,int port){};
    //监听
    void listenSocket(int sockfd,int backlog){};
    //接受
    int acceptRequest(int sockfd){};

    //登录
    //virtual void login(){};

    //聊天后台
    int serverChat(int sockfd){};

};


#endif