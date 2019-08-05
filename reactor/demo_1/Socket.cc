#include "Socket.h"

void Socket::setReuseAddr() {
    int on=1;
    int result = setsockopt( sockfd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
    assert(result != -1);
}
int Socket::setNonblock() { 
    int old_option = fcntl(sockfd_, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(sockfd_, F_SETFL, new_option);
    return old_option;
}
void Socket::bind() {
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //("127.0.0.1")inet_addr("127.0.0.1");
    socklen_t len = sizeof(addr);
    assert( ::bind( sockfd_, (struct sockaddr*)&addr, len) >=0 );
}
void Socket::listen() {
    assert(::listen(sockfd_, LISTENQ)>=0);
} 

int Socket::acceptConnect() {
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int connfd =  ::accept( sockfd_,(struct sockaddr*)&cliaddr, &len);
_again:
    if(connfd < 0) {
        if(errno == EINTR)
            goto _again;
        if (errno != EWOULDBLOCK /* BSD */
         && errno != EPROTO  /* SERV4 */
         && errno != ECONNABORTED)  /* POSIX */
            perror("accept error");
    }
    setNonblock();
    return connfd;
}

void Socket::startConnect() {
    signal(SIGPIPE, SIG_IGN);
    if((sockfd_ = socket(AF_INET,SOCK_STREAM,0)) <0 )
        perror("socket err");

    setNonblock();
    setReuseAddr();
    bind();
    listen();
}

