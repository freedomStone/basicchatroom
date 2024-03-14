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

#define BUFFER_SIZE 64 /*读缓冲区大小*/
#define USER_LIMIT 5 /*最大用户数量*/

//客户数据结构
struct client_data{
    sockaddr_in address;
    char* write_buf;
    char buf[BUFFER_SIZE];
};


//服务端功能基类
class MyServer{ 
public:
    //构造函数
    MyServer(int port){
        memset(&address,0,sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        std::string ipstr = "127.0.0.1";
        inet_pton(AF_INET,ipstr.c_str(),&(address.sin_addr));
    }

    //析构
    virtual ~MyServer(){};

    //服务端运行实现
    virtual void run()=0;
    
protected:
    struct sockaddr_in address;

    //创建socket
    virtual int createSocket()=0;
    //绑定socket
    virtual void bindSocket(int sockfd)=0;
    //监听
    virtual void listenSocket(int sockfd,int backlog)=0;

    //登录
    //virtual void login()=0;

    //聊天后台
    virtual void serverChat(int sockfd)=0;

};


#endif