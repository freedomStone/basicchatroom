//Author:freedomStone
//CreateTime:March 11th,2024
//BasicChatroom Client Class

#ifndef MYCLIENT_H 
#define MYCLIENT_H

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
class MyClient{ 
public:
    //构造函数
    MyClient(const std::string &ipstr,int port){
        memset(&server_address,0,sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        inet_pton(AF_INET,ipstr.c_str(),&(server_address.sin_addr));
    }

    //析构
    virtual ~MyClient(){};

    //客户端运行实现
    virtual void run()=0;
    
protected:
    struct sockaddr_in server_address;

    //绑定创建socket
    virtual int connectSocket()=0;
    //登录
    //virtual void login()=0;

    //聊天
    virtual void clientChat(int sockfd)=0;

};


#endif