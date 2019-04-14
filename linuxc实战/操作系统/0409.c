#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#define MAX_THREAD 3 /* 线程的个数 */
unsigned long long main_counter, counter[MAX_THREAD];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* unsigned long long是比long还长的整数 */
void* thread_worker(void*);
int main(int argc, char* argv[])
{
int i, rtn, ch;
int abc[MAX_THREAD] = {0,1,2};
pthread_t pthread_id[MAX_THREAD] = {0}; /* 存放线程id*/
for (i=0; i<MAX_THREAD; i++)
{
// 在这里填写代码，用pthread_create建一个普通的线程，
//线程id存入pthread_id[i]，线程执行函数是thread_worker
//并i作为参数传递给线程 */
//pthread_create(&pthread_id[i],NULL,thread_worker,&abc[i]); //这里
pthread_create(&pthread_id[i],NULL,thread_worker,(int *)i);

}
sleep(1000);
do {/* 用户按一次回车执行下面的循环体一次。按q退出 */
unsigned long long sum = 0;
/* 求所有线程的counter的和 */
for (i=0; i<MAX_THREAD; i++)
{/* 求所有counter的和 */
sum += counter[i];
printf("%llu\n ", counter[i]);
}
printf("%llu/%llu\n", main_counter, sum);
} while ((ch = getchar()) != 'q');
return 0;
}
void* thread_worker(void* p)
{
int thread_num = (int )p;
/* 在这里填写代码，把main中的i的值传递给thread_num */
printf("%d\n",thread_num);
for(;;)
{

    printf("%d\n",thread_num);
    sleep(1);
/* 无限循环 */
//pthread_mutex_lock(&mutex);

//counter[thread_num]++; /* 本线程的counter加一 */
//main_counter++; /* 主counter 加一 */
//pthread_mutex_unlock(&mutex);

}
}
