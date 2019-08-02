#include "Eventloop.h"
#include "Channel.h"
#include "Epoll.h"
#include "buffer.h"
#include "Coder.h"
#include "Socket.h"
#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>

#define LISTENQ 1024

//把onMessage绑定到listenfd的Channel中让接受来的每一个事件都有一个onMessage

int main(int argc, char const *argv[])
{
    Epoller poller;
    printf("main():pid = %d\n",getpid());

    Eventloop loop(&poller);
    std::shared_ptr<Channel> listen_chl ( new Channel(&loop, EPOLLIN));//不能注册写事件 这是listenfd的Channel
    listen_chl->getsocket().startConnect();
    listen_chl->setReadCallback(std::bind(&Channel::handleaccept, listen_chl)); 
    //这里readcb绑定的是listenChannel需要接受的处理handleaccept 而在具体读事件的时候绑定的是Handleread
    listen_chl->setMessageCallback(std::bind(&onMessage, std::placeholders::_1, std::placeholders::_2)); 
    //因为listen的Channel没有message需要处理所以不用管onMessage将消息送到buffer，但是接下来一系列事件都需要buffer的参与，而每个事件都是经由listen的Channel来注册的。所以，别的Channel在listenfd的Channel中注册时就可以通过listenfd的Channel传参注册OnMessage了，而buffer设置在onMessage中，有事件需要读的时候，就调用onMessage 
    // 只绑定 并没有真正的accept
    loop.addChannel(listen_chl);
    loop.Loop();
    return 0;
}
