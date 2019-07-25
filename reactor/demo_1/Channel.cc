#include "Channel.h"

 
Channel::Channel(Eventloop* loop, int fd, int event):loop_(loop), fd_(fd), start_event(event) { }

void Channel::handleEvent()
{
    if(revents_ == EPOLLIN)
    {
        std::cout<<"handleEvent EPOLLIN fd = "<<fd_<<std::endl;
        readCallback_();
    }
    if(revents_ == EPOLLOUT)
    {
        std::cout<<"handleEvent EPOLLOUT fd = "<<fd_<<std::endl;
        writeCallback_();
    }
    if(revents_ == EPOLLERR)
    {
        std::cout<<"handleEvent EPOLLIN fd = "<<fd_<<std::endl;
        errorCallback_();        
    }
}
    
void Channel::handleaccept() {
    //int  accept(int  s,  struc8ik t  sockaddr  *addr, socklen_t *addrlen);
    struct sockaddr a;  
    socklen_t len = sizeof(a);      
    int fd = accept(fd_, (struct sockaddr *)&a, &len);
    std::shared_ptr<Channel> listen_cha ( new Channel(loop_, fd, EPOLLIN | EPOLLERR));
    


}
    