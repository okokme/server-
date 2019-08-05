//内部Class，供TcpServer使用
#pragma once
#include "Eventloop.h"
#include "Channel.h"
#include "Noncopyable.h"
#include "Socket.h"
#include "Coder.h"

class Channel;
class Acceptor : Noncopyable{
public: 
    typedef std::function<void(int fd)> NewConnectionCallback;
     Acceptor(Eventloop *loop, int port);//:loop_(loop);
    ~Acceptor();
    void setNewConnectionCallback(NewConnectionCallback cb) { newConnectionCallback_ = cb; } //accept回调
 //   bool listenning() const { return listenning; }
    void listen() { }
    std::shared_ptr<Channel> getChannel() { return acceptChannel_; }
private:
    //调用accept()接受新的连接 并回调用户callback
    void handleAccept();
    //acceptChannel所属的loop对象
    Eventloop* loop_;
    //此socket是listen socket
    Socket acceptsocket_;
    //Channel对象检测上述socket上的readable事件
    //并在Channel对象的handleEvent方法中回调handleRead(),handleRead会调用accept来接受新连接
    std::shared_ptr<Channel> acceptChannel_;
    NewConnectionCallback newConnectionCallback_;
 //   bool listenning;
    int idlefd_;

};
