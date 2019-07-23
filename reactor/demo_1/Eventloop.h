#pragma

#include "Noncopyable.h"
#include <thread>
class Eventloop : Noncopyable {
public:
    Eventloop();
    ~Eventloop();
    void Loop();
    void assertInLoopThread() //检查当前线程是否已经创建了其他EventLoop对象
    {
        if(!isInLoopThread())
        abortNotInLoopThread();
    }
    bool isInLoopThread() const { return threadId_ == std::this_thread::get_id();  }
private:
    void abortNotInLoopThread();
    bool looping_; /*atomic*/
    const pid_t threadId_;
};
