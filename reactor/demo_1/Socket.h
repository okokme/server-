#pragma once

#include "Noncopyable.h"
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

class Socket : Noncopyable {
public:
    Socket() { }
    ~Socket() { close(sockfd_); }

private:
    int sockfd_;
}