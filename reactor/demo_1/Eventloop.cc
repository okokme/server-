#include "Eventloop.h"

void Eventloop::addChannel(std::shared_ptr<Channel> chl) { 
    printf("in EventLoop::addChannel\n");
    chl->enableRead();
    std::cout<<"--------------------------------chl->fd()="<<chl->fd()<<std::endl;
    epoller_->insert_Channel(std::make_pair(chl->fd(),chl));
    epoller_->add(chl->fd(), chl->get_events());
   
}
void Eventloop::delChannel(std::shared_ptr<Channel> chl) {
    printf("in EventLoop::delChannelf", chl->fd());
    epoller_->del_Channel(chl->fd());
}
 void Eventloop::changeevent(int fd, int events) { epoller_->mod(fd, events);}

void Eventloop::Loop() {
    printf("in EventLoop::Loop\n");
    while(!quit_)
    {
        //初始化epoller_
        //这里的epoll->poll的第一个参数是timeout 可以后面做时间轮时踢
        int nevents = epoller_->poll(-1,activeChannels_);//--------------------这里没写完
        if(nevents == 0) {
            //等待 超时 踢
        std::cout<<"nevents == 0 为超时踢做准备"<<std::endl;     
        }
        else if(nevents > 0) {
                while(!activeChannels_.empty())
                {
                    activeChannels_.back()->handleEvent();
                    activeChannels_.pop_back();
                }
        }
    }

}