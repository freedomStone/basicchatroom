//Author:freedomStone
//CreateTime:March 14th,2024
//listenSocket function's definition for Linux

#include "./myserverLinux.h"

void MyServerLinux::listenSocket(int sockfd,int backlog = 5){
    int ret = listen(sockfd,backlog);
    if(ret < 0){
        throw std::runtime_error("listen failed");
    }
}