#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void Testfunc()
{
    printf("test");
}
int main()
{
    int procnum = 10;
    int loopnum = 100;
    int i = 0;
    pid_t pid;
    printf("please enter your proname:");
    scanf("%d",&procnum);

    for(i=0; i<procnum; i++)
    {
     //   printf("loopnum1:%d\n",loopnum);
        pid = fork();
        if(pid == 0)
        { 
            for(int j=0; j<loopnum; j++)
            {
                Testfunc();
//                exit(0);//不能在这里写exit(0)会使循环无效
            }
            printf("\n");
            exit(0);
        }//调完后不让子进程参与fork就可以实现
    }
  //  wait(NULL);
    printf("hello\n");
    return 0;
}