#include <iostream>
using namespace std;
//int main()
//{//3.如果多线程模型中,一个线程有异常,比如1/0,这时候这个程序会怎么样?
// 如果是发信号,是哪个线程发送的信如果出现这种情况,应该怎么处理?
 void bbb(int t)                                                                    
{
    cout << "float err" << endl;
    pthread_cancel(pthread_self());
    sleep(2);
}
int main()
{
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
    }                                                                              
    std::cout << "Hello world" << std::endl;
    return 0;
}
    std::cout << "Hello world" << std::endl;
    return 0;
}

