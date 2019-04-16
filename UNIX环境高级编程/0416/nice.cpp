#include <iostream>
#include <sys/resource.h>
#include <unistd.h>
int main()
{
    time_t t1, t2, t3;
    time(&t1);
    int i = 0;
    int num = 10000;
    pid_t pid = fork();

    if(pid == 0)
    {
        int nice = getpriority(PRIO_PROCESS, 0);
        printf("child nice = %d\n", nice);
        for(i; i<num; --i)   ;
        time(&t2);
        printf("child pay %ld sec\n", t2-t1 );
    }
    if(pid >0 )
    {
        setpriority(PRIO_PROCESS, 0, 19);
        int nice = getpriority(PRIO_PROCESS, 0);
        printf("parent nice = %d\n", nice);
        for(i; i<num; --i)   ;
        time(&t3);
        printf("parent pay %ld sec\n", t3-t1 );

    }


    std::cout << "Hello world" << std::endl;
    return 0;
}

