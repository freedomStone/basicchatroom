//Author:freedomStone
//CreateTime:March 14th,2024
//serverChat function's definition for Linux

#include "./myserverLinux.h"

#define FD_LIMIT 65535 /*文件描述符数量限制*/

void MyServerLinux::serverChat(int sockfd){
    //创建与文件描述符最大值一致的数组，方便直接用索引获取对应的client_data对象（空间换时间）
    client_data* users = new client_data[FD_LIMIT];
    //限制用户数量
    pollfd fds[USER_LIMIT + 1];
    int user_counter = 0;
    for(int i = 1;i <= USER_LIMIT;++i){
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    fds[0].fd = sockfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;

    int ret;

    while (true)
    {
        ret = poll(fds,user_counter+1,-1);
        if(ret < 0){
            throw std::runtime_error("poll failure");
            break;
        }

        for(int i = 0;i < user_counter + 1; ++i){
            if((fds[i].fd == sockfd)&&(fds[i].revents & POLLIN))
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept(sockfd,(struct sockaddr*)&client_address,&client_addrlength);
                if(connfd < 0){
                    throw std::runtime_error("errno is " + std::to_string(errno));
                    continue;
                }
                //请求太多关闭连接
                if(user_counter >= USER_LIMIT)
                {
                    const char* info = "too many users\n";
                    std::cout<<info;
                    send(connfd,info,strlen(info),0);
                    close(connfd);
                    continue;
                }

                //对于新连接，同时修改fds和users数组
                user_counter++;
                users[connfd].address = client_address;
                setnonblocking(connfd);
                fds[user_counter].fd = connfd;
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                fds[user_counter].revents = 0;
                std::cout<<"comes a new user,now have "<<user_counter<<" users."<<std::endl; 
            }else if(fds[i].revents & POLLERR)
            {
                std::cout << "get an error from "<<fds[i].fd<<std::endl;
                char errors[100];
                memset(errors,'\0',100);
                socklen_t length = sizeof(errors);
                if(getsockopt(fds[i].fd,SOL_SOCKET,SO_ERROR,&errors,&length)<0)
                {
                    throw std::runtime_error("get socket option failed");
                }
                continue;
            }else if(fds[i].revents & POLLRDHUP)
            {
                //客户关闭连接
                int connfd = fds[i].fd;
                users[fds[i].fd] = users[fds[user_counter].fd];
                close(fds[i].fd);
                fds[i] = fds[user_counter];
                i--;
                user_counter--;
                std::cout<<"a client left\n";
            }else if (fds[i].revents & POLLIN)
            {
                int connfd = fds[i].fd;
                memset(users[connfd].buf,'\0',BUFFER_SIZE);
                ret = recv(connfd,users[connfd].buf,BUFFER_SIZE-1,0);
                std::cout<<"(from ["<<connfd<<"] get "<<ret<<" bytes of clients data): "<<users[connfd].buf<<std::endl;
                if(ret < 0){
                    if(errno != EAGAIN)
                    {
                        close(connfd);
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                }else if(ret == 0){

                }else{
                    for(int j = 1;j<=user_counter;++j)
                    {
                        if(fds[j].fd == connfd){
                            continue;
                        }
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[connfd].buf;
                        //add 字符串拼接
                        //std::string tempss = std::to_string(connfd) + " says:";
                        //strcat(users[fds[j].fd].write_buf,tempss.c_str());
                    }
                }
            }else if(fds[i].revents & POLLOUT)
            {
                int connfd = fds[i].fd;
                if(!users[connfd].write_buf){
                    continue;
                }
                ret = send(connfd,users[connfd].write_buf,strlen(users[connfd].write_buf),0);
                users[connfd].write_buf = NULL;
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
            
        }
    }
    delete [] users;
}
 