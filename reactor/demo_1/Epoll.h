#pragma

#include "Channel.h"
#include <vector>
#include <map>
#include <memory>
#include <assert.h>
#include <sys/epoll.h>
class Channel;
class Epoller {
public:
    Epoller();
    ~Epoller();
    int add(int fd, int event);
    int del(int fd);
    int mod(int fd, int event);
    int poll();
    void insert_Channel(std::pair<int,std::shared_ptr<Channel>> t) { Channel_list.insert(t); }
    int del_Channel(int fd) { 
        auto pos = Channel_list.find(fd);
        if(pos == Channel_list.end()) {
            std::cout<<"not find"<<std::endl;
            return -1;
        }
        else
        {
            Channel_list.erase(fd);
            del(fd);
            std::cout<<"del channel from channel list ok"<<std::endl;
            return 0;
        }
    }
private:
    int epfd_;
    std::vector<struct epoll_event> events; //事件容器
    std::map<int,std::shared_ptr<Channel>> Channel_list;
};