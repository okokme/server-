#include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <signal.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <assert.h>
  #include <stdio.h>
  #include <string.h>

  static bool stop = false;
  /*SIGTERM 信号的处理函数，触发时结束主进程中的循环*/
  static void handle_term(int sig)
  {
      stop = true;
  }

  int main(int argc, char* argv[])
  {
      signal(SIGTERM, handle_term);

      if(argc <= 3)
      {
          printf("usage: %s ip_address port_number count\n", basename(argv[0]));
          return 1;
      }
      const char* ip = argv[1];
      int port = atoi(argv[2]);
      int count= atoi(argv[3]);

      struct sockaddr_in server_address;
      bzero(&server_address, sizeof(server_address));
      server_address.sin_family = AF_INET;
      inet_pton(AF_INET, ip, &server_address.sin_addr);
      server_address.sin_port = htons(port);

      int sockfd[count];
      for(int i = 0; i < count; i++)
      {
          sockfd[i] = socket(AF_INET, SOCK_STREAM,0);
          assert(sockfd[i] >= 0);
          if(connect(sockfd[i],(struct sockaddr*)&server_address,sizeof(server_address)) < 0)
          {
              printf("connection failed\n");
          }
      }

      /*循环等待连接，直到有SIGTERM信号将它中断*/
      while(!stop)
      {
          sleep(1);
      }
      for(int j = 0; j < count; j++)
      {
          close(sockfd[j]);
      }

      return 0;
  }