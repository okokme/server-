#pragma once

#include "Noncopyable.h"
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include <iostream>
#include <functional>

class Eventloop;

class Channel:Noncopyable {
public:
    typedef std::function<void()> EventCallback;
//  typedef std::function<void(const Channel&conn buffer *buf)> cliCallback;
    
    Channel(Eventloop* loop, int fd, int event); //这个fd是什么？ 是我服务器的socket 某个Channel对象负责一个fd的IO事件分发，但并不拥有这个fd 也不会在析构的时候关闭这个fd
   
    void handleEvent();
   
    void setReadCallback(const EventCallback& cb) { readCallback_ = cb; }
    void setWriteCallback(const EventCallback& cb) { writeCallback_ = cb; }
    void setErrorCallback(const EventCallback& cb) { errorCallback_ = cb; }
    EventCallback getReadCallback() { return readCallback_; }
    EventCallback getWriteCallback() { return writeCallback_; }
    EventCallback getErrorCallback() { return errorCallback_;  }
    
    void handleaccept();

    int sendmssage(const char* s, size_t len);
    int recvmessage();

    int fd() const { return fd_; }

    void set_revents(int revt) { revents_ = revt; }
    int get_events() const { return revents_; }
    int get_start_event() { return start_event; }
    int set_nonblock() { 
       int old_option = fcntl(fd, F_GETFL);
       int new_option = old_option | O_NONBLOCK;
       fcntl(fd, F_SETFL, new_option);
       return old_option;
    }

  //  int isReading() { return }
private:
        Eventloop *loop_;
        int fd_;
       // int events_ = 0;
        int revents_ = 0;
        int start_event =0;
        int status_ = 0;

        EventCallback readCallback_;
        EventCallback writeCallback_;
        EventCallback errorCallback_;
};