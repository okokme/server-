// //哲学家就餐问题
// // #include <pthread.h>
// // #include <sys/time.h>
// // #include <stdio.h>

// // #define MAX 5
// // #define UNUSED 0
// // #define USED 1
// // int GnChopstick[5] = {0}; //the number of the chopstick

// // pthread_mutex_t mutex[5]; //five mutex
// // pthread_t GpThread[5]; // five thread


// /*POSIX下线程控制的实验程序残缺*/
// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <ctype.h>
// #include <pthread.h>

// #define MAX_THREAD 3 //线程的个数
// unsigned long long main_counter, counter[MAX_THREAD];
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
// //unsigned long long是比long long还长的整数
// void* thread_worker(void*);

// int main(int argc, char const *argv[])
// {
//     int i, rtn, ch;
//     pthread_t pthread_id[MAX_THREAD] = {0}; //存放线程ID
//     for(i=0; i<MAX_THREAD; i++){
//     /*在这里填写代码，用pthread_create建一个普通的线程，线程ID存入pthread_id[i].
//     线程执行函数是thread_worker 并且 i作为参数传递给线程    
//     */
//         pthread_create(&pthread_id[i],NULL,thread_worker, &i);

//    }
//     do{/*用户按一次回车执行下面的循环体一次，按q退出*/
//         pthread_mutex_lock(&mutex);
//         unsigned long long sum = 0;
//         /*求所有的线程的counter之和*/
//         for(i=0; i<MAX_THREAD; i++) /*求所有counter之和*/
//         {
//             sum += counter[i];
//             printf("%llu", counter[i]);
//         }
//         pthread_mutex_unlock(&mutex);
//         printf("%llu/%llu",main_counter, sum);
//     }while(ch = getchar() != 'q');
//     pthread_mutex_destroy(&mutex);
//     return 0;
// }
// void* thread_worker(void* p)//传入i
// {
//     int thread_num;
//     /*在这里填写代码，把main中的i的值传递给thread_num*/
//     thread_num = *((int*)p);
//     for(;;) /*无限循环*/
//     {
//         pthread_mutex_lock(&mutex);
//         counter[thread_num]++; /*本线程的counter+1*/
//         main_counter++;/*主counter+1*/
//         pthread_mutex_unlock(&mutex);
//     }
// }
// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <ctype.h>
// #include <pthread.h>
// #define MAX_THREAD 3 /* 线程的个数 */
// unsigned long long main_counter, counter[MAX_THREAD];
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// /* unsigned long long是比long还长的整数 */
// void* thread_worker(void*);
// int main(int argc, char* argv[])
// {
// int i, rtn, ch;
// int abc[MAX_THREAD] = {0,1,2};
// pthread_t pthread_id[MAX_THREAD] = {0}; /* 存放线程id*/
// for (i=0; i<MAX_THREAD; i++)
// {
// /* 在这里填写代码，用pthread_create建一个普通的线程，
// 线程id存入pthread_id[i]，线程执行函数是thread_worker
// 并i作为参数传递给线程 */
// //pthread_create(&pthread_id[i],NULL,thread_worker,&abc[i]); //这里
// pthread_create(&pthread_id[i],NULL,thread_worker,&i);

// }
// do {/* 用户按一次回车执行下面的循环体一次。按q退出 */
// unsigned long long sum = 0;
// /* 求所有线程的counter的和 */
// for (i=0; i<MAX_THREAD; i++)
// {/* 求所有counter的和 */
// sum += counter[i];
// printf("%llu\n ", counter[i]);
// }
// printf("%llu/%llu\n", main_counter, sum);
// } while ((ch = getchar()) != 'q');
// return 0;
// }
// void* thread_worker(void* p)
// {
// int thread_num;
// /* 在这里填写代码，把main中的i的值传递给thread_num */
// thread_num = *((int*)p);
// printf("%d\n",thread_num);
// for(;;)
// {
// /* 无限循环 */
// pthread_mutex_lock(&mutex);
// counter[thread_num]++; /* 本线程的counter加一 */
// main_counter++; /* 主counter 加一 */
// pthread_mutex_unlock(&mutex);
// }
// }

//#include <iostream>
#include <stdio.h>
#include <pthread.h>
 
using namespace std;
 
#define NUM_THREADS 10
 
void* say_hello(void* args)
{
    int i = *((int*)args);//对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取；
    cout << "hello in " << i << endl;
}
 
int main()
{
    pthread_t tids[NUM_THREADS];
    cout << "hello in main..." << endl;
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        int ret = pthread_create(&tids[i], NULL, say_hello, (void *)&i);//传入的时候必须强制转换为void* 类型，即无类型指针
        cout << "Current pthread id =" << tids[i] << endl;//这里学会使用tids数组打印创建的进程id信息；
        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
 
    pthread_exit(NULL);
}