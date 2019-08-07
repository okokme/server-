
#pragma once
#include <iostream>
#include <exception>
#include <pthread.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

/*封装信号量*/
class Sem{
private:
    sem_t m_sem;
public:
    Sem()
    {
        if(sem_init(&m_sem,0,0) != 0)
        {
            throw std ::exception();
        }
    }
    ~Sem()
    {
        sem_destroy(&m_sem);
    }
    bool wait()//等待信号量
    {
        return sem_wait(&m_sem) == 0;        
    }
    bool post()//增加信号量
    {
        return sem_post(&m_sem) == 0;
    }
};

//互斥锁
class MutexLocker {
private:
    pthread_mutex_t m_mutex;
public:
    MutexLocker() {  //初始化
        if( pthread_mutex_init( &m_mutex, NULL ) ) {
            cout << "class mutexlocker init \n"<<endl;
            throw exception();
        }
    }

    ~MutexLocker() {
        pthread_mutex_destroy( &m_mutex );
    }

    bool mutex_lock() {
        return pthread_mutex_lock( &m_mutex ) == 0;
    }

    bool mutex_unlock() {
        return pthread_mutex_unlock( &m_mutex );
    }
};


// 条件变量 
class Cond {
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
public:
    Cond() {
        if( pthread_mutex_init( &m_mutex, NULL ) ) {
            cout<<"class Cond mutex init err\n"<<endl;            
            throw exception();
        }
        if( pthread_cond_init( &m_cond, NULL ) ) {
            pthread_cond_destroy( &m_cond );
            cout<<"class Cond cond init err\n"<<endl;            
            throw exception();
        }
    }

    ~Cond() {
        pthread_mutex_destroy( &m_mutex );
        pthread_cond_destroy( &m_cond );
    }

    //pthread_cond_wait
    //基于条件变量阻塞，无条件等待 与互斥锁配合使用,避免造成共享数据的混乱
    bool wait() {
        pthread_mutex_lock( &m_mutex );
        int ret = pthread_cond_wait( &m_cond, &m_mutex );
        pthread_mutex_unlock( &m_mutex );
        return ret == 0;
    }

    //pthread_cond_signal 
    //解除特定线程的阻塞，存在多个线程按入队顺序激活其中一个
    //唤醒等待该条件变量的某个线程
    bool signal() {
        pthread_mutex_lock(&m_mutex);   
        int ret = pthread_cond_signal(&m_cond);   
        pthread_mutex_unlock(&m_mutex);  
        return ret == 0;
//        return pthread_cond_signal( &m_cond ) == 0;
    }

    // 唤醒所有等待该条件变量的线程
    bool broadcast() {
        pthread_mutex_lock(&m_mutex);   
        int ret = pthread_cond_broadcast(&m_cond);   
        pthread_mutex_unlock(&m_mutex);  
        return ret == 0;
    //    return pthread_cond_broadcast( &m_cond ) == 0;
    }
};

