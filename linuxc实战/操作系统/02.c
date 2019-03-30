//gcc 02.c -pthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter = 1;

void thread1(void *arg)
{
        int i,val;

        for(i = 1; i <= 5; i++)
        {
                val = ++counter;//防止上下进程被干扰
                printf("1号进程：i= %d counter= %d\n", i, counter);
               // sleep(1);
                counter = val;
        }
}

void thread2(void *arg)
{
        int i, val;

        for(i = 1; i <= 5; i++)
        {
                val = ++counter;
               // sleep(1);
                printf("2号进程：i= %d counter= %d\n", i, counter);
               // sleep(1);
                counter = val;
        }
}

int main(int argc, char argv[])
{
        pthread_t id1, id2;

        pthread_create(&id1, NULL, (void *)thread1, NULL);
        pthread_create(&id2, NULL, (void *)thread2, NULL);

        pthread_join(id1, NULL);
        pthread_join(id2, NULL);

        printf("counter最终结果为：%d\n", counter);

        return 0;
}                   

// 重新编辑，改变sleep中休眠的时间，看看运行结果
// 重新编辑，把sleep语句注释掉，看看运行结果
// 为什么每次的运行结果不一样？
// 说明什么是临界资源，什么是临界区，如何避免结果的不一致，用哪一种同步机制？
