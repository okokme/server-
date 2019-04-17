#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void *a(void *arg)
{
    printf("hhhhhhhh\n");
    pthread_exit((void *)1);
//    return ((void*)a)
}
int main()
{
    pthread_t tid;
    int p;
    void *tret;
    pthread_create(&tid, NULL, a, NULL);
    pthread_join(tid, &tret);
    printf("exit code %ld\n", (long)tret);//不能转化为int，会失去精度
    std::cout << "Hello world" << std::endl;
    return 0;
}

