//Author:freedomStone
//CreateTime:March 14th,2024
//BasicChatroom Client for Linux

#include <iostream>
#include "myclient.h"

using namespace std;

int main(){
    MyClientLinux myclient("127.0.0.1",8080);
    myclient.run();
    cout<<"hello linux"<<endl;
    return 0;
}
