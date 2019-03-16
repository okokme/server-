#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
/*自定义错误处理函数*/
void my_err(char *err_string, int line)
{
	fprintf(stderr, "line: %d  ",line);
	perror("err_string");
	exit(1);
}
