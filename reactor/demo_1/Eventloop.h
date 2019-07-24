#pragma once

#include "Noncopyable.h"
#include "Channel.h"
#include "Epoll.h"
#include <thread>
#include <vector>
#include <map>
class Eventloop : Noncopyable {
public:
    Eventloop(Epoller *poller):epoller_(poller),quit_(false) { }
    ~Eventloop();
    void Loop();
    Epoller* get_epoller() { return epoller_;}
    
//  typedef std::vector<Channel*> ChannelList;
private:
    typedef std::shared_ptr<Channel> sChannel_;
    Epoller *epoller_;
    std::vector<sChannel_> activeChannels_;
//  std::map<int, Channel*> channelMap_;
    std::map<int, sChannel_> ChannelMap_;
    bool quit_; /*atomic*/

};
