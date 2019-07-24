#include "Epoll.h"
#include "Channel.h"

int Epoller::add(int fd, int event) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_ADD,fd,&ev) != -1);
}

int Epoller::mod(int fd, int event) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = event;
    assert(epoll_ctl(epfd_,EPOLL_CTL_MOD,fd,&ev) != -1);
}

int Epoller::del(int fd) {
    assert(epoll_ctl(epfd_,EPOLL_CTL_DEL,fd,0) != -1);
}
 