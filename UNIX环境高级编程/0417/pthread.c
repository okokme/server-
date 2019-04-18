#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
//using namespace std;
//int main()
//{//3.如果多线程模型中,一个线程有异常,比如1/0,这时候这个程序会怎么样?
// 如果是发信号,是哪个线程发送的信如果出现这种情况,应该怎么处理?
// void bbb(int t)                                                                    
//void *bbb()
//{
//    cout << "float err" << endl;
//    printf("floa err\n");
//    pthread_cancel(pthread_self());
//    sleep(2);
//}
void aaa()
{signal(SIGFPE, SIG_IGN);

    int a = 1/0;
}
int main()
{
pthread_t t;
int errno;
signal(SIGFPE, SIG_IGN);
    pthread_create(&t,NULL,(void *)aaa,NULL);
 while(1)
    {
        //int t = sleep(10);
        //if(t)
        //cout << "wark up" << endl;
        
        int t = sleep(3);//t每隔3秒返回的是0 说明时间达到，返回 若有信号中断返回剩余秒数
        printf("%d\n",t);
        while(t)
        {
            if(errno = EINTR)
                printf("is eintr\n");
            t = sleep(t);
        }
        if(t) //打印不了下一句说明信号来了去处理了然后回不来了？
        printf("wark up\n");
    }                                                                              
    return 0;
}

