cmake_minimum_required(VERSION 2.8)

project(muduo)
add_executable(${PROJECT_NAME} "Channel.cc" "httpdeal.h" "Acceptor.cc" "Acceptor.h" "TcpServer.cc" "TcpServer.h" "Eventloop.cc" "Socket.cc" "buffer.cc" "Channel.h" "Epoll.cc" "Eventloop.h" "Socket.h" "buffer.h" "httpdeal.cc" "Epoll.h" "Noncopyable.h" "test1.cc")

set(CMAKE_CXX_FLAGS "-g -std=c++11 -lpthread")
