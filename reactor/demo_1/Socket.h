#pragma once

#include "Noncopyable.h"
#include <memory>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include <arpa/inet.h>
#define LISTENQ 1024
class Socket : Noncopyable {
public:
    Socket() { }
    void setReuseAddr();
    int setNonblock();
    void bind();
    void listen();
    void startConnect();
    void setFd( int fd ) { sockfd_ = fd; }
    int getfd() { return sockfd_; }
    int acceptConnect();
    ~Socket() { close(sockfd_); }

private:
    int sockfd_;
};