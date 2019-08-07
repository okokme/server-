#include "buffer.h"
#include "Channel.h"
#include "Eventloop.h"
#include <iostream>
#include <functional>
#include <bits/stdc++.h>
#include <string>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/wait.h>

   
 void connection( Channel &firstSend ){
        firstSend.sendmssage();
    }

int sendFile(char* filename, int connfd, int start)
{
    int filefd = open(filename, O_RDONLY);
    if(filefd < 0 ) {
        std::cout<<"filefd = "<<filefd<<std::endl;
        return 0;
    }
    struct stat stat_buf;
    fstat(filefd, &stat_buf);
    int sum = start;
    while(sum < stat_buf.st_size) {
        off_t t = sum;
        int r = sendfile(connfd, filefd, &t, stat_buf.st_size);
        if(r < 0)
            continue;
        else
            sum += r;
    }
    close(filefd);
    printf( "fd =%d,sendfile finish, \n", connfd );    
    return stat_buf.st_size;
    
}

// type对应response的Content-Type，num为状态码，info为状态描述
int send_file(  std::string& gfilename, const char *type, int start, std::shared_ptr<Channel> chl, const int num, const char *info ) 
{    
    struct stat filestat;
    char header[500];
    int fd; 
    std::cout<<"gfilename = " << gfilename << std::endl;  
    char* filename = const_cast<char*>(gfilename.c_str());
    std::string error_file = "/home/k/server-/reactor/My_web_server_2.0/test/404.html";

    int ret = stat( filename, &filestat );
    if( ret < 0 || !S_ISREG( filestat.st_mode ) ) {  // 打开文件出错或没有该文件
        std::cout << "errno:" <<filename <<"  err="<< errno  << std::endl;
        if(open(filename,O_RDWR) < 0)
        {
            send_file( error_file, "text/html", start, chl, 200, "OK"  );
        }
    }
    bzero(header, strlen(header));
    sprintf( header, "HTTP/1.1 %d %s\r\nServer: okokme\r\nContent-Length: %d\r\nContent-Type: %s;\r\ncharset:utf-8\r\n\r\n", num, info, int(filestat.st_size - start), type );
    chl->send(header, strlen(header));
    sendFile(filename, chl->fd(), start);
    return 0;
}

   

int deal_get( const std::string & uri, int start, std::shared_ptr<Channel> chl ) {
    std::string filename = uri.substr(0);
    std::string index = "/home/k/server-/reactor/My_web_server_2.0/test/index.html";
    std::string error_file = "/home/k/server-/reactor/My_web_server_2.0/test/404.html";
    std::string ico = "/home/k/server-/reactor/My_web_server_2.0/img/favicon.ico";

     if( uri == "/" || uri == "/index.html" ) {
        send_file( index, "text/html", start, chl, 200, "OK"  );
    } else if( uri.find( ".jpg" ) != std::string::npos || uri.find( ".png" ) != std::string::npos ) {
        send_file( filename, "image/jpg", start, chl, 200, "OK" );
        printf("filename:%s",filename.c_str());
    } else if( uri.find( ".html" ) != std::string::npos ) {
        send_file( filename, "text/html; charset=utf-8", start, chl, 200, "OK" );
    } else if( uri.find( ".ico" ) != std::string::npos ) {
        send_file( ico, "image/x-icon", start, chl, 200, "OK" );
    } else if( uri.find( ".js" ) != std::string::npos ) {
        send_file( filename, "yexy/javascript", start, chl, 200, "OK" );
    } else if( uri.find( ".css" ) != std::string::npos ) {
        send_file( filename, "text/css", start, chl, 200, "OK" );
    } else if( uri.find( ".mp3" ) != std::string::npos ) {
        send_file( filename, "audio/mp3", start, chl, 200, "OK" );
    } else if( uri.find( ".mp4" ) != std::string::npos ) {
        send_file( filename, "audio/mp4", start, chl, 200, "OK" );
    } else {
        send_file( filename, "text/plain", start, chl, 200, "OK" );
    }
}

// /CGI/addr
int deal_post( const std::string & uri, char *buf, std::shared_ptr<Channel> chl) {
    std::cout<<"In deal_post"<<std::endl;
    std::string filename = uri.substr(0);
//    std::string filename = "/home/k/server-/reactor/My_web_server_2.0/src/config/CGI/addr";
    std::cout<<"filename:"<<filename<<std::endl;
    std::string html = "/home/k/server-/reactor/My_web_server_2.0/test/404.html";
    if( uri.find( "adder" ) != std::string::npos ) {  //使用CGI服务器，进行加法运算
        char *tmp = buf;
        int len, a, b;
        char *l = strstr( tmp, "Content-Length:" );  //判断ContentLeng是不是tmp的子串
        sscanf( l, "Content-Length: %d", &len );// 获取请求报文主体大小
        len = strlen( tmp ) - len;       
        tmp += len;
        sscanf( tmp, "a=%d&b=%d", &a, &b );
        sprintf(tmp, "%d+%d,%d", a, b, chl->fd());  // tmp存储发送到CGI服务器的参数

        // fork产生子进程，执行CGI服务器进行计算（webServer只进行解析、发送数据，不进行相关计算）
        if( fork() == 0 ) {
            // dup2( accp_fd, STDOUT_FILENO );
            execl( filename.c_str(), tmp, NULL );
        }
        wait( NULL );  // 等待子进程结束
    } else {
        send_file( html, "text/html", 0, chl,404, "Not Found" );
    }
}

void onMessage(std::shared_ptr<Channel> chl, Buffer buf_) //Buffer&
{
    printf("buf address = %p\n",buf_.begin());
    std::cout<<"onMessage"<<std::endl;
 //   std::cout<<buf_.c_str()<<std::endl;
    int crlf;
    while(buf_.readable() >= 4)
    {
        crlf = buf_.findCrlf();
        if(crlf >= 0)
        {
            int start = 0;
            char method[5], uri[100], version[10];
            char* b = buf_.begin();
            sscanf( b, "%s %s %s", method, uri, version );
            printf("recv: method=%s uri=%s version=%s\n",method,uri,version);
            if( char *tmp =  std::strstr( b, "Range:" ) ) { //断点续传
                tmp += 13;
                sscanf( tmp, "%d", &start );
            }
        
            if( !strcmp( method, "GET" ) ) {  // 为GET
                deal_get( uri, start,  chl);
            } 
            else if( !strcmp( method, "POST" ) ) {  // 为POST
                deal_post( uri, b, chl );
            }
            else {
                const char *header = "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/plain;charset=utf-8\r\n\r\n";
                chl->send(  header, strlen(header));
            }  
           // crlf = -1;
        }
        //else
        //{
             buf_.retrieve(crlf);
            break;  // 只要处理完就退出循环，避免浏览器一直处于pending状态
       // }
    }
}
