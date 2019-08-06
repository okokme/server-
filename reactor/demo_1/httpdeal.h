#include "buffer.h"
#include "Channel.h"
#include "Eventloop.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <string.h>
// class Channel;
// class Coder {
// public:

// private:


// };    

    void onMessage(std::shared_ptr<Channel> chl, Buffer& buf_)
    {
        std::cout<<"onMessage"<<std::endl;
        std::cout<<buf_.c_str()<<std::endl;
        const char* s = "non-blocking网络编程中，在Tcp这种字节流协议上做应用层分包是网络编程的基本需求。（muduo p194） 什么叫分包？ 分包指的是在发送一个消息或一帧数据时，通过一定的处理，让接收方能从字节流中识别并截取（还原）出一个个消息。 为什么需要打包和分包？ 因为tcp一次发送的数据可能不足一个完整的消息，或者包含多个消息。tcp一次发送数据的大小与内核中发送缓冲区的大小有关，如果当前发送缓冲区空余空间很小，那么可能一次就发送不了一个完整的消息；也有可能内核经过优化把两次send的数据仅合并成一次发送，这样对方收到的数据就会包含多个消息。所以我们在发送数据时需要在一条消息数据中再多添加一些额外信息让接受端可以正确识别一个个消息。 常用的打包方式有哪些？ 对于短连接的tcp服务，分包不是一个问题，只要发送方主动关闭连接，就表示一个消息发送完毕，接收方read返回0，从而知道消息的结尾。 对于长连接的tcp服务，打包有四种方法： 1） 消息长度固定 2） 使用特殊的字符或者字符串作为消息的边界。例如http协议的headers以\r\n为字段的分隔符 3） 在每条消息的头部加一个字段长度 4） 利用消息本身的格式来分包，例如xml中 的配对，或者json格式中的{…}的配对。解析这种消息格式通常会用到状态机。 muduo的打包分包基本原理： 1）当发送端发送一个结构体时，首先使用protobuf进行序列化，然后计算序列化数据的长度，然后使用“长度+序列化数据”的打包方式发送给接收端，接收端接收到数据后对数据进行分包，首先读取数据长度，然后根据长度读取序列化数据，并对数据进行反序列化得到完整的消息结构。 （2）当发送端只发送一个简单的字符串时，可以使用“字符串长度+字符串数据”这种简单的打包方式，打包后的数据存放到muduo::net::Buffer，然后发送出去。接收的数据同样存放在muduo::net。 实现长度分包的代码： muduo实现长度分包的代码由类LengthHeaderCodec 实现。代码位于https://github.com/chenshuo/muduo/blob/master/examples/asio/chat/codec.h LengthHeaderCodec实现发送功能的代码为：---------------------作者：sunny_ss12来源：CSDN原文：https://blog.csdn.net/sunny_ss12/article/details/46802955版权声明：本文为博主原创文章，转载请附上博文链接！";
        write(chl->fd(), s, strlen(s));
        buf_.retrieve(strlen(s));
    }
    void connection( Channel &firstSend ){
        firstSend.sendmssage();
    }


void onMessage(std::shared_ptr<Channel> chl, Buffer& buf_)
{

    std::cout<<"onMessage"<<std::endl;
    std::cout<<buf_.c_str()<<std::endl;

    int start = 0;
    char method[5], uri[100], version[10];
    sscanf( buf_, "%s %s %s", method, uri, version );
    printf("recv: method=%s uri=%s version=%s\n",method,uri,version);
    if( char *tmp = strstr( buf_, "Range:" ) ) {
        tmp += 13;
        sscanf( tmp, "%d", &start );
    }

    if( !strcmp( method, "GET" ) ) {  // 为GET
        deal_get( uri, start );
    } else if( !strcmp( method, "POST" ) ) {  // 为POST
        deal_post( uri, buf_ );
    } else {
        const char *header = "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/plain;charset=utf-8\r\n\r\n";
        send( accp_fd, header, strlen(header), 0 );
    }
    break;  // 只要处理完就退出循环，避免浏览器一直处于pending状态
}


int deal_get( const string & uri, int start ) {
    string filename = uri.substr(1);

    if( uri == "/" || uri == "/index.html" ) {
        send_file( "index.html", "text/html", start );
    } else if( uri.find( ".jpg" ) != string::npos || uri.find( ".png" ) != string::npos ) {
        send_file( filename, "image/jpg", start );
        printf("filename:%s",filename.c_str());
    } else if( uri.find( ".html" ) != string::npos ) {
        send_file( filename, "text/html", start );
    } else if( uri.find( ".ico" ) != string::npos ) {
        send_file( filename, "image/x-icon", start );
    } else if( uri.find( ".js" ) != string::npos ) {
        send_file( filename, "yexy/javascript", start );
    } else if( uri.find( ".css" ) != string::npos ) {
        send_file( filename, "text/css", start );
    } else if( uri.find( ".mp3" ) != string::npos ) {
        send_file( filename, "audio/mp3", start );
    } else if( uri.find( ".mp4" ) != string::npos ) {
        send_file( filename, "audio/mp4", start );
    } else {
        send_file( filename, "text/plain", start );
    }
}

int deal_post( const string & uri, char *buf ) {
    string filename = uri.substr(1);
    if( uri.find( "adder" ) != string::npos ) {  //使用CGI服务器，进行加法运算
        char *tmp = buf;
        int len, a, b;
        char *l = strstr( tmp, "Content-Length:" );  //判断ContentLeng是不是tmp的子串
        sscanf( l, "Content-Length: %d", &len );// 获取请求报文主体大小
        len = strlen( tmp ) - len;       
        tmp += len;
        sscanf( tmp, "a=%d&b=%d", &a, &b );
        sprintf(tmp, "%d+%d,%d", a, b, accp_fd);  // tmp存储发送到CGI服务器的参数

        // fork产生子进程，执行CGI服务器进行计算（webServer只进行解析、发送数据，不进行相关计算）
        if( fork() == 0 ) {
            // dup2( accp_fd, STDOUT_FILENO );
            execl( filename.c_str(), tmp, NULL );
        }
        wait( NULL );  // 等待子进程结束
    } else {
        send_file( "html/404.html", "text/html", 0, 404, "Not Found" );
    }
}



// type对应response的Content-Type，num为状态码，info为状态描述
//后两项默认填200 OK 遇到不同状况再改
int send_file( const string & filename, const char *type, 
                            int start, const int num, const char *info ) {


                                //chl->send()
    struct stat filestat;
    char header[200];
    int fd;    
    int ret = stat( filename.c_str(), &filestat );
    if( ret < 0 || !S_ISREG( filestat.st_mode ) ) {  // 打开文件出错或没有该文件
        test_i++;
        printf("accp_fd = %d, epoll_fd = %d, i = %d\n",accp_fd,epoll_fd,test_i);

        cout << "file not found : " << filename << endl;

   char path_404[40];//出错码404对应文件名缓冲区
 //  char *url;//文件名称
  //  bzero(url, strlen(url));
    strcpy(path_404,"404.html");
 //   url = path_404;
    char filename2[200];
    bzero(filename2,sizeof(filename2));
    sprintf(filename2,"/home/k/linuxc-/linux高性能服务器编程/http服务器/My web server%s",path_404);
    struct stat my_file;
    if(stat(filename2,&my_file)<0)
    {
        cout << "获取失败\n";
    }
    int file_size = my_file.st_size;
   // char header[200];
    sprintf(header,"HTTP/1.1 404 NOT_FOUND\r\nConnection: close\r\ncontent-length:%d\r\n\r\n",file_size);
    send( accp_fd, header, strlen(header), 0 );
    fd = open(path_404, O_RDONLY); //打开404文件
    close(fd);
    return -1;

    }

   // char header[200];
    sprintf( header, "HTTP/1.1 %d %s\r\nServer: okokme\r\nContent-Length: %d\r\nContent-Type: %s;\r\ncharset:utf-8\r\n\r\n", num, info, int(filestat.st_size - start), type );

    // send第二个参数只能是c类型字符串，不能使用string
    send( accp_fd, header, strlen(header), 0 );

    fd = open( filename.c_str(), O_RDONLY ); //打开文件
    int sum = start;

    while( sum < filestat.st_size ) {
        off_t t = sum;

        int r = sendfile( accp_fd, fd, &t, filestat.st_size );
        //ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count); 返回值：成功传输的字节数
        //out_fd 是已经打开了,用于写操作(write)的文件描述符;
        //in_fd 是已经打开了,用于读操作(read)的文件描述符;
        //offset 偏移量;表示sendfile函数从in_fd中的哪一偏移量开始读取数据.如果是零表示从文件的开始读,否则从相应的偏移量读取.如果是循环读取的时候,下一次offset值应为sendfile函数返回值加上本次的offset的值.
        //count是在两个描述符之间拷贝的字节数(bytes)

        // if( r < 0 ) {

        //     printf("errno = %d, r = %d\n", errno, r);
        //      perror("sendfile : ");
        //     if( errno == EAGAIN ) {
        //         printf("errno is EAGAIN\n");
        //         //continue;
        //     } else {
        //         perror( "sendfile " );
        //         close( fd );
        //         break;
        //     }
        // } else {
        //     sum += r;
        // }
        if(r < 0)
        {
            continue;
        }
        else
            sum += r;
    }
    close( fd );
    printf( "sendfile finish, %d\n", accp_fd );
    return 0;
}

int Task::get_size( const string & filename ) {
    struct stat filestat;
    int ret = stat( filename.c_str(), &filestat );
    if( ret < 0 ) {
        cout << "file not found : " << filename << endl;
        return 0;
    }
    return filestat.st_size;
}


    void connection( Channel &firstSend ){
        firstSend.sendmssage();
    }