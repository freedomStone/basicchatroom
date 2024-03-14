//Author:freedomStone
//CreateTime:March 14th,2024
//BasicChatroom Client for Linux

#include "myclientLinux.h"

int main(int argc,char *argv[]){
    //设定服务器地址
    const std::string ipstr = (argc > 1)?argv[1]:"127.0.0.1";
    const int port = (argc > 2)?std::atoi(argv[2]):8081;

    try{
        MyClientLinux myclient(ipstr,port);
        myclient.run();
    }catch(std::exception &e){
        std::cout <<"错误:"<<e.what()<<std::endl;
        return errno;
    }
    
    std::cout<<"BasicChatroom v0.1"<<std::endl;
    return 0;
}
