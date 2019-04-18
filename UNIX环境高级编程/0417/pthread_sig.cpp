#include <iostream>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
using namespace std;
void *aaa(void *p)
{
    cout<<"aaa come in"<<endl;
    int a = 1/0;//会发送异常信号
    cout<<"出"<<endl;
}
void bbb(int t)
{//转进来的直接是发送SIGFPE的线程，而不是主线程
//这样要想让异常线程终止直接可以在这个线程里将自己杀死
    cout<<"float err~~~~"<<endl;
    pthread_cancel(pthread_self());
    sleep(2);
}
//
int main()
{
    signal(SIGFPE,bbb);//设置捕获SIGFPE信号并将此线程转到bbb函数中
     pthread_t t;
    pthread_create(&t,NULL,aaa,NULL);
    while(1)
    {
        //int t = sleep(10);
        //if(t)
        //cout << "wark up" << endl;

        int t = sleep(3);
        if(t)
            cout << "wark up" << endl;
        cout<<"sleep3success"<<endl;
    }
    std::cout << "Hello world" << std::endl;
    return 0;
}

