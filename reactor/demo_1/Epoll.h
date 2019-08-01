#pragma once

#include "Channel.h"
#include <vector>
#include <memory>
#include <iostream>
#include "Eventloop.h"
#include <sys/epoll.h>
#include <assert.h>
#include <unistd.h>
#include <map>

class Channel;
class Eventloop;

class Epoller {
public:
    Epoller():events(10){
        epfd_ = epoll_create(1);
        std::cout<<"epfd = "<<epfd_<<std::endl;
        assert( epfd_!= -1);
    }
    ~Epoller() {
        close(epfd_);
    }
    size_t INIT_SIZE = 64;
    int add(int fd, int event);
    int del(int fd);
    int mod(int fd, int event);
    int poll(int timeout, std::vector<std::shared_ptr<Channel>>& active_channel);
    void insert_Channel(std::pair<int,std::shared_ptr<Channel>> t) {std::cout<<"in insert_Channel"<<std::endl; Channel_list.insert(t); }
    int del_Channel(int fd) 
    { 
        printf("in Epoll::del_Channel\n");        
        auto pos = Channel_list.find(fd);
        if(pos == Channel_list.end()) {
            std::cout<<"not find"<<std::endl;
            return -1;
        }
        else
        {
            Channel_list.erase(pos);
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