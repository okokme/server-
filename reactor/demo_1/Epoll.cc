#include "Epoll.h"
#include "Channel.h"

int Epoller::add(int fd, int event) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_ADD,fd,&ev) != -1);
}

int Epoller::mod(int fd, int event) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_MOD,fd,&ev) != -1);
}

int Epoller::del(int fd) {
    assert(epoll_ctl(epfd_,EPOLL_CTL_DEL,fd,0) != -1);
}
 
int Epoller::poll(int timeout,std::vector<std::shared_ptr<Channel>>& active_channel)
{
    int nevents = epoll_wait(epfd_,&events[0],events.size(),timeout);
    std::cout<<"nevents = "<<nevents<<std::endl;
    if(nevents > 0)   
    {
        for(int i=0; i<nevents; i++)
        {
            auto it = Channel_list.find(events[i].data.fd);
            assert(it!=Channel_list.end());
            it->second->set_revents(events[i].events);//第一次设置事件-------------------------set_event未实现啊
            active_channel.push_back(it->second);
        }

    }
    else if(nevents <0 )
    {
        if(errno == EINTR) //慢系统调用，信号中断 
            return 0;
        else {
            std::cout<<"epoll_err"<<std::endl;
            return -1;
            //写入日志
        }   
    }
    return nevents;
}