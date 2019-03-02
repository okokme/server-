#pragma once
#include "task.h"
#include "ThreadPool.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
const int max_event_num = 20;

class webServer
{
private:
    int port;
    int sock_fd;
    int epoll_fd;
    struct sockaddr_in server_addr;
public:
    webServer(int p){
        port = p;
        sock_fd = 0;
        memset( &server_addr, 0, sizeof(server_addr) );
    }

    ~webServer() {
        close(sock_fd);
    }


public:
    int run();
};
