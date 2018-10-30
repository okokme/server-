/*client.c*/                                                                                        
#include <sys/types.h>                                                                              
#include <sys/socket.h>                                                                             
#include <unistd.h>                                                                                 
#include <stdio.h>                                                                                  
#include <stdlib.h>                                                                                 
#include <strings.h>                                                                                
#include <string.h>                                                                                 
#include <arpa/inet.h>                                                                              
#define SERV_PORT 8000                                                                              
void perr_exit(const char *str)                                                                     
{                                                                                                   
    perror(str);                                                                                    
    exit(1);                                                                                        
}                                                                                                   
int main(int argc,char *argv[])                                                                     
{                                                                                                   
    int sfd,len;                                                                                    
    sfd = socket(AF_INET,SOCK_STREAM,0);                                                            
    char buf[256];                                                                                  
    struct sockaddr_in serv_addr;                                                                   

    bzero(&serv_addr,sizeof(serv_addr));                                                            
    //init                                                                                          
    serv_addr.sin_family = AF_INET;                                                                 
    serv_addr.sin_port = htons(SERV_PORT);                                                          
    inet_pton(AF_INET,argv[1],&serv_addr.sin_addr.s_addr);//转换char *IP地址为网络二进制序          

   if(connect(sfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)                              
       perr_exit("connect error");                                                                  
    while(fgets(buf,sizeof(buf),stdin))//读取终端输入的数据                                         
    {                                                                                               
        if(write(sfd,buf,strlen(buf)) < 0)//写入数据到服务器                                        
            perr_exit("write error");                                                               
        len = read(sfd,buf,sizeof(buf));//读取服务器传递的数据                                  
        if(len <0)                                                                             
            perr_exit("read error");
        if(len == 0)
        {
            printf("the other size closed\n");
            close(sfd);
            exit(1);
        }                                                                   
        if(write(STDOUT_FILENO,buf,len) < 0)//输出到终端                                            
            perr_exit("write error");                                                               
    }                                                                                               
    return 0;                                                                                       
}   
/*client.c*/    
            /*                                                                      
#include <sys/types.h>                                                                              
#include <sys/socket.h>                                                                             
#include <unistd.h>                                                                                 
#include <stdio.h>                                                                                  
#include <stdlib.h>                                                                                 
#include <strings.h>                                                                                
#include <string.h>                                                                                 
#include <arpa/inet.h>                                                                              
#define SERV_PORT 8000                                                                              
void perr_exit(const char *str)                                                                     
{                                                                                                   
    perror(str);                                                                                    
    exit(1);                                                                                        
}                                                                                                   
int main(int argc,char *argv[])                                                                     
{                                                                                                   
    int sfd,len;                                                                                    
    sfd = socket(AF_INET,SOCK_STREAM,0);                                                            
    char buf[256];                                                                                  
    struct sockaddr_in serv_addr;                                                                   

    bzero(&serv_addr,sizeof(serv_addr));                                                            
    //init                                                                                          
    serv_addr.sin_family = AF_INET;                                                                 
    serv_addr.sin_port = htons(SERV_PORT);                                                          
    inet_pton(AF_INET,argv[1],&serv_addr.sin_addr.s_addr);//转换char *IP地址为网络二进制序          

   if(connect(sfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)                              
       perr_exit("connect error");                                                                  
    while(fgets(buf,sizeof(buf),stdin))//读取终端输入的数据                                         
    {                                                                                               
        if(write(sfd,buf,strlen(buf)) < 0)//写入数据到服务器                                        
            perr_exit("write error");                                                               
        len = read(sfd,buf,sizeof(buf));//读取服务器传递的数据                                  
        if(len <0)                                                                                  
            perr_exit("read error");
        if(len == 0)
        {
            printf("the other size closed\n");
            close(sfd);
            exit(1);
        }                                                                    
        if(write(STDOUT_FILENO,buf,len) < 0)//输出到终端                                            
            perr_exit("write error");                                                               
    }                                                                                               
    return 0;                                                                                       
}   
*/
/*clientc*/    
            /*                                                                       
#include <sys/types.h>                                                                              
#include <sys/socket.h>                                                                             
#include <unistd.h>                                                                                 
#include <stdio.h>                                                                                  
#include <stdlib.h>                                                                                 
#include <strings.h>                                                                                
#include <string.h>                                                                                 
#include <arpa/inet.h>                                                                              
#define SERV_PORT 8000                                                                              
void perr_exit(const char *str)                                                                     
{                                                                                                   
    perror(str);                                                                                    
    exit(1);                                                                                        
}                                                                                                   
int main(int argc,char *argv[])                                                                     
{                                                                                                   
    int sfd,len;                                                                                    
    sfd = socket(AF_INET,SOCK_STREAM,0);                                                            
    char buf[256];                                                                                  
    struct sockaddr_in serv_addr;                                                                   

    bzero(&serv_addr,sizeof(serv_addr));                                                            
    //init                                                                                          
    serv_addr.sin_family = AF_INET;                                                                 
    serv_addr.sin_port = htons(SERV_PORT);                                                          
    inet_pton(AF_INET,argv[1],&serv_addr.sin_addr.s_addr);//转换char *IP地址为网络二进制序          

   if(connect(sfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)                              
       perr_exit("connect error");                                                                  
    while(fgets(buf,sizeof(buf),stdin))//读取终端输入的数据                                         
    {                                                                                               
        if(write(sfd,buf,strlen(buf)) < 0)//写入数据到服务器                                        
            perr_exit("write error");                                                               
        len = read(sfd,buf,sizeof(buf));//读取服务器传递的数据                                  
        if(len <0)                                                                                  
            perr_exit("read error");
        if(len == 0)
        {
            printf("the other size closed\n");
            close(sfd);
            exit(1);
        }                                                                    
        if(write(STDOUT_FILENO,buf,len) < 0)//输出到终端                                            
            perr_exit("write error");                                                               
    }                                                                                               
    return 0;                                                                                       
}*/  