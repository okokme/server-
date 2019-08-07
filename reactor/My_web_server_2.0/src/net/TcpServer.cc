
#include "TcpServer.h"    
TcpServer::TcpServer(Eventloop* loop, const int port):loop_(loop), acceptor_(loop, port){
    acceptor_.setNewConnectionCallback(std::bind(&TcpServer::NewConnection, this, std::placeholders::_1));
   
}
void TcpServer::NewConnection(int fd)
{
    //acceptor_.//绑定Channel中的Handleaccept
    std::cout<<"a new connection will add a new channel from handleaccept"<<std::endl;
    std::shared_ptr<Channel> accept_cha ( new Channel(loop_, fd, EPOLLIN | EPOLLERR));
    accept_cha->setFd(fd);
    
    accept_cha->setReadCallback( std::bind(&Channel::handleRead, accept_cha)); //std::function<void()>  ////////不知道该bind啥
    std::cout<<"setReadCallback = handleRead ......."<<std::endl;
    accept_cha->setMessageCallback(this->messageCallback_);
    accept_cha->setErrorCallback(std::bind(&Channel::handleError, accept_cha));

    loop_->addChannel(accept_cha); /////////这里触发了每个事件都会有新的Channel

}

void TcpServer::start() 
{
    if(connectionCallback_)
        connectionCallback_(*acceptor_.getChannel().get());
}