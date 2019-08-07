#pragma once

#include <vector>
#include <bits/types.h>
#include <sys/uio.h>
#include <algorithm>
#include <iostream>


class Buffer {
public:
    static const size_t INIT_SIZE = 2048;
    Buffer(): buf_(INIT_SIZE) { } //先给缓冲区赋初值，给一个足够大的缓冲区
    static const char crlf[];
    char *begin() { return &*buf_.begin(); }
    char *peek() { return begin() + readindex_; }
    size_t prependable() { return readindex_; }
    size_t readable() { return writeindex_ - readindex_; }
    size_t writeable() { return buf_.capacity() - writeindex_; }

    
    //将data追加到buffer中
    void append(const char*data, size_t len)
    {
        makeSpace(len);
        buf_.insert(buf_.begin()+writeindex_, data, data+len );
        writeindex_ += len;
    }
    void retrieve(int len)
    {
        if(len < readable())
            readindex_ += len;
        else 
            readindex_ = writeindex_ =0;
    }
    void retrieveAll() { retrieve( readable() ); }

    //内部腾挪
    void makeSpace(size_t len)
    {
        //没有足够的腾挪空间
        if(writeable() + prependable() < len)
        {
            buf_.resize(writeindex_+len);
        }
        //有足够的腾挪空间
        else if(len < writeable() )
        {
            size_t readn = readable();
            std::copy(peek(), peek()+readn, begin());
            readindex_ = 0;
            writeindex_ = readindex_ + readn;
        }
    }
    void swap(Buffer& buffer_)
    {
        buf_.swap(buffer_.buf_);
        std::swap(readindex_, buffer_.readindex_);
        std::swap(writeindex_, buffer_.writeindex_);
    }
    int readfd(int fd);
    //返回c风格字符串
    char *c_str()
    {
        append("\0", 1);
        writeindex_--;
        return peek();
    }
    //返回\r\n\r\n在buffer中第一次出现的位置，没出现返回-1
    int findCrlf()
    {
        const char *crlf_ = std::search(peek(), begin()+writeindex_, crlf, crlf+4 );
        return crlf_ == (begin() + writeindex_) ? -1 : crlf_ - peek(); 
    }

private:
    std::vector<char> buf_;
    size_t readindex_ = 0;
    size_t writeindex_ = 0;
};