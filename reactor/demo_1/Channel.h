#pragma once

#include "Noncopyable.h"
#include <iostream>
#include <functional>

class Eventloop;

class Channel:Noncopyable {
public:
    typedef std::function<void()> EventCallback;

    //EventCallback 
    Channel(Eventloop* loop, int fd); //这个fd是什么？ 某个Channel对象负责一个fd的IO事件分发，但并不拥有这个fd 也不会在析构的时候关闭这个fd
    void handleEvent();
    void setReadCallback(const EventCallback& cb) {
        readCallback_ = cb;
    }
    void setWriteCallback(const EventCallback& cb) {
        writeCallback_ = cb;
    }
    void setErrorCallback(const EventCallback& cb) {
        errorCallback_ = cb;
    }
    int fd() const {return fd_;}
    int events() const { return events_; }
    void setrevents(int revt) { revents_ = revt;}

    
private:
        Eventloop *_loop;
        int fd_;
        int events_ = 0;
        int revents_ = 0;
        int status_ = 0;
        EventCallback readCallback_;
        EventCallback writeCallback_;
        EventCallback errorCallback_;
        


};