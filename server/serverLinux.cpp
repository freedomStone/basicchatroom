//Author:freedomStone
//CreateTime:March 14th,2024
//BasicChatroom Server for Linux

#include "./myserverLinux.h"

int main(int argc,char *argv[]){
    const int port = (argc > 1)?std::atoi(argv[1]):8081;
    
    try{
        MyServerLinux myserver(port);
        myserver.run();
    }catch(std::exception &e){
        std::cout <<"错误:"<<e.what()<<std::endl;
        return errno;
    }
    
    std::cout<<"BasicChatroom v0.1"<<std::endl;
    
    return 0;
}