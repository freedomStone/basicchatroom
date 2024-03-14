//Author:freedomStone
//CreateTime:March 14th,2024
//bindSocket function's definition for Linux

#include "./myserverLinux.h"

void MyServerLinux::bindSocket(int sockfd){
    int ret = bind(sockfd,(struct sockaddr*)&address,sizeof(address));
    if(ret < 0){
        throw std::runtime_error("error bind failure");
    }
}
