//运行示例： ./comp 1.txt 123
//(123是密码)
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

//编译加 -lssl -lcrypto

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>


int main(int argc, char* argv[])
{                                                                            
    if(fork() == 0) {
        execl("/home/k/server-/zlib/minizip", "-o", "-9","-p",argv[2] ,"target.zip", argv[1], NULL);
    }
    wait(NULL);
    //子进程压缩加密结束
    
    //当前目录下生成了一个target.zip文件
    //发送target.zip 
    //然后把target.zip删掉
    return 0;
}
