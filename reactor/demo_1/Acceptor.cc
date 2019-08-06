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
    
    // std::shared_ptr<Channel> accept_cha ( new Channel(loop_, connfd, EPOLLIN | EPOLLERR));
    // accept_cha->setFd(connfd);
    
    // accept_cha->setReadCallback( std::bind(&Channel::handleRead, accept_cha)); //std::function<void()>  ////////不知道该bind啥
    // accept_cha->setMessageCallback(messageCallback_);
    // accept_cha->setErrorCallback(std::bind(&Channel::handleError, accept_cha));
    
    // loop_->addChannel(accept_cha);
}

