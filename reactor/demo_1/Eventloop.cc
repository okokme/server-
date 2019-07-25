#include "Eventloop.h"

void Eventloop::Loop()
{
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