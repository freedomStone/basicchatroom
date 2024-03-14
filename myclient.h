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
    #include <assert.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <poll.h>
    #include <fcntl.h>
#else
    std::cout<<"Unknown Platform!"<<std::endl;
#endif


//客户端功能基类
class MyClient{ 
public:
    //构造函数
    MyClient(const char* ipstr,int port){
        memset(&server_address,0,sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        inet_pton(AF_INET,ipstr,&server_address.sin_addr);
    }

    //实现消息发送给服务器
    //virtual int sentMessage(const char* message)=0;
    //实现接受消息并展示出来
    //virtual char* recvMessage()=0;
    //析构
    virtual ~MyClient(){};
    //绑定创建socket
    virtual int createSocket()=0;

    //客户端运行实现
    virtual void run()=0;
    
protected:
    struct sockaddr_in server_address;
};

//Linux实现
class MyClientLinux:public MyClient{
public:
    MyClientLinux(const char* ipstr,int port):MyClient(ipstr,port){}
    virtual ~MyClientLinux(){};
    
    int createSocket() override{
        int sockfd = socket(PF_INET,SOCK_STREAM,0);
        if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address)) < 0)
        {
            std::cout<<"connection failed\n";
            close(sockfd);
            return -1;
        }else{
            return sockfd;
        }
    }

    //创建 pollfd
    void event_init(pollfd *fds,int sockfd){
        fds[0].fd = 0;
        fds[0].events = POLLIN;
        fds[0].revents = 0;
        fds[1].fd = sockfd;
        fds[1].events = POLLIN | POLLRDHUP;
        fds[1].revents = 0;
    }

    void run() override{
        int sockfd = createSocket();
        pollfd fds[2];
        event_init(fds,sockfd);
        int pipefd[2];
        bool whilestatus = pipe(pipefd) && (sockfd >= 0);
        const int BUFFER_SIZE = 64;
        char read_buf[BUFFER_SIZE];
        int ret;
        while (whilestatus)
        {
            ret = poll(fds,2,-1);
            if(ret < 0){
                std::cout<<"poll failure\n";
                break;
            }
            if(fds[1].revents & POLLRDHUP){
                std::cout<<"server close the connection\n";
                break;
            }else if(fds[1].revents & POLLIN){
                memset(read_buf,'\0',BUFFER_SIZE);
                recv(fds[1].fd,read_buf,BUFFER_SIZE-1,0);
                std::cout<<read_buf<<std::endl;
            }

            if(fds[0].revents & POLLIN){
                ret = splice(0,NULL,pipefd[1],NULL,32768,SPLICE_F_MORE|SPLICE_F_MOVE);
                ret = splice(pipefd[0],NULL,sockfd,NULL,32768,SPLICE_F_MORE|SPLICE_F_MOVE);
            }
        }
        close(sockfd); 
    }

    
};


#endif