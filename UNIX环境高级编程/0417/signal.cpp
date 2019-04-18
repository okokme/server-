#include <iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

int main()
{

    pid_t = 0;
    struct sigaction act;
    act.sa_sigaction = catch_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    //注册SIGINT信号
    sigation(SIGINT, &act, NULL);
    sigation(SIGRTMIN, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);
    pid = fork();
    if(pid == 0)
        int i = 0; ret = 0;
    union sigval v1;
    union sigval v2;
    for (i = 0; i < 3; i++)
    {
        v1.sival_int = 201 + i;
        ret = sigqueue(getppid(), SIGINT, v1);
        if(ret ! = 0)
            printf("SIGINT err\n");
        else
            printf("SIGINT success\n");
    }
    for( i = 0; i < 3; i++)
    {
        v2.sival_int = 301 + i;
        ret = sigqueue(getppid(), SIGRTMIN, v2);
        if(ret ! = 0)
             printf("SIGTMIN err\n");
         else
             printf("SIGTMIN success\n");
    }


    std::cout << "Hello world" << std::endl;
    return 0;
}

