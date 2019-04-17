#include <iostream>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    pid_t pid;
    if((pid = fork())== 0 )
    {
        printf("hhhh\n");
        alarm(20);
        exit;
    }
    if(pid > 0 )
        sleep(30);
    std::cout << "Hello world" << std::endl;
    return 0;
}

