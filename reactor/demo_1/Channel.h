#pragma once
#include "Noncopyable.h"
#include <iostream>
#include <functional>

class Eventloop;

class Channel:Noncopyable {
public:
    typedef std::function<void()> EventCallback;
    Channel(Eventloop* loop, int fd);
};