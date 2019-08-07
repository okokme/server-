#include "Acceptor.h"

Acceptor::Acceptor(Eventloop *loop, int port):loop_(loop) { 
        acceptsocket_.setPort(port);
        acceptsocket_.startConnect();
        acceptChannel_.reset(new Channel(loop, acceptsocket_.getfd(),EPOLLIN));
        
        acceptChannel_->setReadCallback(std::bind(&Acceptor::handleAccept, this )); 
        //这里readcb绑定的是listenChannel需要接受的处理handleaccept 而在具体读事件的时候绑定的是Handleread
    //    acceptChannel_->setMessageCallback(std::bind(&onMessage, std::placeholders::_1,std::placeholders::_2));
        acceptChannel_->setErrorCallback(std::bind(&Channel::handleError,acceptChannel_));
        loop_->addChannel(acceptChannel_);
}

void Acceptor::handleAccept()
{
    int connfd = acceptsocket_.acceptConnect();
    if(newConnectionCallback_)
        newConnectionCallback_(connfd);
}

