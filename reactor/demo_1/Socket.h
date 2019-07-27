#pragma once

#include "Noncopyable.h"
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/in.h>

class Socket : Noncopyable {
public:
    Socket() { 
        sockfd_ = socket(AF_INET,SOCK_STREAM,0);
    }
    void bind() {
        struct sockaddr_in addr;


    }
    ~Socket() { close(sockfd_); }

private:
    int sockfd_;

}