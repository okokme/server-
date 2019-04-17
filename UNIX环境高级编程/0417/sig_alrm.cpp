#include <iostream>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
static void 
my_alarm(int signo)
{
    struct passwd* rootptr;
    printf("in signal handle\n");
    if( (rootptr = getpwnam("root")) == NULL)
        printf("getpwnam(root) error\n");
    alarm(1);
}
int main()
{
    struct passwd* ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for(; ;)
    {
        if((ptr = getpwnam("str")) == NULL)
            printf("getpwnam err\n");
        if(strcmp(ptr->pw_name, "str") != 0)
            printf("retrun value corrupted!, pw_name = %s\n", ptr->pw_name);
    }

    std::cout << "Hello world" << std::endl;
    return 0;
}

