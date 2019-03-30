#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>

/* 允许建立的子进程个数最大值 */
#define MAX_CHILD_NUMBER 10 
/* 子进程睡眠时间 */
#define SLEEP_INTERVAL 2 
int proc_number=0; /* 子进程的自编号，从0开始 */
void do_something(); 

int main(int argc, char const *argv[])
{
    signal(SIGCHLD,SIG_IGN);// SIGCHLD
//子进程结束时, 父进程会收到这个信号。
//如果父进程没有处理这个信号，也没有等待(wait)子进程，子进程虽然终止，
//但是还会在内核进程表中占有表项，这时的子进程称为僵尸进程。
//这种情况我们应该避免(父进程或者忽略SIGCHILD信号，或者捕捉它，或者wait它派生的子进程，或者父进程先终止，
//这时子进程的终止自动由init进程来接管)。
    /*子进程个数*/
    int child_proc_number = MAX_CHILD_NUMBER;
    int i, ch;
    pid_t child_pid;
    pid_t pid[10] = {0}; //存放每个子进程的ID
    if(argc > 1)/*命令行参数第一个参数表示子进程个数*/
    {
        child_proc_number = atoi(argv[1]);
        child_proc_number = (child_proc_number > 10)?10:child_proc_number;
    }
    for(i=0; i<child_proc_number; i++)
    {
    /* 填写代码，建立child_proc_number个子进程要执行
     * proc_number = i; 
     * do_something(); 
     * 父进程把子进程的id保存到pid[i] */ 
        pid_t t = fork();
        if(t == -1)
        {
            perror("fork");
            return -1;
        }
        if(t == 0)
        {
            proc_number = i; //进程会复制，代码段，数据段，全局变量段，静态区，堆栈等，是另一块内存空间，所以虽然是全局变量但是值不会相互干扰
            //pid[i] = getpid();
            do_something();
        }
        if(t > 0)
        {
            pid[i] = t;            
        }
    }
    /*让用户选择杀死进程，数字表示杀死该进程，q退出*/
    while((ch = getchar()) != 'q')
    {
        if(isdigit(ch))
        {
        /*  填写代码，向pid[ch-'0']发信号SIGTERM， 
                    * 杀死该子进程 */ 
        /*If pid is positive, then signal sig is sent to the process with the ID
       specified by pid.*/
            kill(pid[ch-'0'], SIGTERM);
        }
    }
    /* 在这里填写代码，杀死本组的所有进程 */ 
    /*If  pid  equals  0,  then  sig is sent to every process in the process
       group of the calling process.*/
       kill(0, SIGTERM);
    return 0;
}
void do_something()
{
    for(;;)
    {
        printf("This is process No.%d and its pid is %d\n",proc_number,getpid());
        sleep(SLEEP_INTERVAL);/*主动阻塞两秒钟*/
    }
}