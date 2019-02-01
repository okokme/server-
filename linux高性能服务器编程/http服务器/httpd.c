#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>
#include<strings.h>
#include<string.h>
#include<sys/stat.h>
#include<pthread.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdint.h>

#define ISspace(x) isspace((int)(x)) //检查参数是否为空格字符
#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
#define STDIN  0
#define STDOUT 1
#define STDERR 2

int startup(u_short *);//初始化Http服务器，包括建立套接字，绑定端口，进行监听等
void accept_request(void *);//处理从套接字上间听到的一个HTTP请求，在这里可以很大一部分地体现服务器处理请求流程
void unimplemented(int client);//返回给浏览器表明收到的HTTP 请求所用的method不被支持
void not_found(int client);//处理找不到文件的情况
void server_file(int client, const char *filename);//调用cat把服务器文件返回给浏览器
void headers(int client, const char *filename); //发送头部
void cat(int client, FILE* filename);//读取服务器上某个文件写到socket套接字
void excute_cgi(int client, const char *path, const char *method, const char *query_string);//运行CGI程序的处理，也是主要这个函数
int get_line(int sock, char *buf, int size);//读取套接字的一行把回车换行等情况都统一为换行结束符
void bad_request(int client);//返回客户端 这是个错误请求，HTTP状态码400 BAD REQUEST
void cannot_execute(int client);//主要处理发生在CGI程序的错误
void err_die(const char *sc);//调用perror打印错误信息并退出

void err_die(const char *sc)
{
    perror(sc);
    exit(1);
}
void cannot_execute(int client)
{
    char buf[1024];
    sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
    send(client, buf, strlen(buf), 0);        
}
void bad_request(int client)
{
    char buf[1024];
    sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "such as a POST without a Content-Lengrh\r\n");
    send(client, buf, sizeof(buf), 0);
}
int get_line(int sock, char *buf, int size)
{
    int i = 0;//buf中保存读到的字符的起始下标
    char c = '\0';//-用以保存读取到的每个字符
    int n; 
    while((i < size *1) && (c != '\n'))
    {
        //每次读入一个字符，保存在c中
        n = recv(sock, &c, 1, 0);
        if(n > 0)
        {
            if(c == '\r')
            {
                //MSG_PEEK允许我们查看已经可读的数据，并且不在recv返回后丢弃这些数据
                //如果读到‘\r’,有些系统是以“\r\n”为换行，有些以“\r”为换行
                //这里通过查看下一个字符是不是‘\n’来处理“\r\n”的情况
                n = recv(sock, &c, 1, MSG_PEEK);
                if((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i] = c;//还没读到行尾，则将读到的字符存入buf
            i++;//更新起始下标
        }
        else //下面语句会导致循环终止
            c = '\n';
    }
    buf[i] = '\0';
    return i;
}
void excute_cgi(int client, const char *path, const char *method, const char *query_string)
{
    char buf[1024];
    int cgi_output[2];
    int cgi_input[2];
    pid_t pid;
    int status;
    int i;
    char c;
    int numchars = 1;
    int content_length = -1;

    buf[0] = 'A'; buf[1] = '\0';
    if(strcasecmp(method, "GET") == 0)
        while((numchars > 0) && strcmp("\n", buf))
            numchars = get_line(client, buf, sizeof(buf));
    else if(strcasecmp(method, "POST") == 0)//POST
    {
        numchars = get_line(client, buf, sizeof(buf));
        while((numchars > 0) && strcmp("\n", buf))
        {
            buf[15] = '\0';
            if(strcasecmp(buf, "Content-Length:") == 0)
                content_length = atoi(&buf[16]);
                numchars = get_line(client, buf, sizeof(buf)); 
        }
        if(content_length == -1)
        {
            bad_request(client);
            return;
        }
    }
    else //HEAD or other
    {
    }

    if(pipe(cgi_input) < 0) //先建立管道得到关于cgi_input的一对文件描述符
    {
        cannot_execute(client);
        return;
    }
    if(pipe(cgi_output) < 0)
    {
        cannot_execute(client);
        return;
    }
    if(pid = fork() < 0)
    {
        cannot_execute(client);
        return;
    }
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    send(client,buf,strlen(buf), 0);
    if(pid == 0)//子进程：CGI
    {
        char meth_env[255];
        char query_env[255];
        char length_env[255];

        dup2(cgi_output[1], STDOUT);
        dup2(cgi_input[0], STDIN);
        close(cgi_output[0]);
        close(cgi_input[1]);
        sprintf(meth_env, "REQUEST_METHOD=%s", method);
        putenv(meth_env);//用于改变或增加环境变量
        if(strcasecmp(method, "GET") == 0)
        {
            sprintf(query_env, "CONTENT_STRING=%s",query_string);
            putenv(query_env);
        }
        else //POST
        {
            sprintf(length_env, "CONTENT_LENGTH=%d",content_length);
            putenv(length_env);
        }
        execl(path, NULL);
        exit(0);
    }
    else //parent
    {
        close(cgi_output[1]);
        close(cgi_input[0]);
        if(strcasecmp(method, "POST") == 0)
            for(i = 0; i < content_length; i++)//包体写入cgi_input[1]
            {
                recv(client, &c, 1, 0);
                write(cgi_input[1], &c, 1);
            }
        while(read(cgi_output[0], &c, 1) >0)
        {
            send(client, &c, 1, 0);
        }
        close(cgi_input[1]);
        close(cgi_input[0]);
        waitpid(pid, &sttus, 0);
    }
}
void cat(int client, FILE* resource)
{
    char buf[1024];

    fgets(buf, sizeof(buf), resource);
    while(!feof(resource))
    {
        send(client, buf, strlen(buf), 0);
        fgets(buf, sizeof(buf), resource);
    }
}
void headers(int client, const char *filename);
{
    char buf[1024];
    (void)filename; //可以用filename来确定文件类型 ？？？？？？？？这步是用来干什么的啊？？？

    strcpy(buf, "HTTP/1.0 200 OK\r\n");
    send(client, buf, strlen(buf), 0);
    strcpy(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client,buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
} 
void server_file(int client, const char *filename)
{
    FILE *resource = NULL;
    int numchars = 1;
    char buf[1024];

    buf[0] = 'A'; buf[1] = '\0';
    while((numchars > 0) && strcmp("\n", buf)) //读取并丢弃
        numbers = get_line(client, buf, sizeof(buf));
    resource = fopen(filename, "r");
    if(resource == NULL)
        not_found(client);
    else
    {
        headers(client, filename);
        cat(client, resource);
    }
    fclose(resource);
}

void not_found(int client)
{
    char buf[1024];
    sprintf(buf,"HTTP/1.0 404 NOT fOUND\r\n ");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "SERVER_STRING");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf("\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf("is unavaliable or nonexistent.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);   
}
void unimplemented(int client)
{
    char buf[1024];
    sprintf(buf,"HTTP/1.0 501 Method Not Implemented\r\n ");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "SERVER_STRING");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf("\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><p>HTTP request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}
void accept_request(void *arg)
{
    int client = (intptr_t)arg; //传给线程的参数是已连接套接字描述符
    char buf[1024];
    size_t numchars; //读取到的字节数据
    char method[255]; //方法
    char url[255]; //地址
    char path[512]; //路径
    size_t i,j;
    struct stat st;
    int cgi = 0; //判断是否接入CGI程序，接入为0 //becomes true if server decides this is a CGI program
    char *query_string = NULL;

    //从已连接套接字描述符读取一行数据
    numchars = get_line(client, buf, sizeof(buf));
    i = 0; j = 0; //i用于遍历method、url、path数组，j用于遍历buf
    
    //从buf中抽取方法数据，保存到method中
    while(!ISspace(buf[i]) && (i<sizeof(method) -1))
    {
        method[i] = buf[i];
        i++;
    }
    j = i;
    method[i] = '\0';

    //strcasecmp:忽略大小写的字符串比较
    //如果既不是GET方法，也不是POST方法，调用unimplemented函数处理
    if(strcasecmp(method, "GET") && strcasecmp(method, "POST"))
    {
        unimplemented(client); 
        return;
    }
    //如果是POST方法，将cgi设置为1
    if(strcasecmp(method, "POST") == 0)
        cgi = 1;
    i = 0;
    //跳过方法数据后的空格
    while(ISspace(buf[j]) && (j < numchars))
        j++;
    //从buf中抽取url数据
    while(!ISspace(buf[j]) && (i<sizeof(url)-1) && (j < numchars))
    {
        url[i] = buf[j];
        i++; j++;
    }
    url[i]='\0';

    //如果method是GET，那么需要在获取url后处理
    if(strcasecmp(method, "GET") == 0)
    {
        query_string = url;
        //下面的处理主要是判断url中有没有包含‘？’，如果包含了‘？’，需要将cgi设置为1
        //然后将url从‘？’处截断，并使query_string指向‘？’之后
        while((*query_string != '?') && (*query_string != '\0'))
            query_string++;
        if(*query_string == '?')
        {
            cgi = 1;
            *query_string = '\0';
            query_string++;
        }
    }

    //path:"htdocs"+url
    sprintf(path, "htdos%s", url);
    //如果url末尾为‘/’,表示是个目录，那么更新path：“htdocs”+url+index.html"
    if(path[strlen(path)-1] == '/')
        strcat(path, "index.html");
    //获取文件的状态，保存到st中
    //????????????????????????????????/????????????????????????????????????????????????    
    if(stat(path, &st) == -1) //如果文件状态获取失败
    {//读取客户html请求剩余的数据，然后调用not_found客户端返回文件不存在错误
        while((numchars > 0) && strcmp("\n",buf)) //读取并放弃头
            numchars = get_line(client, buf, sizeof(buf));
        not_found(client);
    }
    else//如果文件存在
    {
        //如果文件是个目录，那么path：”htdos“+url+“、index.html”
        if((st.st_mode & S_IFMT) == S_IFDIR)
            strcat(path, "/index.html");
            //具有可执行权限cgi=1是什么意思？？？？？？？？？？？？？？？？？？？？
        if((st.st_mod & S_IXUSR) || (st.st_mod & S_IXGRP) || (st.st_mod & S_IXOTH))
            cgi = 1;
        //如果没有设置cgi，那么调用server_file进行响应
        //如果设置了cgi，那么调用execute_cgi进行响应
        if(!cgi)
            server_file(client, path);
        else
            execute_cgi(client, path, method, query_string);    
    }
    //处理完客户端的HTML请求之后，关闭已连接套接字描述符（关闭TCP连接）
    close(client);
}

int startup(u_short *port)
{
    int httpd = 0;           //服务器监听套接字文件描述符
    int on =1;               //设置监听套接字的套接字选项时，作为参数传入，表示开启
    struct sockaddr_in name; //ipv4套接字地址结构

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if(httpd = -1)
        err_die("socket");
    //初始化、设置套接字地址结构
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;              //IPV4协议
    name.sin_port = htons(*port);           //传入的4000号 端口 将主机字节序转换为网络字节序
    name.sin_addr.s_addr htonl(INADDR_ANY); //通配地址

    //setsockopt函数 设置套接字性质
    //SO_REUSERADDR　允许重用本地地址和端口
    if( (setsockopt(httped, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) <0)
    {
        err_die("setsockopt failed");
    }

    //调用bind将监听套接字描述符与地址绑定
    if(bind(httpd,(struct sockaddr *)&name, sizoeof(name)) <0)
    {
        err_die("bind");
    }

    //如果传入的端口号为0，说明希望内核分配一个，因此调用getsocjname获取内核
    //分配的地址信息，进一步获取分配的端口号
    if(*port == 0)
    {
        socklen_t namelen = sizeof(name);
        if(getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            err_die("getsockname");
        *port = ntohs(name.sin_port); //获取内核分配的端口号，网络字节序转主机字节序
    }
    
    //调用listen进行监听，backlog参数为5，即已完成和未完成队列的连接总数是5
    if(listen(httpd,5) <0)
        err_die("listen");
    return(httpd);
}
 
int main(int argc, char const *argv[])
{
    int server_sock = -1; //服务器监听套接字描述符
    u_short port = 4000; //服务器默认监听端口号
    int client_sock = -1; //已连接套接字描述符
    struct sockaddr_in client_name; //已连接套接字地质结构
    socket_t client_name_len = sizeof(client_name);
    pthread_t newthread; //线程ID

    //根据Port创建监听套接字描述符，绑定到相应地址进行监听，得到监听描述符
    server_sock = startup(&port);
    printf("httpd running on port %d\n",port);
    while(1)
    {
        //阻塞于accept，接收来自客户端的连接请求
        client_sock = accept(server_sock, (struct sockaddr *)*client_name, &client_name_len);
        if(client_sock == -1)
            err_die("accept");
        //创建线程处理来自客户端的请求
        if(pthread_create(&newthread, NULL, (void *)accept_request, (void *)(intptr_t)client_sock) != 0)
            perror("pthread_create");
    }
    return 0;
}
