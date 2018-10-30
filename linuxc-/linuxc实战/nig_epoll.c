


/*************************************************************************
    * File: 1-1.c
    * Brief:
    * Author: luoyuxiang
    * Mail: 269724033@qq.com
    * Created Time: Sat 17 Dec 2016 08:00:39 PM CST
 ************************************************************************/

#ifndef _NIG_EPOLL_H_INCLUDED_
#define _NIG_EPOLL_H_INCLUDED_

#include "nig_header.h"
#include "nig_config.h"
#include "nig_http.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

struct epoll_event *evlist;

NIG_API int epoll_setnonblocking(int fd);

// 创建服务端  套接字并进行绑定
NIG_API  int epoll_socket_servers(const char* ip,int port);

/*
 * 创建连接fastcgi服务器的客户端套接字
 * 出错返回-1
 */
NIG_API  int epoll_socket_client(const char* fastcgi_host,int fastcgi_port);

//创建epoll
NIG_API  int epoll_create_event(int flag);

//添加事件
NIG_API void epoll_add_event(http_ret * ret, int state);

//修改事件
NIG_API  void epoll_update_event(http_ret * ret, int state);

//删除事件
NIG_API  void epoll_delete_event(http_ret * ret, int state);

#endif    /*end ifndef*/


//设置socket连接为非阻塞模式
//http://www.cnblogs.com/xuyh/p/3273082.html
NIG_API int epoll_setnonblocking(int fd) {
    /**
     fcntl 用命令F_GETFL和F_SETFL获取/设置文件标志，比如阻塞与非阻塞
　　 O_NONBLOCK  非阻塞I/O;
　  */
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option); //F_setfl设置文件标志非阻塞
    return old_option;
}

NIG_API  int epoll_socket_servers(const char* ip,int port)
{
    int  listenfd;
    int opt=1;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if (listenfd == -1)
    {
        perror("socket error:");
        exit(1);
    }
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopet error\n");
        exit(1);
    }
    epoll_setnonblocking(listenfd);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    if (bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
    {
        perror("bind error: ");
        exit(1);
    }
    return listenfd;
}


/*
 * 创建连接fastcgi服务器的客户端套接字
 * 出错返回-1
 */
int epoll_socket_client(const char * fastcgi_host, int fastcgi_port)
{
    int cgi_sock;
    struct sockaddr_in serv_addr;

    //创建套接字
    cgi_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == cgi_sock)
    {
        //error_log("socket error", DEBUGARGS);
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(fastcgi_host);
    serv_addr.sin_port = htons(fastcgi_port);

    /**
    if (bind(cgi_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1)
    {
        perror("bind error: ");
        exit(1);
    }
    **/
    // 连接服务器
    if(-1 == connect(cgi_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
    {
        //error_log("connect error", DEBUGARGS);
        return -1;
    }

    return cgi_sock;
}


NIG_API  int epoll_create_event(int flag) {
    int epfd = -1;
    epfd = epoll_create1(flag);
    if(epfd == -1) {
        perror("epoll_create1");
        return -1;
    }

    evlist = (struct epoll_event*)malloc(1024 * sizeof(struct epoll_event));
    if(evlist == NULL) {
        perror("malloc");
        return -1;
    }

    return epfd;
}

/**
 *
state表示感兴趣的事件和被触发的事件,可能的取值为：
   EPOLLIN：表示对应的文件描述符可以读；
   EPOLLOUT：表示对应的文件描述符可以写；
   EPOLLPRI：表示对应的文件描述符有紧急的数可读；
   EPOLLERR：表示对应的文件描述符发生错误；
   EPOLLHUP：表示对应的文件描述符被挂断；
   EPOLLET：    ET的epoll工作模式；
 *
 */

NIG_API void epoll_add_event(http_ret * ret, int state)
{
    struct epoll_event ev;
    ev.data.ptr = (void *)ret;
    //ev.data.fd = listenfd;
    ev.events = state;

    int s = -1;
    s = epoll_ctl(ret->epollfd, EPOLL_CTL_ADD, ret->fd, &ev);
    if(s == -1) {
        perror("http_epoll_add");
        return ;
    }
    epoll_setnonblocking(ret->fd);
    return ;
}


NIG_API  void epoll_update_event(http_ret * ret, int state)
{
    struct epoll_event ev;
    ev.data.ptr = (void *)ret;
    //ev.data.fd = listenfd;
    ev.events = state;

    int s = -1;
    s = epoll_ctl(ret->epollfd, EPOLL_CTL_MOD, ret->fd, &ev);
    if(s == -1) {
        perror("http_epoll_mod");
        return ;
    }
    return ;
}


NIG_API  void epoll_delete_event(http_ret * ret, int state)
{
    struct epoll_event ev;
    ev.data.ptr = (void *)ret;
    //ev.data.fd = listenfd;
    ev.events = state;

    int s = -1;
    s = epoll_ctl(ret->epollfd, EPOLL_CTL_DEL, ret->fd, &ev);
    if(s == -1) {
        perror("http_epoll_del");
        return ;
    }

    return ;
}
