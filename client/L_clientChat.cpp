//Author:freedomStone
//CreateTime:March 14th,2024
//clientChat function's definition for Linux

#include "./myclientLinux.h"

int MyClientLinux::clientChat(int sockfd){
    char read_buf[BUFFER_SIZE] = {'\0'};

    pollfd fds[2];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;

    int pipefd[2];
    bool whilestatus = pipe(pipefd) && (sockfd >= 0);
    
    int ret;
    
    while (whilestatus)
    {
        ret = poll(fds,2,-1);
        if(ret < 0){
            throw std::runtime_error("poll failure");
            break;
        }

        if(fds[1].revents & POLLRDHUP){
            throw std::runtime_error("server close the connection");
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

    return 0;
}