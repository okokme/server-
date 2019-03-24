#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	printf("begin");
	pid = fork();
	switch(pid)
	{
		case 0: printf("child process is running. curpid is %d, parentpid is %d\n",pid, getppid());
		       	break;
		case -1: printf("process created error\n ");
			 break;
		default: printf("partnt process is running, childpid is %d, parentpid is %d\n", pid, getpid());
			 break;
	}
}
