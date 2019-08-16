//运行时输入 ./decomp 123
//(123是密码)
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    if(fork() == 0) {
        execl("/home/k/server-/zlib/miniunz", "-x", "-p", argv[1], "target.zip", NULL);
    }
    wait(NULL);
    //子进程解压结束
    //解压后删掉target.zip 只留下解压后的1.txt
    printf("okkokok\n");
    return 0;
}
