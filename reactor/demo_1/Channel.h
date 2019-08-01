#pragma once

//#include <buffer.h>
#include "Noncopyable.h"
#include "Eventloop.h"
#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory>
#include <string>
#include <iostream>
#include <functional>

class Eventloop;
class Epoller;

class Channel:Noncopyable {
public:
    typedef std::function<void()> EventCallback;
 //   typedef std::function<void(std::shared_ptr<Channel>, Buffer&)> MessageCallback;
    
    Channel(Eventloop* loop, int fd, int event); //这个fd是什么？ 是我服务器的socket 某个Channel对象负责一个fd的IO事件分发，但并不拥有这个fd 也不会在析构的时候关闭这个fd
   
    
    void setReadCallback(const EventCallback& cb) { printf("in Channel::setReadCallback\n");readCallback_ = cb; }
    void setWriteCallback(const EventCallback& cb) { printf("in Channel::setWriteCallback\n");writeCallback_ = cb; }
    void setErrorCallback(const EventCallback& cb) { printf("in Channel::setErrorCallback\n");errorCallback_ = cb; }
 //   void setMessageCallback(const MessageCallback& cb) { messageCallback_ = cb;}

    EventCallback getReadCallback() { return readCallback_; }
    EventCallback getWriteCallback() { return writeCallback_; }
    EventCallback getErrorCallback() { return errorCallback_;  }

    void handleEvent();
    void handleaccept();
    void handleRead();
    void handleWrite();
    void handleClose();
    void handleError();

    void enableRead() { printf("in Channel::enableRead\n");events_ |= EPOLLIN; }
//    void enableWrite() { events_ |= EPOLLOUT; changeEvent();} //这个设计感觉非常巧妙
//    void disableWrite() { events_ &= ~EPOLLOUT; changeEvent();} //忽略关注写事件
//    void changeEvent() { loop_->changeevent(fd(), get_events());}

    int sendmssage(const char* s, size_t len);
    int recvmessage();

    int fd() const { return fd_; }

    void set_revents(int revt) { printf("in Channel::set_revents\n");revents_ = revt; }//内核事件表给revents_
    int get_revents() const { return revents_; }
    int get_events() const { return events_; }

    int set_nonblock() { 
      printf("in Channel::set_noblock\n");
       int old_option = fcntl(fd(), F_GETFL);
       int new_option = old_option | O_NONBLOCK;
       fcntl(fd(), F_SETFL, new_option);
       return old_option;
    }

  //  int isReading() { return }
private:
        Eventloop *loop_;
        int fd_;
        int events_ = 0;
        int revents_ = 0;
        int status_ = 0;

        EventCallback readCallback_;
        EventCallback writeCallback_;
        EventCallback errorCallback_;
 //       MessageCallback messageCallback_;
};