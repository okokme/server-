#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/times.h>
#include <iostream>

int main()
{
    struct tms time_buf_begin, time_buf_end;
    long tck = 0;
    clock_t time_head, time_end;
    tck = sysconf(_SC_CLK_TCK);//clock_t用_SC_CLK_TCK转换成秒数
    time_head = times(&time_buf_begin);
    printf("head_time is :%f\n", time_head/(double)tck);
    for(int i=0;i<100000; i++ )
        for(int j=0; j<10000; j++)
// 1.           ;
// 2.
            open("Cannon-1.txt",O_RDONLY);
    time_end = times(&time_buf_end);
    printf("end_time is :%f\n", time_end/(double)tck);
    printf("u_time is :%f\n", (time_buf_end.tms_utime-time_buf_begin.tms_utime)/(double)tck);
    printf("sys_time is :%f\n", (time_buf_end.tms_stime-time_buf_begin.tms_stime)/(double)tck);
    printf("child_u_time is :%f\n", (time_buf_end.tms_cutime-time_buf_begin.tms_cutime)/(double)tck);
    printf("child_sys_time is :%f\n", (time_buf_end.tms_cstime-time_buf_begin.tms_cstime)/(double)tck);
    std::cout << "Hello world" << std::endl;
    return 0;
}

