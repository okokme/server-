#include "Eventloop.h"

void Eventloop::Loop()
{
    while(!quit_)
    {
        //初始化epoller_
        int nevents = epoller_->  ;//--------------------这里没写完
        if(nevents == 0) {
            //等待 超时 踢
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