//Author:freedomStone
//CreateTime:March 14th,2024
//BasicChatroom Server Class for Linux

#ifndef MYSERVERLINUX_H 
#define MYSERVERLINUX_H

#include "./myserver.h"

//服务端功能类
class MyServerLinux:public MyServer{ 
public:
    //构造函数
    MyServerLinux(int port):MyServer(port){}

    //析构
    virtual ~MyServerLinux(){};

    //服务端运行实现
    void run() override{
        int sockfd = createSocket();
        bindSocket(sockfd);
        listenSocket(sockfd,USER_LIMIT);
        serverChat(sockfd);
        close(sockfd);
    };
    
protected:

    //创建socket
    int createSocket() override;
    //绑定socket
    void bindSocket(int sockfd) override;
    //监听
    void listenSocket(int sockfd,int backlog) override;

    //登录授权
    //virtual void login(){};

    //聊天后台
    void serverChat(int sockfd) override;

private:
    //将文件描述符设置为非阻塞的
    int setnonblocking(int fd)
    {
        int old_option = fcntl(fd,F_GETFL);//获取文件描述符fd的状态标志
        int new_option = old_option | O_NONBLOCK; //在既有状态基础上增加非阻塞状态
        fcntl(fd,F_SETFL,new_option);//设置新状态
        return old_option;//返回旧状态以便恢复该状态
    }

};


#endif