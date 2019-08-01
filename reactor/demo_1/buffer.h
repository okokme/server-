#pragma once

#include <vector>
#include <bits/types.h>
#include <sys/uio.h>
#include <algorithm>


class Buffer {
public:
    Buffer(): buf_(INIT_SIZE) { } //先给缓冲区赋初值，给一个足够大的缓冲区
    static const size_t INIT_SIZE = 1024;
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

private:
    std::vector<char> buf_;
    size_t readindex_ = 0;
    size_t writeindex_ = 0;
};