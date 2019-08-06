#pragma once

#include "Eventloop.h"
#include "Channel.h"
#include "Epoll.h"
#include "buffer.h"
//#include "Coder.h"
#include "Socket.h"
#include "Acceptor.h"
#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>

class Acceptor;
class Eventloop;
class Channel;
class TcpServer {
public:
  
    typedef std::function<void(Channel& )> ConnectionCallback;
    typedef std::function<void(std::shared_ptr<Channel>, Buffer&)> MessageCallback;
    
    TcpServer(Eventloop* loop, const int port); 
    ~TcpServer() { }

    Eventloop* getLoop() const { return loop_; }
    void NewConnection(int fd);
    void start();
    //set connection Callback 
    //not thread safe
    void setConnectionCallback(const ConnectionCallback cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback cb) { messageCallback_ = cb; }
private:
    Eventloop* loop_;
    Acceptor acceptor_;
    ConnectionCallback connectionCallback_; 
    MessageCallback messageCallback_;
};