#include <iostream>
#include "Eventloop.h"
#include "Channel.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>

void threadFunc()
{
    printf("main():pid = %d, tid = %d\n",getpid(),gettid());
    Eventloop loop;
    loop.Loop();

}
int main(int argc, char const *argv[])
{
    //Eventloop loop;
    printf("main():pid = %d, tid = %d\n",getpid(),gettid());
    Eventloop loop;
    std::thread thread1(threadFunc);
    thread1.join();
    loop.Loop();
    pthread_exit(NULL);
    return 0;
}
