//Author:freedomStone
//CreateTime:March 14th,2024
//createSocket function's definition for Linux

#include "./myclientLinux.h"

int MyClientLinux::connectSocket() {
    //创建套接字
    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        throw std::runtime_error("Error creating socket");
    }
    //连接
    int res = connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address));
    if( res < 0)
    {
        throw std::runtime_error("Error in making connection");
        return -1;
    }else{
        return sockfd;
    }
}