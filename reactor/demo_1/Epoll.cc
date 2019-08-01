#include "Epoll.h"
#include "Channel.h"

int Epoller::add(int fd, int event) {
    printf("in Epoll::add\n");
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_ADD,fd,&ev) != -1);
    if (Channel_list.size() >= INIT_SIZE) {
        INIT_SIZE *= 2;
        events.resize(INIT_SIZE);
    }
}

int Epoller::mod(int fd, int event) {
    printf("in Epoll::mod\n");
    
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_MOD,fd,&ev) != -1);
}

int Epoller::del(int fd) {
    printf("in Epoll::del\n");
    
    assert(epoll_ctl(epfd_,EPOLL_CTL_DEL,fd,0) != -1);
}
 
int Epoller::poll(int timeout,std::vector<std::shared_ptr<Channel>>& active_channel)
{
   // printf("in Epoll::poll\n");
    
    int nevents = epoll_wait(epfd_, &events[0], events.size(), timeout);
   // std::cout<<"nevents = "<<nevents<<std::endl;
     
    if(nevents > 0)   
    {
        for(int i=0; i<nevents; i++)
        {
            auto it = Channel_list.find(events[i].data.fd);
            assert(it!=Channel_list.end());
            it->second->set_revents(events[i].events);//将内核事件表中的此事件 传递给参数Channel类中的revent 后面内核有什么事件返回直接读revent
            active_channel.push_back(it->second);
        }

    }
    else if(nevents <0 )
    {
        if(errno == EINTR) //慢系统调用，信号中断 
        {
            printf("EINTR\n");
             return 0;
        } 
        // if(events. & EPOLLERR || events & EPOLLHUP || (! events & EPOLLIN))
        // {
        //     printf("events & EPOLLERR || events & EPOLLHUP || (! events & EPOLLIN)\n");
        //     return 0;
        // }
        else {
            std::cout<<"epoll_err"<<std::endl;
            exit(0);
            return -1;  
            //写入日志
        }   
    }
    return nevents;
}