#include "buffer.h"
#include "Channel.h"
#include "Eventloop.h"
#include <iostream>

// class Channel;
// class Coder {
// public:

// private:


// };    

void onMessage(std::shared_ptr<Channel> chl, Buffer & buf_)
{
    std::cout<<"onMessage"<<std::endl;
    std::cout<<buf_.c_str()<<std::endl;
    
}
    void connection( Channel &firstSend ){
        firstSend.sendmssage();
    }