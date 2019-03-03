#include "task.h"

void removefd( int epollfd, int fd ) {
    epoll_ctl( epollfd, EPOLL_CTL_DEL, fd, 0 );
    //移除多路复用实例中的一个socket的文件描述符
    close( fd );
}
void my_err(const char* err_string, int line )
{
    fprintf(stderr, "line: %d", line);
    perror(err_string);
}


void Task::doit() {
    char buf[ BUFFER_SIZE ] = {0};

    while( int r = recv( accp_fd, buf, 1024, 0 ) ) {
        if( !r ) {
            cout << " browser exit.\n"<<endl;
            break;
        } else if( r < 0 ) {  // 如果接收出错则继续接收数据
            perror("recv <0");
            continue;
        }
//排错：接受没问题，发送出错会有r<0的时候此时errno = 11，且设置了EPOLLONESHOT事件确实是一个socket只能被一个线程处理，但是只要一有错，就会触发别的线程处理?

        buf[strlen(buf)+1]='\0';
                printf("%s\n",buf);
                printf("successeful!\n");

        int start = 0;
        char method[5], uri[100], version[10];
        sscanf( buf, "%s %s %s", method, uri, version );
printf("recv: method=%s uri=%s version=%s\n",method,uri,version);
        if( char *tmp = strstr( buf, "Range:" ) ) {
            tmp += 13;
            sscanf( tmp, "%d", &start );
        }

        if( !strcmp( method, "GET" ) ) {  // 为GET
            deal_get( uri, start );
        } else if( !strcmp( method, "POST" ) ) {  // 为POST
            deal_post( uri, buf );
        } else {
            const char *header = "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/plain;charset=utf-8\r\n\r\n";
            send( accp_fd, header, strlen(header), 0 );
        }
        break;  // 只要处理完就退出循环，避免浏览器一直处于pending状态
    }
    // close( accp_fd );  // 任务完成直接close，不能在析构函数close(如果不delete task的话，
                          // 不delete task不够调用析构函数)
}

int Task::deal_get( const string & uri, int start ) {
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

int Task::deal_post( const string & uri, char *buf ) {
    string filename = uri.substr(1);
    if( uri.find( "adder" ) != string::npos ) {  //使用CGI服务器，进行加法运算
        char *tmp = buf;
        int len, a, b;
        char *l = strstr( tmp, "Content-Length:" );  //判断ContentLeng是不是tmp的子串
        sscanf( l, "Content-Length: %d", &len );// 获取请求报文主体大小
       // printf("len1=%d\n",len);
        len = strlen( tmp ) - len;
      //  printf("len2=%d\n",len);
       // printf("tmp=%s\n",tmp);        
        tmp += len;
        //printf("tmp=%s\n",tmp);
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
int Task::send_file( const string & filename, const char *type, 
                            int start, const int num, const char *info ) {
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



