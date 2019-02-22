#pragma once
#include "task.h"
#include "threadPool.h"
using namespace std;

const int max_event_num = 20;

class webServer
{
public:
    webServer(int p):sock_fd, port(p){memset( &server_addr, 0, sizeof(server_addr) );}
    ~webServer() { close(sock_fd); }
private:
    int port;
    int sock_fd;
    int epoll_fd;
    struct sockaddr_in server_addr;
public:
    int run();
}