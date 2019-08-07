#pragma once


#include "ThreadPool.h"
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/wait.h>
#include <errno.h>
#define BUFFER_SIZE 1024

using namespace std;
void removefd(int epollfd, int fd);
void my_err(const char* err_string, int line );

//封装执行任务的类
class Task
{
private:
    int accp_fd; //存储accept的返回值，客户端的fd
    int epoll_fd; //多路复用中的一个socket文件描述符
    int test_i;
public:
    Task() {}
    Task(int fd, int epoll): accp_fd(fd), epoll_fd(epoll) { test_i=0; cout<<accp_fd<<"start\n"<<endl;}
    ~Task() {removefd(epoll_fd, accp_fd); cout<<accp_fd<<"close\n"<<endl;}
    void doit(); //执行任务
    int send_file(const string &filename, const char *type, int start,const int num = 200,const char *info = "OK");//发送
    int deal_get(const string & uri, int start = 0); //处理GET请求
    int deal_post(const string & uri, char *buf );//处理POST请求
    int get_size(const string & filename);//获取文件大小 

};

