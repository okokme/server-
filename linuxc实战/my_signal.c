#include<stdio.h>
#include<signal.h>

/*信号处理函数*/
/*ctrl+c发送信号SIGINT，按 Ctrl+\ 发送信号SIGQUIT退出*/
void handler_sigint(int signo)
{
	printf("recv SIGINT\n");
}
int main()
{
	/*安装信号处理函数*/
	signal(SIGINT,handler_sigint); //在main函数中，只要一接收到第一个参数的信号，就立刻执行第二个参数的函数。一劳永逸式安装信号处理函数，以后运行中一直起作用。
	while(1)
		;
	return 0;
}
