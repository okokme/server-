#include "Channel.h"

class Eventloop;
 
Channel::Channel(Eventloop* loop, int fd, int event):loop_(loop), fd_(fd), events_(event) { printf("in Channel::构造Channel\n");}

void Channel::handleEvent()
{
    printf("in Channel::handleEvent\n");
    if(revents_ == EPOLLIN)
    {
        std::cout<<"handleEvent EPOLLIN fd = "<<fd_<<std::endl;
        if(readCallback_) //如果setreadCallback后 readCallback为真，否则为假不执行下面语句
            readCallback_(); //读事件由用户自己负责 因为bind参数不同，有不同触发的readcb 一个是listenfd的readcb 一个是读事件的readcb 
        //readCallback_();
    }
    if(revents_ == EPOLLOUT)
    {
        std::cout<<"handleEvent EPOLLOUT fd = "<<fd_<<std::endl;
   //     handleWrite(); //send后有剩余数据需要写道缓冲区 才会触发handlewrite //写事件由loop自动负责
        //  writeCallback_(); 
       
    }
    if(revents_ == EPOLLERR)
    {
        std::cout<<"handleEvent EPOLLIN fd = "<<fd_<<std::endl;
        errorCallback_();        
    }
}
    
void Channel::handleaccept() {        //-----------------没写完
    //int  accept(int  s,  struc8ik t  sockaddr  *addr, socklen_t *addrlen);
    printf("in Channel::handleaccept\n");
    struct sockaddr a;  
    socklen_t len = sizeof(a);      
    int fd = ::accept(fd_, (struct sockaddr *)&a, &len);   
    std::cout<<"acceptfd = "<<fd<<std::endl;     
    assert(fd >0 );
    std::shared_ptr<Channel> accept_cha ( new Channel(loop_, fd, EPOLLIN | EPOLLERR ));
    
    accept_cha->set_nonblock();
    accept_cha->setReadCallback( std::bind(&Channel::handleRead, accept_cha)); //std::function<void()>  ////////不知道该bind啥
//    accept_cha->setMessageCallback(messageCallback_);

    loop_->addChannel(accept_cha);
   // loop_->get_epoller()->insert_Channel( std::make_pair(fd,accept_cha) ); //是不是可以写成loop_->addChannel();
   // loop_->get_epoller()->add(accept_cha->fd,accept_cha->get_events()); //添加新channel到epollevents中
    //接受完处理事件是应该设置回调了吗？
}

void Channel::handleRead() {
    printf("in Channel::handleread\n");
    char buf[4096];
    read(fd_, buf, sizeof(buf));
    std::cout<<"------------"<<buf<<std::endl;
    //read
     // ssize_t read(int fd, void *buf, size_t count);


}
