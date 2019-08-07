#include "Channel.h"
#include "Eventloop.h"
#include <memory>
#include <string.h>
#include <poll.h>
#include <errno.h>

Channel::Channel(Eventloop* loop, int fd, int event):loop_(loop),fd_(fd),events_(event),input_(),output_() { }
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
    //        std::cout<<getReadCallback()<<std::endl;
            readCallback_(); //读事件由用户自己负责 因为bind参数不同，有不同触发的readcb 一个是listenfd的readcb 一个是读事件的readcb 
      return;
    }
    if(revents_ & EPOLLOUT)
    {
        std::cout<<"handleEvent EPOLLOUT fd = "<<fd()<<std::endl;
        handleWrite(); //send后有剩余数据需要写道缓冲区 才会触发handlewrite //写事件由loop自动负责
    }
}
    
void Channel::handleRead() 
{
    input_.retrieveAll();
    std::cout<<"***********first in not read *************"<<std::endl;
    std::cout<<input_.c_str()<<std::endl;
    std::cout<<"******************************************"<<std::endl;
    
    ssize_t n = input_.readfd(fd());
    std::cout << "handleRead() fd = " << fd() << "\n";
    std::cout << "readable = " << input_.readable() << "\n";
    std::cout << "read: " << input_.c_str() << "\n";
    if(n > 0)
    {
        if(messageCallback_){
             messageCallback_(shared_from_this(), input_); //之前的bug出在setmessagecallback使用了引用
             ////这里有问题 不会改 只容许在先前共享的对象，即 std::shared_ptr 所管理的对象上调用 shared_from_this 。（特别是不能在构造 *this 期间 shared_from_this 。）
        }
       
    }
    else if(n == 0)
    {
        handleClose();
    }        
    else
    {
        handleError();
    }
}
void Channel::handleWrite()
{
    std::cout<<output_.c_str()<<std::endl;
    if(isWriting())
    {
        ssize_t n = write(fd(), output_.peek(), output_.readable());
        if( n>=0 )
        {
            output_.retrieve(n);
            if(output_.readable()  == 0) 
            {
                clearStatus(Channel::SENDING);
                disableWrite();
                if(writeCompleteCallback_)
                    writeCompleteCallback_;
            }
        }
        else 
        {
            if(errno == EPIPE || (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR))//EPIPE对端已经关闭连接
            {
                handleClose();
            }
        }
    }
}

void Channel::handleClose()
{
    if(status_ == Channel::SENDING) //并不立即调用delChannel 如果正在发送消息（state = Channel::SENDING） 把缓冲区中消息全发完 再执行delChannel关
    {
        setWriteCompleteCallback( std::bind(&Eventloop::delChannel, loop_, shared_from_this()) ); 
    }
    else
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

int Channel::send(const char*s, size_t len) 
{
    setStatus(Channel::SENDING);
    if(! (isWriting() && (output_.readable() == 0)) )
    {
        ssize_t n = write(fd(), s, len); //发不完才会存到output_ buffer中
        if(n>0) //n<len剩下的没发完的放在缓冲区  n=len 成功发完了 取消  ②本来是可以成功发完的，但是消息正在发送 结果有handleclose触发 那么先等发送完毕后再关
        {
            if(n<len)
            {
                output_.append(s+n, len-n);
                enableWrite();
            }
            else //  等消息发完后 如果要关闭 执行delchannel 不关闭的话清除SENDING状态
            {
                clearStatus(Channel::SENDING);
                if(writeCompleteCallback_)
                    writeCompleteCallback_;  
                    //这里应该把缓冲区的消息全发完
            }
        }
        else
        {
            if(errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) 
                handleClose();
        }
    }
    else
        output_.append(s, len);
}

