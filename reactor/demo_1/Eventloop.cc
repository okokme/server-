#include "Eventloop.h"
__thread Eventloop* t_loopInThisThread = 0;
Eventloop::Eventloop():looping_(false)
{
   // threadId_ = gettid();
   threadId_ = std::this_thread::get_id();



}