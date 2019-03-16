1.服务端程序(名为listen)接收3个参数：IP地址、端口号和`backlog`值。我们在服务器上运行：

`./listen 127.0.0.1 8888 5`

2.客户端程序(名为connect)接收3个参数：IP地址、端口和count连接数。我们在Linux另外一个终端上运行（建立9个连接）：

`./connect localhost 8888 9`

3.通过netstat命令查看listen监听队列内容

`$netstat -nt|grep 8888`

```
tcp        0      0 127.0.0.1:8888          127.0.0.1:53928         ESTABLISHED
tcp        0      0 127.0.0.1:8888          127.0.0.1:53922         ESTABLISHED
tcp        0      0 127.0.0.1:8888          127.0.0.1:53924         ESTABLISHED
tcp        0      0 127.0.0.1:8888          127.0.0.1:53918         ESTABLISHED
tcp        0      0 127.0.0.1:8888          127.0.0.1:53920         ESTABLISHED
tcp        0      0 127.0.0.1:8888          127.0.0.1:53926         ESTABLISHED
```

