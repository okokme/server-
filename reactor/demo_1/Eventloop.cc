#include "Eventloop.h"

void Eventloop::addChannel(std::shared_ptr<Channel> chl) { 
    printf("in EventLoop::addChannel\n");
     // loop_->get_epoller()->insert_Channel( std::make_pair(fd,accept_cha) ); //是不是可以写成loop_->addChannel();
   // loop_->get_epoller()->add(accept_cha->fd,accept_cha->get_events()); //添加新channel到epollevents中
    chl->enableRead();
    epoller_->insert_Channel(std::make_pair(chl->fd(),chl));
    epoller_->add(chl->fd(), chl->get_events());
   
}
void Eventloop::delChannel(std::shared_ptr<Channel> chl) {
    printf("in EventLoop::delChannel\n");
    epoller_->del(chl->fd());
    epoller_->del_Channel(chl->fd());
}
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
                    activeChannels_.front()->handleEvent();
                    activeChannels_.pop_back();
                }
        }
    }

}