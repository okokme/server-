/*#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM 10
 
pthread_mutex_t mutex;
 
pthread_cond_t conda;
pthread_cond_t condb;
pthread_cond_t condc;
 
int floga = 0;
int flogb = 0;
int flogc = 0;
 
void *thread_a(void *argv)
{
	int i = 0;
	char *p;
	p = (char *)argv;
	//printf("%s",p);
	while(i < NUM)
	{
		pthread_mutex_lock(&mutex);
		floga = 1;
		pthread_cond_wait(&conda,&mutex);
		floga = 0;
		//pthread_mutex_unlock(&mutex);
		printf("%s",p);
		while(!flogb)
		{
		    pthread_mutex_unlock(&mutex);
			sleep(10);
		    pthread_mutex_lock(&mutex);
		}
		pthread_cond_signal(&condb);
		pthread_mutex_unlock(&mutex);
		i++;
	}
	floga = 1;
}
 
void *thread_b(void *argv)
{
	int i;
	char *p;
	p = (char *)argv;
	//printf("%s",p);
	while(i < NUM)
	{
		pthread_mutex_lock(&mutex);
		flogb = 1;
		pthread_cond_wait(&condb,&mutex);
		flogb = 0;
		//pthread_mutex_unlock(&mutex);
 
		printf("%s",p);
		while(!flogc)
		{
			pthread_mutex_unlock(&mutex);
			sleep(10);
			pthread_mutex_lock(&mutex);
		}
		pthread_cond_signal(&condc);
		pthread_mutex_unlock(&mutex);
		i++;
	}
 
}
 
void *thread_c(void *argv)
{
	int i;
	char *p;
	p = (char *)argv;
	//printf("%s",p);
	while(i < NUM)
	{
		pthread_mutex_lock(&mutex);
		flogc = 1;
		pthread_cond_wait(&condc,&mutex);
		flogc = 0;
		//pthread_mutex_unlock(&mutex);
 
		printf("%s",p);
		while(!floga)
		{
			pthread_mutex_unlock(&mutex);
			sleep(10);
			pthread_mutex_lock(&mutex);
		}
		pthread_cond_signal(&conda);
		pthread_mutex_unlock(&mutex);
		i++;
	}
}
 
int main()
{
	pthread_t A;
	pthread_t B;
	pthread_t C;
	int ret;
	char *pa = "A";
	char *pb = "B";
	char *pc = "C";
 
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&conda,NULL);
	pthread_cond_init(&condb,NULL);
	pthread_cond_init(&condc,NULL);
 
	ret = pthread_create(&A,NULL,thread_a,(void *)pa);
	if(ret == -1)
	{
		printf("pthread_create a error!\n");
		exit(-1);
	}
	ret = pthread_create(&B,NULL,thread_b,(void *)pb);
	if(ret == -1)
	{
		printf("pthread_create a error!\n");
		exit(-1);
	}
	ret = pthread_create(&C,NULL,thread_c,(void *)pc);
	if(ret == -1)
	{
		printf("pthread_create a error!\n");
		exit(-1);
	}
	sleep(2);
	pthread_cond_signal(&conda);
 
	pthread_join(A,NULL);
	//printf("\nfinished A!\n");
	pthread_join(B,NULL);
	//printf("\nfinished B!\n");
	pthread_join(C,NULL);
	//printf("\nfinished C!\n");
	printf("\nfinished!\n");
 
    return 0;
}
*/
/*
#include <stdio.h>   
#include <stdlib.h>   
#include <pthread.h>    
#include <unistd.h>   
#include <string.h>    

#define NUM 3  

int n=0;  
pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;                     //互斥锁
pthread_cond_t qready=PTHREAD_COND_INITIALIZER;                     //条件变量 


void * thread_func(void *arg)  
{
 int param=(int*)arg;  
 char c='A'+param;  
 int ret,i=0;  
 for (; i < 10; i++)  
 {
  pthread_mutex_lock(&mylock);  
  while (param != n)                                  //刚运行时，n = 0， param = 0,条件不成立，所以直接打印A  ；然后是B和C
  {   
   ret = pthread_cond_wait(&qready, &mylock);  
  } 

  printf("%c ",c);                       //打印A、B、C 
  n=(n+1)%NUM;                        //n变成了1、然后是2、3、4
  pthread_mutex_unlock(&mylock);  
  pthread_cond_broadcast(&qready);  
 }      
 return (void *)0;  
} 

int main(int argc, char** argv) {


 int i;
 int err;  
 pthread_t tid[NUM];  
 void *tret;  
 for(i = 0 ; i < NUM; i++)  
 {

  err=pthread_create(&tid[i],NULL,thread_func,(void *)i);  
  if(err != 0)  
  {

   printf("thread_create error:%s\n",strerror(err));  
   exit(-1);  
  }  
 }  
 for (i = 0; i < NUM; i++)  
 {

  err = pthread_join(tid[i], &tret);  
  if (err != 0)  
  {

   printf("can not join with thread %d:%s\n", i,strerror(err));  
   exit(-1);  
  }  
 }  
 printf("\n");  
 return 0;  
}  */
   
   
#include<stdio.h>  
#include<errno.h>  
#include<string.h>  
#include<stdlib.h>  
#include<pthread.h>  
#include<unistd.h>
  
#define PRINTTIME 10  
/*互斥锁 MUTEX*/  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  
/*条件变量*/  
pthread_cond_t condA_B = PTHREAD_COND_INITIALIZER;  
pthread_cond_t condB_C = PTHREAD_COND_INITIALIZER;  
pthread_cond_t condC_A = PTHREAD_COND_INITIALIZER;  
  
int flagA = 0,flagB = 0,flagC = 0;  
  
void *th_A_C(void *arg){  
  
    printf("A come!\n");  
    int i = 0;  
    char *name = (char *)arg;  
    while(i < PRINTTIME){  
        pthread_mutex_lock(&mutex);  
        printf("A LOCKED\n");  
  
        flagA = 1;  
        /*等待C的信号*/  
        pthread_cond_wait(&condC_A,&mutex);  
        flagA = 0;  
        printf("%c:%d-->%lx\n",*name,i,pthread_self());  
        /*发信号给B*/  
        /*在发信号给B之前，先检测B有没有在等待*/  
        /*若B在等待，在这里就可以检测到标志位flagB == 1*/  
        while(!flagB){  
  
            pthread_mutex_unlock(&mutex);  
            usleep(30);  
                      printf("--------------------------wait flagB\n");  
            pthread_mutex_lock(&mutex);  
  
        }/*循环结束表示flagBC为1，就是B已经加锁，并在等待A给它信号，所以现在A发信号给B*/  
  
              printf("signal A--->B finished!\n");  
        pthread_cond_signal(&condA_B);        
        pthread_mutex_unlock(&mutex);  
              printf("%c UNLOCK!\n",*name);  
        i++;  
        usleep(20);  
    }  
    /*A的循环结束的时候把自己的flagA 位置为1，欺骗C线程 让C线程以为A这边准备好了，然后发信号给他。这样可以避免C判断A没有再等带它的标志一直死循环状态退不出来*/  
    flagA = 1;  
}  
  
  
  
void *th_B_A(void *arg){  
  
    printf("B come!\n");  
    int i = 0;  
    char *name = (char *)arg;  
    while(i < PRINTTIME){  
  
        pthread_mutex_lock(&mutex);  
              printf("B LOCKED\n");  
        /*B抢到锁，设置标志位flagBC = 1*/  
        flagB = 1;  
        /*等待A的信号*/  
        pthread_cond_wait(&condA_B,&mutex);  
        flagB = 0;  
        printf("%c:%d-->%lx\n",*name,i,pthread_self());  
        /*发信号给C*/  
        /*在发信号给C之前先检测C有没有在等待*/  
        /*若C在等待则flagC == 1*/  
        while(!flagC){  
  
            pthread_mutex_unlock(&mutex);  
            usleep(30);  
                      printf("--------------------------wait flagC\n");  
            pthread_mutex_lock(&mutex);  
        }  
  
        /*循环结束表示flagC 已经为1 ,所以开始给C发信号*/  
              printf("signal B--->C finished!\n");  
        pthread_cond_signal(&condB_C);        
        pthread_mutex_unlock(&mutex);  
              printf("%c UNLOCK!\n",*name);  
  
        i++;  
        usleep(20);  
    }  
}  
  
  
  
void *th_C_B(void *arg){  
  
    printf("C come!\n");  
    int i = 0;  
    char *name = (char *)arg;  
    while(i < PRINTTIME){  
  
        pthread_mutex_lock(&mutex);  
              printf("C LOCKED\n");  
        flagC = 1;  
        /*等待B的信号*/  
        pthread_cond_wait(&condB_C,&mutex);  
        flagC = 0;  
        printf("%c:%d-->%lx\n",*name,i,pthread_self());  
        /*发信号给A*/  
        /*发信号给A 之前先检测A有没有在等待，若在等待 则flagA == 1*/  
  
        while(!flagA){  
  
            pthread_mutex_unlock(&mutex);  
            usleep(30);  
                      printf("--------------------------wait flagA\n");  
            pthread_mutex_lock(&mutex);  
        }  
        /*循环结束表示A在等待，所以发信号给A*/  
  
              printf("signal C--->A finished!\n");  
        pthread_cond_signal(&condC_A);        
        pthread_mutex_unlock(&mutex);  
              printf("%c UNLOCK!\n",*name);  
  
        i++;  
        usleep(20);  
    }  
}  
  
int main(void){  
  
    pthread_t th1,th2,th3;  
  
    char name1 = 'A',name2 = 'B',name3 = 'C';  
  
    int *p1 =(int *) &name1;  
    int *p2 =(int *) &name2;  
    int *p3 =(int *) &name3;  
  
    if(pthread_create(&th1,NULL,th_A_C,(void *)p1) < 0){  
  
        fprintf(stderr,"pthread_create th1 %s\n",strerror(errno));  
        exit(1);  
    }  
    usleep(30);  
    if(pthread_create(&th2,NULL,th_B_A,(void *)p2) < 0){  
  
        fprintf(stderr,"pthread_create th2 %s\n",strerror(errno));  
        exit(1);  
    }  
    usleep(30);  
    if(pthread_create(&th3,NULL,th_C_B,(void *)p3) < 0){  
  
        fprintf(stderr,"pthread_create th1 %s\n",strerror(errno));  
        exit(1);  
    }  
  
    //起始给线程A发通知，防止A,b,c,死锁  
    /*直接通知A，不能内个让他再傻等*/  
  
    pthread_cond_broadcast(&condC_A);  
  
  
    pthread_join(th1,NULL);  
    printf("th1 finished!\n");  
    pthread_join(th2,NULL);  
    printf("th2 finished!\n");  
    pthread_join(th3,NULL);  
    printf("th3 finished!\n");  
  
    return 0;  
}  