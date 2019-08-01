#include "Channel.h"
#include "Eventloop.h"
#include <memory>
#include <string.h>
#include <poll.h>
//class Eventloop;
 
Channel::Channel(Eventloop* loop, int fd, int event):loop_(loop), fd_(fd), events_(event) { printf("in Channel::构造Channel\n");}
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
        std::cout<<"handleEvent EPOLLIN fd = "<<fd_<<std::endl;
        if(readCallback_) //如果setreadCallback后 readCallback为真，否则为假不执行下面语句
            readCallback_(); //读事件由用户自己负责 因为bind参数不同，有不同触发的readcb 一个是listenfd的readcb 一个是读事件的readcb 
      return;
    }
    if(revents_ & EPOLLOUT)
    {
        std::cout<<"handleEvent EPOLLOUT fd = "<<fd_<<std::endl;
   //     handleWrite(); //send后有剩余数据需要写道缓冲区 才会触发handlewrite //写事件由loop自动负责
    }
}
    
void Channel::handleaccept() {        //-----------------没写完
    //int  accept(int  s,  struc8ik t  sockaddr  *addr, socklen_t *addrlen);
    struct sockaddr a;  
    socklen_t len = sizeof(a);      
    int fd = ::accept(fd_, (struct sockaddr *)&a, &len);   
    //std::cout<<"accept a new fd = "<<fd<<std::endl;     
    assert(fd >0 );
    std::shared_ptr<Channel> accept_cha ( new Channel(loop_, fd, EPOLLIN | EPOLLERR));
    
    accept_cha->set_nonblock();
    accept_cha->setReadCallback( std::bind(&Channel::handleRead, accept_cha)); //std::function<void()>  ////////不知道该bind啥
    accept_cha->setMessageCallback(messageCallback_);
    accept_cha->setErrorCallback(std::bind(&Channel::handleError, accept_cha));
    
    loop_->addChannel(accept_cha);
   // loop_->get_epoller()->insert_Channel( std::make_pair(fd,accept_cha) ); //是不是可以写成loop_->addChannel();
   // loop_->get_epoller()->add(accept_cha->fd,accept_cha->get_events()); //添加新channel到epollevents中
    //接受完处理事件是应该设置回调了吗？
}

void Channel::handleRead() {
    ssize_t n = input_.readfd(fd());
    std::cout << "handleRead() fd = " << fd() << ", read: " << input_.c_str() << "\n";
            
            input_.retrieveAll();
            //const char *s = "jfskldjfaslkfjsadklf sdlf,s alfdjsl fajdf lskfj slafjsald fjsldf s";
            //write(fd(), s, strlen(s));
            //return;
    if(n > 0)
    {
        if(messageCallback_){
           
            
             messageCallback_(shared_from_this(), input_); 
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
    
  //  char buf[4096];
    
   // read(fd_, buf, sizeof(buf));
   // std::cout<<"------------"<<buf<<std::endl;
    //read
     // ssize_t read(int fd, void *buf, size_t count);
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