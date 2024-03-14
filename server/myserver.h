//Author:freedomStone
//CreateTime:March 14th,2024
//BasicChatroom Server Class

#ifndef MYSERVER_H 
#define MYSERVER_H

//公共库
#include <iostream>
#include <string.h>

//区分系统预调用不同库
#ifdef _WIN32
    std::cout<<"Windows Platform!"<<std::endl;
#elif __linux__
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <poll.h>
    #include <fcntl.h>
    #include <errno.h>
#else
    std::cout<<"Unknown Platform!"<<std::endl;
#endif


//客户端功能基类
class MyServer{ 
public:
    //构造函数
    MyServer(){}

    //析构
    virtual ~MyServer(){};

    //客户端运行实现
    virtual void run()=0;
    
protected:
    struct sockaddr_in address;

    //创建socket
    virtual int createSocket()=0;
    //绑定socket
    virtual void bindSocket(int sockfd,int port)=0;
    //监听
    virtual void listenSocket(int sockfd,int backlog)=0;
    //接受
    virtual int acceptRequest(int sockfd)=0;

    //登录
    //virtual void login()=0;

    //聊天后台
    virtual int serverChat(int sockfd)=0;

};


#endif