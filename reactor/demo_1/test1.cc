#include <iostream>
#include "Eventloop.h"
#include "Channel.h"
#include "Epoll.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    Epoller poller;
    printf("main():pid = %d\n",getpid());

    //socket bind lisen 得到fd
    
    Eventloop loop(&poller);
    Channel *listen_chl = new Channel(&loop, fd, EPOLLIN | EPOLLERR); //不能注册写事件 这是listenfd的Channel
    listen_chl->accept
    loop.Loop();
    return 0;
}
