编译： make

清除.o文件： make clean

服务器运行：./server 8888

打开浏览器输入：localhost：8888



基于epoll和线程池实现的小型webserver，支持GET、POST方法。

可以解析返回html、css、js、mp3、mp4、jpg、png等文件。

使用c++编写。

---

记录过程：一进来先注册socket事件完成三次握手，建立线程池

* 线程池内部开始运转，在构造函数中开始创建线程并调用类的工作函数使队列没有任务状态下的线程等待），主线程进行设置表单事件，进入轮播循环等待客户端连接，若是新连接，在表单中注册事件，若是已有连接，查看任务（当为有数据写事件入时，new一个对象建立任务Task（将该事件中的客户端fd和多路复用只中的socket文件描述符写入改Task进行初始化），并将这个任务加入线程池中（线程池中接收到任务将任务加入任务队列，并唤醒一个工作线程，工作线程将任务从队列中取出进行执行task->doit任务

* * task内部运转recv接受客户端发来的消息到缓冲区，将接收来的内容打印出来，利用sscanf函数将开头的三个字段取出 分别是方法，网址，协议

    如打印出来其中之一是：`recv: method=GET uri=/1.mp3 version=HTTP/1.1` 

    * 如果是GET方法，将请求的uri和长度start放入get_post函数去继续执行：

      将uri进行引用成为string类型，并初始化同类型filename与从第一个以后的字符开始（目的是如果访问资源为了将/去掉）

      如接收到的`GET /picture/hehe.jpg HTTP/1.1 recv: method=GET uri=/picture/hehe.jpg version=HTTP/1.1 filename:picture/hehe.jpg5close `

      如果是第一次访问默认uri为/或者访问index.html页面，调用send_file将要发送的网页以及类型标识进行封装统一发送。		

    ```c
    send_file( "index.html", "text/html", start ); 
    ```

    ​	如果调用uri.find(".后缀")查找其他资源标识并找到的情况下，调用send_file封装发送

    ```
    send_file( filename, "image/jpg", start ); 
    ```

    

    * 如果是POST方法，将请求的uri和buf继续放到post_get函数执行：

      还是同样像GET方法中开始的那样将uri文件的/去掉成string类型。

      如果在uri中找到调用CGI程序的标识，继续从buf中获取请求长度，获取参数，用tmp存储参数发送到CGI服务器，fork产生子进程，执行CGI服务器计算；

      ```c++
      if( fork() == 0 ) {             execl( filename.c_str(), tmp, NULL ); }
      ```

      否则sendfile404

  其他，构造发送的头部，向客户端发送没有501错误

  调用send_file函数发送报文及打开服务器相关资源

  ```c
  int Task::send_file( const string & filename, const char *type,int start, const int num, const char *info )
  ```

  * send_file内部实现：获取文件名，通过文件名获取文件信息，若打开失败或没有该文件（获取失败），发送给客户端404提示报文，并打开404文件。

    若获取成功，发送成功报文，并打开该文件。

，执行结束delete task，该线程继续沉睡，直到下一次唤醒（signal或brodecast）

---

附一个GET报文和一个POST报文以作参考

GET的buf接收的是这种

`GET /1.png HTTP/1.1 Host: localhost:8888 Connection: keep-alive User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36 Accept: image/webp,image/apng,image/*,*/*;q=0.8 Referer: http://localhost:8888/submit.html Accept-Encoding: gzip, deflate, br Accept-Language: zh-CN,zh;q=0.9 Cookie: _ga=GA1.1.1296320880.1547386986  `

POST的buf接收的是这样 

`POST /CGI/adder HTTP/1.1 Host: localhost:8888 Connection: keep-alive Content-Length: 7 Cache-Control: max-age=0 Origin: http://localhost:8888 Upgrade-Insecure-Requests: 1 Content-Type: application/x-www-form-urlencoded User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36 Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8 Referer: http://localhost:8888/submit.html Accept-Encoding: gzip, deflate, br Accept-Language: zh-CN,zh;q=0.9 Cookie: _ga=GA1.1.1296320880.1547386986  a=1&b=3  `