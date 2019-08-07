#include "buffer.h"

const size_t INIT_SIZE = 2048;
const char Buffer::crlf[] = "\r\n\r\n";
int Buffer::readfd(int fd)
{
    //std::cout<<"hhhhhh bufferreadfd"<<std::endl;
    //ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);
    struct iovec iov[2];
    char extrabuf[65535];
    ssize_t n = 0;
    size_t writen = writeable();
    iov[0].iov_base = begin() + writeindex_;
    iov[0].iov_len = writen;
    iov[1].iov_base  = extrabuf;
    iov[1].iov_len = sizeof(extrabuf);
    if((n = readv(fd, iov, 2)) > 0)
    {
        if(n <= writen)
        {
            writeindex_ += n;
        }
        else
        {
            writeindex_ += writen;
            append(extrabuf, n-writen);
        }
    }
    std::cout<<" nhuhuhuhuhuhuhu = "<< n << std::endl;
    return n; 
}