#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/wait.h>

int main()
{/*
    if(fork() == 0) {
        execl("/home/k/server-/zlib/minizip", "-o", "-9", "target.zip", "a.txt", "b.txt", NULL);
    }
       // execl("/bin/ls", "ls", "-al", "/etc/", NULL);
    wait(NULL);
    printf("hhhhhhhhhh000i\n");
  */
      
    if(fork() == 0) {
        execl("/home/k/server-/zlib/miniunz", "-x", "target.zip", NULL);
    }
    wait(NULL);
    printf("okkokok\n");
    return 0;
    
}

