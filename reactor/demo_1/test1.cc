#include "Eventloop.h"
#include "Channel.h"
#include "Epoll.h"
#include <sys/types.h>
#include <sys/socket.h>
//#include <linux/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>
#define LISTENQ 1024

int main(int argc, char const *argv[])
{
    Epoller poller;
    printf("main():pid = %d\n",getpid());
    
    signal(SIGPIPE, SIG_IGN);
    int fd = socket(AF_INET,SOCK_STREAM, 0);
    int on=1;
    std::cout<<"listenfd = "<<fd<<std::endl;
    int result = setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
    assert(result != -1);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_ANY); //
    socklen_t len = sizeof(addr);

    assert(bind( fd, (struct sockaddr*)&addr, len) >=0 );
    assert(::listen(fd, LISTENQ)>=0);

    //socket bind lisen 得到fd
   
    Eventloop loop(&poller);
    std::shared_ptr<Channel> listen_chl ( new Channel(&loop, fd, EPOLLIN | EPOLLERR /*| EPOLLET*/)); //不能注册写事件 这是listenfd的Channel
    listen_chl->setReadCallback(std::bind(&Channel::handleaccept, listen_chl)); //这里readcb绑定的是listenChannel需要接受的处理handleaccept 而在具体读事件的时候绑定的是Handleread
 //   listen_chl->setM;
// 只绑定 并没有真正的accept
    loop.addChannel(listen_chl);
  //  loop.get_epoller()->insert_Channel(std::make_pair(fd,listen_chl));//----------这里要用insert_channel 还是要用addChannel?
    loop.Loop();
    return 0;
}
