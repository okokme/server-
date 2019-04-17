#include <iostream>
#include <unistd.h>
int main()
{int n=sleep(100);
while(n)
{
if(errno == EINTR)
printf("is einter\n");
n = sleep(n);
}
    std::cout << "Hello world" << std::endl;
    return 0;
}

