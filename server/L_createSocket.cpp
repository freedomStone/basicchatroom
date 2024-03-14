//Author:freedomStone
//CreateTime:March 14th,2024
//createSocket function's definition for Linux

#include "./myserverLinux.h"

int MyServerLinux::createSocket(){
    int ret = socket(PF_INET,SOCK_STREAM,0);
    if(ret < 0){
        throw std::runtime_error("create socket failed");
    }
    return ret;
}