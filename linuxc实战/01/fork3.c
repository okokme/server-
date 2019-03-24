#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>
int main()
{
    pid_t pid;
//    signal(SIGCHLD, SIG_IGN);
    printf("before fork pid:%d\n",getpid());
    int abc = 10;
    pid = fork();
    if(pid == -1)
    {
        perror("title");
        return -1;
    }
    if(pid > 0)
    {
        abc++;
        printf("parent: pid:%d", getpid());
        printf("abc: %d\n", abc);
        sleep(20);//父进程20秒不收尸，让子进程先死
    }
    else if(pid == 0)
    {
        abc++;
        printf("child:%d, parent:%d\n",getpid(), getppid());
        printf("abc: %d\n",abc);
        //sleep(100);
    }
    printf("fork after..");
    return 0;
}

