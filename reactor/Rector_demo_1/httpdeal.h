#include "buffer.h"
#include "Channel.h"
#include "Eventloop.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <string.h>
// class Channel;
// class Coder {
// public:

// private:


// };    

    void onMessage(std::shared_ptr<Channel> chl, Buffer& buf_)
    {
        std::cout<<"onMessage"<<std::endl;
        std::cout<<buf_.c_str()<<std::endl;
        // const char* s = "non-blocking网络编程中，在Tcp这种字节流协议上做应用层分包是网络编程的基本需求。（muduo p194） 什么叫分包？ 分包指的是在发送一个消息或一帧数据时，通过一定的处理，让接收方能从字节流中识别并截取（还原）出一个个消息。 为什么需要打包和分包？ 因为tcp一次发送的数据可能不足一个完整的消息，或者包含多个消息。tcp一次发送数据的大小与内核中发送缓冲区的大小有关，如果当前发送缓冲区空余空间很小，那么可能一次就发送不了一个完整的消息；也有可能内核经过优化把两次send的数据仅合并成一次发送，这样对方收到的数据就会包含多个消息。所以我们在发送数据时需要在一条消息数据中再多添加一些额外信息让接受端可以正确识别一个个消息。 常用的打包方式有哪些？ 对于短连接的tcp服务，分包不是一个问题，只要发送方主动关闭连接，就表示一个消息发送完毕，接收方read返回0，从而知道消息的结尾。 对于长连接的tcp服务，打包有四种方法： 1） 消息长度固定 2） 使用特殊的字符或者字符串作为消息的边界。例如http协议的headers以\r\n为字段的分隔符 3） 在每条消息的头部加一个字段长度 4） 利用消息本身的格式来分包，例如xml中 的配对，或者json格式中的{…}的配对。解析这种消息格式通常会用到状态机。 muduo的打包分包基本原理： 1）当发送端发送一个结构体时，首先使用protobuf进行序列化，然后计算序列化数据的长度，然后使用“长度+序列化数据”的打包方式发送给接收端，接收端接收到数据后对数据进行分包，首先读取数据长度，然后根据长度读取序列化数据，并对数据进行反序列化得到完整的消息结构。 （2）当发送端只发送一个简单的字符串时，可以使用“字符串长度+字符串数据”这种简单的打包方式，打包后的数据存放到muduo::net::Buffer，然后发送出去。接收的数据同样存放在muduo::net。 实现长度分包的代码： muduo实现长度分包的代码由类LengthHeaderCodec 实现。代码位于https://github.com/chenshuo/muduo/blob/master/examples/asio/chat/codec.h LengthHeaderCodec实现发送功能的代码
        // write(chl->fd(), s, strlen(s));
        // buf_.retrieve(strlen(s));
    }
    void connection( Channel &firstSend ){
        firstSend.sendmssage();
    }


