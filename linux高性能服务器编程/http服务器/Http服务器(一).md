# Http服务器(一)





问：Http协议的职责是什么？

答：生成针对目标web服务器的Http请求报文；

​	对Web服务器请求的内容的处理。

（听起来挺像废话的..就是客户端向服务器发出的第一步 和 服务器接收最后一步，一种固定格式请求和对应的解析处理。“请给我http://baidu.com/xss/的资源”  ... “原来是想要这台计算机上的/xss/资源啊”）

---



问：URL是什么？

答：URL地址(俗称网址)，是同一资源定位符。分为带参数和不带参数的。

GET方法使用的是带参数的URL，即传递的参数会使用？连接在资源路径后边；

POST方法使用的是不带参数的URL，它的参数是通过Http请求报头中的请求消息体传递给服务器的。

URI 用字符串标识某一互联网资源

---



问：Http协议的格式是什么？

答：如下

```
GET 或 POST 请求的url路径（一般是去掉域名的路径） HTTP协议版本号
字段1名： 字段1值\r\n
字段2名： 字段2值\r\n
...
字段n名： 字段n值\r\n
\r\n
http协议包体内容
```

Http协议由两部分组成：包头和包体 

包头和包体之间使用一个\r\n分割。 由于Http协议包头的每一行都是\r\n结尾，所以Http协议包头一般以\r\n\r\n结束。

Http协议包体不是必需的，GET方法一般没有包体。POST方法有包体。

---



问：GET方法和POST方法有没有使用的特地情景？

答：有。

**GET：获取资源。**

GET 方法用来请求访问已被 URI 识别的资源。 指定的资源经服务器端解析后返回响应内容。

也就是说， 如果请求的资源是文本， 那就保持原样返回； 如果是像 CGI（ Common Gateway Interface， 通用网关接口） 那样的程序， 则返回经过执行后的输出结果。

(主要用于访问页面资源)

![1548691581305](/tmp/1548691581305.png)

**POST:传输实体主体**

POST 方法用来传输实体的主体。
虽然用 GET 方法也可以传输实体的主体， 但一般不用 GET 方法进行传输， 而是用 POST 方法。 

注：虽说 POST 的功能与 GET 很相似， 但POST的主要目的并不是获取响应的主体内容。

![1548691806419](/tmp/1548691806419.png)



---



# 一、请求协议

## 举个栗子

比如我们在浏览器中请求<http://www.hootina.org/index_2013.php>这个网址，这是一个典型的GET方法，浏览器组装的http数据包格式如下：

```
GET /index_2013.php HTTP/1.1\r\n
Host: www.hootina .org\r\n
Connection: keep-alive\r\n
Upgrade-Insecure-Requests: 1\r\n
User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36\r\n
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n
Accept-Encoding: gzip, deflate\r\n
Accept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\n
\r\n
```

>**Host**：域名
>
>Host表示请求的服务器网址；



>**Connection：keep-alive** 是HTTP/1.1的特性，为了保证tcp持久连接。
>
>持久连接的特点是，只要任意一端没有明确提出断开连接，则保持TCP连接状态。
>
>​			旨在建立一次TCP连接后进行多次请求和相应的交互。



>**Upgrade-Insecure-Request:1**
>
>告诉服务器，自己支持这种操作，也就是我能读懂你服务器发过来的上面这条信息，并且在以后发请求的时候不用http而用https



>**User-Agent**: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36
>
>用于浏览器识别，可以看出你的系统版本，浏览器，浏览器内核等
>
>使用的代理是Mozilla/5.0



>**Accept**: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,\*/*;q=0.8\r\n
>
>表示浏览器支持的MIME类型。
>
>告诉服务器当前客户端可以支持的文档类型，这里包含了\*/*表示什么都可以接收（优先级不同）
>
>**Text**：用于标准化地表示的文本信息，文本消息可以是多种字符集和或者多种格式的
>
>**text/html**:表示html文档
>
>**Application**：用于传输应用数据或者二进制数据
>
>**application/xhtml+xml**表示 xhtml 文档；
>
>**application/xml**表示 xml 文档。
>
> 



>**Accept-Encoding: gzip, deflate**
>
>表示浏览器支持的编码是gzip和deflate（**客户端支持的编码**）
>
>**Accept-Encoding**：表示浏览器有能力解码的编码类型
>
>**gzip**： GNU zip 的缩写，它是一个 GNU 自由软件的文件压缩程序，也经常用来表示 gzip 这种文件格式。
>
>**deflate**：同时使用了LZ77与哈弗曼编码的一个无损数据压缩算法



>**Accept-Language: zh-CN,zh;q=0.9,en;q=0.8**
>
>浏览器支持的语言分别是简体中文和中文（**当前客户端可以支持的语言**）
>
>**Accept-Language**表示浏览器所支持的语言类型；
>
>**zh-cn**表示简体中文；
>
>**zh** 表示中文；



## 另一栗子

若是POST请求，与GET请求的区别和用法上文已说明，它的特别在于有包体

```
POST /HttpDemo/index.jsp HTTP/1.1
Host: 127.0.0.1:8080
Connection: keep-alive
Content-Length: 28
Cache-Control: max-age=0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Origin: http://127.0.0.1:8080
User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.125 Safari/537.36
Content-Type: application/x-www-form-urlencoded
Referer: http://127.0.0.1:8080/HttpDemo/index.jsp
Accept-Encoding: gzip,deflate,sdch
Accept-Language: zh-CN,zh;q=0.8
Cookie: JSESSIONID=57C3302F3350676F65B5E4409ABA87CF

```

>**Referer**: http://127.0.0.1:8080/HttpDemo/index.jsp：请求来自哪个页面，例如在百度上点击链接到了这里，那么Referer:http://www.baidu.com;
>
>如果你是在浏览器的地址栏里输入，那么就没有这个Referer请求头了
>
>防盗链使用这个特性很好用！
>
>

*Referer请求头是比较有用的一个请求头，它可以用来做统计工作，也可以用来做防盗链。*
*统计工作：我公司网站在百度上做了广告，但不知道在百度上做广告对我们网站的访问量是否有影响，那么可以对每个请求中的Referer进行分析，如果Referer为百度的很多，那么说明用户都是通过百度找到我们公司网站的。* 

*防盗链：我公司网站上有一个下载链接，而其他网站盗链了这个地址，例如在我网站上的index.html页面中有一个链接，点击即可下载JDK7.0，但有某个人的微博中盗链了这个资源，它也有一个链接指向我们网站的JDK7.0，也就是说登录它的微博，点击链接就可以从我网站上下载JDK7.0，这导致我们网站的广告没有看，但下载的却是我网站的资源。这时可以使用Referer进行防盗链，在资源被下载之前，我们对Referer进行判断，如果请求来自本网站，那么允许下载，如果非本网站，先跳转到本网站看广告，然后再允许下载。*

觉得这一段很通俗易懂，来自：https://blog.csdn.net/chao_xun/article/details/39611087

>**Content-Length**: 28：请求体的长度，这里表示28个字节



>**userName=min&password=111217**：请求题内容，hello是在表单中输入的数据。userName，password是表单字段的名字，=后面是输入的数据，多个字段中间使用&连接



# 响应协议

例如：

在浏览器中请求https://www.cnblogs.com/balloonwj/p/9093578.html这个网址

服务器向客户端返回的报文

```

HTTP/1.1 200 OK\r\n
Content-Type: text/html\r\n 用于定义用户的浏览器或相关设备如何显示将要加载的数据，或者如何处理将要加载的数据。
Content-Length:42\r\n
\r\n

```

问：什么是状态码？ 什么时候会用到状态码？

答：**HTTP状态码**（英语：HTTP Status Code）是用以表示网页服务器超文本传输协议响应状态的3位数字代码。上例的200 OK就是。

最常用的见下：

* 200 OK

  请求已成功，请求所希望的响应头或数据体将随此响应返回。出现此状态码是表示正常状态。

* 400 Bad Request

  1、语义有误，当前请求无法被服务器理解。除非进行修改，否则客户端不应该重复提交这个请求。

  2、请求参数有误。

* 404 Not Found

  请求失败，请求所希望得到的资源未被在服务器上发现。没有信息能够告诉用户这个状况到底是暂时的还是永久的。假如服务器知道情况的话，应当使用410状态码来告知旧资源因为某些内部的配置机制问题，已经永久的不可用，而且没有任何可以跳转的地址。404这个状态码被广泛应用于当服务器不想揭示到底为何请求被拒绝或者没有其他适合的响应可用的情况下。出现这个错误的最有可能的原因是服务器端没有这个页面。

* 500 Internal Server Error

  服务器遇到了一个未曾预料的状况，导致了它无法完成对请求的处理。一般来说，这个问题都会在服务器端的源代码出现错误时出现。

* 501 Not Implemented

服务器不支持当前请求所需要的某个功能。当服务器无法识别请求的方法，并且无法支持其对任何资源的请求。





**关闭与浏览器的连接，就是完成了一次HTTP请求与回应，因为HTTP是无连接的。**