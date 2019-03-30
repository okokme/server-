#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define N 100
#define true 1
#define producerNum  10
#define consumerNum  10
#define sleepTime 10

typedef int semaphore;
typedef int item;
item buffer[N] = {0};
int in = 0;
int out = 0;
int proCount = 0;
semaphore mutex = 1, empty = N, full = 0, proCmutex = 1;

void * producer(void * a){
    while(true){
        while(proCmutex <= 0);
        proCmutex--;
        proCount++;
        printf("生产一个产品ID%d, 缓冲区位置为%d\n",proCount,in);
        proCmutex++;

        while(empty <= 0){
            printf("缓冲区已满！\n");
        }
        empty--;

        while(mutex <= 0);
        mutex--;

        buffer[in] = proCount;
        in = (in + 1) % N;

        mutex++;
        full++;
        sleep(sleepTime);
    }
}

void * consumer(void *b){
    while(true){
        while(full <= 0){
            printf("缓冲区为空！\n");
        }
        full--;

        while(mutex <= 0);
        mutex--;

        int nextc = buffer[out];
        buffer[out] = 0;//消费完将缓冲区设置为0

        out = (out + 1) % N;

        mutex++;
        empty++;

        printf("\t\t\t\t消费一个产品ID%d,缓冲区位置为%d\n", nextc,out);
        sleep(sleepTime);
    }
}

int main()
{
    pthread_t threadPool[producerNum+consumerNum];
    int i;
    for(i = 0; i < producerNum; i++){
        pthread_t temp;
        if(pthread_create(&temp, NULL, producer, NULL) == -1){
            printf("ERROR, fail to create producer%d\n", i);
            exit(1);
        }
        threadPool[i] = temp;
    }//创建生产者进程放入线程池


    for(i = 0; i < consumerNum; i++){
        pthread_t temp;
        if(pthread_create(&temp, NULL, consumer, NULL) == -1){
            printf("ERROR, fail to create consumer%d\n", i);
            exit(1);
        }
        threadPool[i+producerNum] = temp;
    }//创建消费者进程放入线程池


    void * result;
    for(i = 0; i < producerNum+consumerNum; i++){
        if(pthread_join(threadPool[i], &result) == -1){
            printf("fail to recollect\n");
            exit(1);
        }
    }//运行线程池
    //pthread_join()函数，以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。如果线程已经结束，那么该函数pthread_join()函数，以阻塞的方式等待thread指定的线程结束。当函数返回时，被等待线程的资源被收回。如果线程已经结束，那么该函数会立即返回。并且thread指定的线程必须是joinable的。会立即返回。并且thread指定的线程必须是joinable的。
    //参数 ：thread: 线程标识符，即线程ID，标识唯一线程。retval: 用户定义的指针，用来存储被等待线程的返回值
    return 0;
}