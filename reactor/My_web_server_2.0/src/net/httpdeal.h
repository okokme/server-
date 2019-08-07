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
     
    int ret = stat( filename, &filestat );

    if( ret < 0 || !S_ISREG( filestat.st_mode ) ) {  // 打开文件出错或没有该文件
        std::cout << "errno:" <<filename <<"  err="<< errno  << std::endl;

        char path_404[200];//出错码404对应文件名缓冲区
        strcpy(path_404,"/home/k/server-/reactor/My_web_server_2.0/test/404.html");
        int file_size = sendFile(path_404, chl->fd(), start);
        bzero(header, strlen(header));    
        sprintf(header,"HTTP/1.1 404 NOT_FOUND\r\nConnection: close\r\ncontent-length:%d\r\n\r\n",file_size);
        chl->send(header, strlen(header));
        return -1;
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

    // if(open(filename.c_str(),O_RDWR) < 0)
    // {
    //     send_file( error_file, "text/html", start, chl, 200, "OK"  );
    // }
     if( uri == "/" || uri == "/index.html" ) {
        send_file( index, "text/html", start, chl, 200, "OK"  );
    } else if( uri.find( ".jpg" ) != std::string::npos || uri.find( ".png" ) != std::string::npos ) {
        send_file( filename, "image/jpg", start, chl, 200, "OK" );
        printf("filename:%s",filename.c_str());
    } else if( uri.find( ".html" ) != std::string::npos ) {
        send_file( filename, "text/html; charset=utf-8", start, chl, 200, "OK" );
    //} else if( uri.find( ".ico" ) != std::string::npos ) {
    //     send_file( filename, "image/x-icon", start, chl, 200, "OK" );
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

int deal_post( const std::string & uri, char *buf, std::shared_ptr<Channel> chl) {
    std::string filename = uri.substr(1);
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


 // void onMessage(std::shared_ptr<Channel> chl, Buffer& buf_)
    // {
    //     std::cout<<"onMessage"<<std::endl;
    //     std::cout<<buf_.c_str()<<std::endl;
    //     // const char* s = "non-blocking网络编程中，在Tcp这种字节流协议上做应用层分包是网络编程的基本需求。（muduo p194） 什么叫分包？ 分包指的是在发送一个消息或一帧数据时，通过一定的处理，让接收方能从字节流中识别并截取（还原）出一个个消息。 为什么需要打包和分包？ 因为tcp一次发送的数据可能不足一个完整的消息，或者包含多个消息。tcp一次发送数据的大小与内核中发送缓冲区的大小有关，如果当前发送缓冲区空余空间很小，那么可能一次就发送不了一个完整的消息；也有可能内核经过优化把两次send的数据仅合并成一次发送，这样对方收到的数据就会包含多个消息。所以我们在发送数据时需要在一条消息数据中再多添加一些额外信息让接受端可以正确识别一个个消息。 常用的打包方式有哪些？ 对于短连接的tcp服务，分包不是一个问题，只要发送方主动关闭连接，就表示一个消息发送完毕，接收方read返回0，从而知道消息的结尾。 对于长连接的tcp服务，打包有四种方法： 1） 消息长度固定 2） 使用特殊的字符或者字符串作为消息的边界。例如http协议的headers以\r\n为字段的分隔符 3） 在每条消息的头部加一个字段长度 4） 利用消息本身的格式来分包，例如xml中 的配对，或者json格式中的{…}的配对。解析这种消息格式通常会用到状态机。 muduo的打包分包基本原理： 1）当发送端发送一个结构体时，首先使用protobuf进行序列化，然后计算序列化数据的长度，然后使用“长度+序列化数据”的打包方式发送给接收端，接收端接收到数据后对数据进行分包，首先读取数据长度，然后根据长度读取序列化数据，并对数据进行反序列化得到完整的消息结构。 （2）当发送端只发送一个简单的字符串时，可以使用“字符串长度+字符串数据”这种简单的打包方式，打包后的数据存放到muduo::net::Buffer，然后发送出去。接收的数据同样存放在muduo::net。 实现长度分包的代码： muduo实现长度分包的代码由类LengthHeaderCodec 实现。代码位于https://github.com/chenshuo/muduo/blob/master/examples/asio/chat/codec.h LengthHeaderCodec实现发送功能的代码为：---------------------作者：sunny_ss12来源：CSDN原文：https://blog.csdn.net/sunny_ss12/article/details/46802955版权声明：本文为博主原创文章，转载请附上博文链接！";
    //     // write(chl->fd(), s, strlen(s));
    //     // buf_.retrieve(strlen(s));
    // }