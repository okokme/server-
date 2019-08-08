### 项目介绍

本项目是使用C++编写的基于事件驱动模型的Web Server. 目前支持静态GET请求以及CGI请求. 以及部分HTTP/1.1特性.

### 使用方法

* 编译：`cd src/net/build/`  `make`

* 服务器运行：`./muduo`

* 打开浏览器输入：`localhost：8888`

### 特点

* 可以解析返回html、css、js、mp3、mp4、jpg、png等文件。

* 使用c++11部分特性（`std::function` `shared_ptd`...）

* 基于事件驱动模型

* Reactor风格
