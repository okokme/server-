#include "Channel.h"
#include "Eventloop.h"
#include <memory>
#include <string.h>
#include <poll.h>
#include <errno.h>

Channel::Channel(Eventloop* loop, int fd, int event):loop_(loop),fd_(fd),events_(event) { }
int Channel::SENDING = 001;
void Channel::changeEvent() { loop_->changeevent(fd(), get_events());}

void Channel::handleEvent()
{
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        printf("EPOLLHUP !EPOLLIN\n");
        if (errorCallback_) errorCallback_();
        return;
    }
    if (revents_ & (EPOLLERR | POLLNVAL)) {
        printf("EPOLLERR \n");
        if (errorCallback_) errorCallback_();
        return;
    }
    if(revents_ & EPOLLIN)
    {
        std::cout<<"handleEvent EPOLLIN fd = "<<fd()<<std::endl;
        if(readCallback_) //如果setreadCallback后 readCallback为真，否则为假不执行下面语句
            readCallback_(); //读事件由用户自己负责 因为bind参数不同，有不同触发的readcb 一个是listenfd的readcb 一个是读事件的readcb 
      return;
    }
    if(revents_ & EPOLLOUT)
    {
        std::cout<<"handleEvent EPOLLOUT fd = "<<fd()<<std::endl;
   //     handleWrite(); //send后有剩余数据需要写道缓冲区 才会触发handlewrite //写事件由loop自动负责
    }
}
    
void Channel::handleRead() {
    ssize_t n = input_.readfd(fd());
    std::cout << "handleRead() fd = " << fd() << ", read: " << input_.c_str() << "\n";
         //    input_.retrieveAll();
            //const char *s = "jfskldjfaslkfjsadklf sdlf,s alfdjsl fajdf lskfj slafjsald fjsldf s";
            //write(fd(), s, strlen(s));
            //return;
    if(n > 0)
    {
        if(messageCallback_){
             messageCallback_(shared_from_this(), input_); //之前的bug出在setmessagecallback使用了引用
             ////这里有问题 不会改 只容许在先前共享的对象，即 std::shared_ptr 所管理的对象上调用 shared_from_this 。（特别是不能在构造 *this 期间 shared_from_this 。）
        }
       
    }
    else if(n == 0)
    {
        //std::cout << "hand close" << std::endl;
        handleClose();
    }        
    else
    {
        handleError();
    }
 //   input_.retrieveAll();
}

void Channel::handleClose()
{
    // if(status_ == Channel::SENDING) //如果正在发送消息 把缓冲区中消息全发完 
    // {
    //     setWriteCompleteCallback( std::bind(&Eventloop::delChannel, loop_, shared_from_this()) );//, this
    // }
    // else
    {
        loop_->delChannel(shared_from_this());
    }
}
void Channel::handleError()
{
    handleClose();
}

int Channel::sendmssage()
{
    char buf[1024];
    std::cout<<"on send message"<<std::endl;
    const char*s = "hello my name is huhu\n";
    write(fd_, s, strlen(s));
}
