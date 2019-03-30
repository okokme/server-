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
	printf("befor fork pid:%d \n", getpid());
	int a = 10;
    int ret = 0;

	pid = vfork(); //errno
	if (pid == -1)	
	{
		perror("pid<0 err\n");
		return -1;
	}
	if (pid > 0)
	{
		printf("parent: pid:%d \n", getpid());
	}
	else if (pid == 0)
	{//子进程注意，要么拉起来一个应用，要么结束必须 不然会出现coredump
		printf("child: %d, parent: %d \n", getpid(), getppid());
        //exit(0);
//int  execve  (const  char  *filename, char *const argv [], char *constenvp[]);
//把自己写的程序启动起来
//        int ret = execve("./hello",NULL, NULL );
        char *const argv[] = {"ls", "-l", NULL};
        int ret = execve("bin/ls",argv, NULL);       
        if(ret == -1)
        {
            perror("execve");
        }
        printf("execve 测试有没有执行");
		exit(0);//这里的exit酌情写上，若是到别的应用中，且别的应用中写了exit，那么此处可以不用写exit
				//否则必须写上exit，这就是vfork的不好之处
    }

	printf("fork after....\n");
	return 0;
}


// int main(void )
// {
// 	pid_t pid;
// 	int ret = 0;
	
// 	printf("befor fork pid:%d \n", getpid());
// 	int abc = 10;
// 	pid = vfork(); //errno
// 	if (pid == -1)	
// 	{
// 		//printf("pid < 0 err.\n");
// 		perror("tile");
// 		return -1;
// 	}
// 	if (pid > 0)
// 	{
// 		printf("parent: pid:%d \n", getpid());
	
// 	}
// 	else if (pid == 0)
// 	{
// 		printf("child: %d, parent: %d \n", getpid(), getppid());
// 		//printf("abc:%d\n", abc);
		
// 		//把自己写应用程序启动起来
// 		//通过一个应用程序执行命令
// 		char *const argv[] = {"ls", "-l", NULL};
// 	   	ret =  execve("/bin/ls", argv, NULL);
// 	   	if (ret == -1)
// 		{
// 			perror("execve:");
// 		}
// 	    printf("execve 测试有没有执行\n");
			
// 			exit(0);
// 		}

// 	//printf("fork after....\n");
// 	return 0;
// }


