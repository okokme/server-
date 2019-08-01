#pragma once

#include "Noncopyable.h"
#include "Channel.h"
#include "Epoll.h"
#include <thread>
#include <vector>
#include <map>

class Epoller;
class Channel;
class Eventloop : Noncopyable {
public:
    Eventloop(Epoller *poller):epoller_(poller),quit_(false) {printf("in EventLoop::构造函数\n"); }
    ~Eventloop() { }
    void Loop();
//    void changeevent(int fd, int events) { epoller_->mod(fd, events);}
    void addChannel(std::shared_ptr<Channel> chl); ///向loop中添加一个新的Channel
    void delChannel(std::shared_ptr<Channel> chl);
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
