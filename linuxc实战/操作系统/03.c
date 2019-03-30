//多进程模型缺点：创建进程过程会带来一定开销（频繁的上下文切换）；数据交换需要IPC技术
//上下文切换：如果运行进程A后要切换到运行进程B，就应将A的相关信息移出内存，并读入B的相关信息
//多线程模型优点：上下文切换不需要切换数据区和堆，可以利用数据区和堆交换数据
#include <stdio.h>
#include <pthread.h>
 
void * thread_summation(void *arg);
int sum=0;
 
int main(void)
{
  pthread_t id_t1, id_t2;	//线程ID
  int range1[]={1, 5};
  int range2[]={6, 10};
  
  //创建线程
  pthread_create(&id_t1, NULL, thread_summation, (void*)range1);
  pthread_create(&id_t2, NULL, thread_summation, (void*)range2);
  //等待线程终止
  pthread_join(id_t1, NULL);
  pthread_join(id_t2, NULL);
  
  printf("result: %d \n", sum);
  return 0;
}
 
void* thread_summation(void* arg)
{
  int start=((int *)arg)[0];
  int end=((int *)arg)[1];
  
  while(start<=end)
  {
    sum+=start;	//此处存在临界区相关问题
    start++;
  }
  return NULL;
}
