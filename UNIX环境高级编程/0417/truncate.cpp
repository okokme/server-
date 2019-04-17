#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int fd;
  fd = open("/home/k/server-/UNIX环境高级编程/0417/c.txt", O_RDWR|O_CREAT, S_IRUSR|S_IXUSR|S_IWUSR);
   ftruncate(fd, 1048576);
   close(fd);
    
    //truncate("/home/k/server-/UNIX环境高级编程/0417/c.txt", 10);
    std::cout << "Hello world" << std::endl;
    return 0;
}

