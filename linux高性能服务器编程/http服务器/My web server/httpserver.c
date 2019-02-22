#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<pthread.h>
//监听套接字创建
int create_listenfd()
{
    //sbla,shabila
    //创建tcp连接
    int fd = socket(AF_INET, SOCK_STREAM ,0);
    //绑定地址
    struct sockaddr_in sin;
    bzero(&sin,sizeof(sin));//清空
    sin.sin_family = AF_INET;
    sin.sin_port = htons(80); //80是Http默认端口
    sin.sin_addr.s_addr = htonl(INADDR_ANY); //监听任意网卡
    //serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int res = bind(fd, (struct sockaddr *)&sin, sizeof(sin));
    //if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0)//将IP与端口绑定在一起
    
    if(res == -1)
    {
        perror("bind");//将错误信息打印出来
    }
    listen(fd,100); //监听
    return fd;
}

int main()
{
    //1 创建监听套接字，返回是套接字描述符
    int socket = create_listenfd();

    //2 接受客户端的连接
    int fd = accept(socket, NULL,NULL); //这里会阻塞，有结果才会往下走 
    printf("有客户端连接");
    //3 处理客户端发来的请求

    close(fd);
    close(socket);
}