// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>

// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// #include <signal.h>
// #include <errno.h>
// #include <signal.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// int main()
// {
//     pid_t pid;
//     signal(SIGCHLD, SIG_IGN);
//     printf("before fork pid:%d\n",getpid());

//     int fd = open("./1.txt",O_RDWR);
//     if(fd = -1)
//     {
//         perror("myopen");
//     }
//     pid = fork();

//     if(pid == -1)
//     {
//         perror("title");
//         return -1;
//     }
//     if(pid > 0)
//     {
//         write(fd, "parent", 6);
//         printf("parent: pid:%d", getpid());

//         //sleep(20);//父进程20秒不收尸，让子进程先死
//     }
//     else if(pid == 0)
//     {
//         write(fd, "child", 5);
//         printf("child: pid:%d, parent pid:%d", getpid(), getppid());
//         close(fd);
//         exit(0);// 因为是两个文件描述符，子进程和父进程有各自的内存空间,所以是两个文件描述符，所以要close两次（分别在父子进程中close一次）
//         //sleep(100);
//     }
//     printf("fork after..");
//     return 0;
// }

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <signal.h>

   #include <sys/stat.h>
       #include <fcntl.h>


int main(void )
{
	pid_t pid;
	int fd; 
	signal(SIGCHLD, SIG_IGN);
	printf("befor fork pid:%d \n", getpid());
	
	/*
	RETURN VALUE
       open() and creat() return the new file descriptor, or -1 if an error occurred  (in  which  case,  errno  is  set
       appropriately).
       */

	
	fd  = open("./1.txt", O_RDWR);
	if (fd == -1)
	{
		perror("myopen");
		return -1;
	}


	pid = fork(); //errno
	if (pid == -1)	
	{
		perror("tile");
		return -1;
	}
	if (pid > 0)
	{
		printf("parent: pid:%d \n", getpid());
		//#include <unistd.h>

       //ssize_t write(int fd, const void *buf, size_t count);
		write(fd, "parent", 6);
		close(fd);
	
		//sleep(20);
	}
	else if (pid == 0)
	{

		printf("child: %d, parent: %d \n", getpid(), getppid());
		write(fd, "child", 5);
		//sleep(100);
		close(fd);
		exit(0);
	}

	printf("fork after....\n");
	return 0;
}

