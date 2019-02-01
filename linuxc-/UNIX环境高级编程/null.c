#include<fcntl.h>
#include"apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGhij";
int mian()
{
	int fd;
	if((fd = creat("file.hole",S_IRWXU)) <0)
	{
		my_err("create error", __LINE__);
	}
	if(write(fd, buf1, 10) != 10)
		my_err("write error", __LINE__);
	//offset now = 10;
	if(lseek(fd, 16384, SEEK_SET) == -1)
		my_err("lseek error",__LINE__);
	//offset now = 16384
	if(write(fd, buf2, 10)!= 10)
		my_err("buf2 write error",__LINE__);
	//offset noe = 16394
	
	exit(0);
	//在此乱入一句vim的操作命令， 将全文中所有errNum替换成my_err输入：%s/errNum/my_err/g

}
