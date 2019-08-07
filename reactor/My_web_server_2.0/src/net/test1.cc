#include "Eventloop.h"
#include "Channel.h"
#include "Epoll.h"
#include "buffer.h"
//#include "Coder.h"
#include "Socket.h"
#include "TcpServer.h"
#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>
#include "httpdeal.h"

//把onMessage绑定到listenfd的Channel中让接受来的每一个事件都有一个onMessage

class Server {
public:
    Server(Eventloop* loop, int port):loop_(loop),server_(loop, port) { 
         server_.setConnectionCallback(std::bind(connection,  std::placeholders::_1 ));
         server_.setMessageCallback(std::bind(onMessage, std::placeholders::_1, std::placeholders::_2));
    }
    void start() { server_.start(); }
   
private:
    TcpServer server_;
    Eventloop *loop_;
};

int main(int argc, char const *argv[])
{
    printf("main():pid = %d\n",getpid());
    Eventloop loop;
    Server server(&loop, 8888);
    server.start();
    loop.Loop();
    return 0;
}
