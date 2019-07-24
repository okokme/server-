#include <iostream>
#include "Eventloop.h"
#include "Channel.h"
#include "Epoll.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    Epoller poller;
    printf("main():pid = %d\n",getpid());
    Eventloop loop(&poller);
    loop.Loop();
    return 0;
}
