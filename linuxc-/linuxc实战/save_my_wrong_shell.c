#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<ctype.h>
#include<pwd.h> //用于打印用户名
#define BUFFSIZE 64

#define normal 0        //一般的命令
#define out_redirect 1  //输出重定向
#define in_redirect 2   //输入重定向
#define have_pipe 3     //命令中有管道

void GetLoginName();
void GetHostName();
void GetDir();              //打印提示符
void get_input(char *);     //得到输入的命令
void explan_input(char*, int *, char a[][8]);//对于输入的命令进行解析
//此地注意,二维数组作为函数参数,第一维长度可以不确定,但是必须指定第二维长度,char a[][]

void do_cmd(int, char a[][8]);  //执行命令
int find_command(char *);       //查找命令中的可执行程序


int main(int argc, char **argv)
{
    char buf[BUFFSIZE];
    char arglist[10][8];
    int argcount;

    while(1)
    {
        memset(buf,0,BUFFSIZE);
        GetLoginName();
        GetHostName();
        GetDir();       //打印提示符
        fflush(stdout);

        get_input(buf); //读取用户输入
        if(strcmp(buf,"exit")==0 || strcmp(buf,"logout")==0)
            break;
        int i;
        for(i=0; i<10; i++) //初始化存放命令和参数的组
        {
            arglist[i][0] = '\0';
        }
        argcount = 0;                           //计数,命令中词汇量
        explan_input(buf,&argcount,arglist);    //解析命令
//       do_cmd(argcount,arglist);               //执行命令
    }
    return 0;
}
    

void GetLoginName()
{
    struct passwd* pass;
    pass = getpwuid(getuid());
    printf("[%s@",pass->pw_name);
}
void GetHostName()
{
    char name[128];
    gethostname(name,sizeof(name)-1);
    printf("%s",name);
}
void GetDir()
{
    char pwd[128];
    getcwd(pwd,sizeof(pwd)-1);
    int len = strlen(pwd);
    char*p = pwd+len-1;
    while(*p != '/' && len--)
    {
        p--;
    }
    p++;
    printf("%s]@",p);
}

void get_input(char *buf)
{
    fgets(buf,BUFFSIZE,stdin);
    int len; 
    len = sizeof(buf);
    if(len >= BUFFSIZE)
    {
        printf("ERROR: command is too long!\n");
        exit(-1);
    } 
    buf[len -1] = '\0'; //去除换行符

}

/*解析buf中的命令存入arglist中,命令及参数个数为argcount
ls -l arglist[0]=ls, arglist[1]=-l*/

void explan_input(char *buf, int *argcount,char arglist[][8])
{
    char *p = buf;
    ///将用户输入的整行字符拆分成一个个单词,存入二维数组的每一行中
    while(*p != '\0')
    {
        if(*p==' ') p++;
        else
        {
            char *q = p;
            int len = 0;
            while((*q!=' ') && (*q!='\0'))
            {
                q++; //尾暂存位置
                len++; //命令或参数长度
            }
            //将当前已拆解的单词存入二维数组的一行
            strncpy(arglist[*argcount],p,len+1);
            arglist[*argcount][len]='\0';
            (*argcount)++;
            p = q;//获取尾位置
        }
    }

}

void do_cmd(int argcount, char arglist[10][8])
{
    //指针数组,每个元素指向二维数组的一行
    //arg存放所有命令及参数,argnext存放管道后的命令
    char *arg[argcount+1],*argnext[argcount+1];
    int i;
    int flag = 0;
    int how = 0;//用于标识命令中是否含有 > <
    int background = 0; //用于标识指令中是否具有后台运行符&
    char *file;
    pid_t pid;

    //提取命令
    for(i=0; i<argcount; i++)
    arg[i] = arglist[i]; //指针数组,每个元素指向二维数组的一行
    arg[argcount] = NULL;

    //查看命令行是否具有后台运行符
    for(i=0; i<argcount; i++)
    {
        if(strncmp(arg[i],"&",1) == 0) //
        {
            //后台运行符必须在命令的末尾,否则格式错误
            if(i == argcount - 1)
            {
                background = 1;
                arg[argcount - 1] = NULL;
                break;
            }
            else
            {
                printf("ERROR:wrong command about background\n");
                return;
            }

        }
    }
    for(i=0; arg[i]!=NULL; i++)
    {
        if(strcmp(arg[i],">")==0)
        {
            flag++;
            how = out_redirect;
            if(arg[i+1]==NULL)//输出重定向符>在最后,没有重定向接受文件
            //arg是指针数组,指向的是二维数组的一行(一个命令或参数)下一个命令没了NULL说明在最后
            flag++;//使flag==1告知命令格式错误
        }
        if(strcmp(arg[i],"<")==0)
        {
            flag++;
            how = in_redirect;
            if(i == 0)//输入重定向符<在最前边
            flag++;
        }
        if(strcmp(arg[i],"|")==0)
        {
            flag++;
            how = have_pipe;
            if(arg[i+1]==NULL) //管道符在最后
            flag++;
            if(i==0)
            flag++;
        }
    }
    //flag>1,说明同时含有><|的两个或者以上,本程序不支持,或命令格式错误
    if(flag>1)
    {
        printf("ERROR:wrong command about>,<,|\n");
        return;
    }

    if(how == out_redirect) //命令中只含有一个输出重定向符
    {
        for(i=0; arg[i]!=NULL; i++)
        if(strcmp(arg[i],">")==0)
        {
            file = arg[i+1]; //获取输出的重定向
            arg[i]=NULL;
        }
    }

    if(how == in_redirect) //输入命令中只含有一个输入重定向符
    {
        for(i=0;arg[i]!=NULL; i++)
        if(strcmp(arg[i],"<")==0)
        {
            file = arg[i+1];
            arg[i] = NULL;
        }
    }

    if(how == have_pipe) //命令中只有一个管道符号
    {
        for(i=0; arg[i]!=NULL; i++)
        if(strcmp(arg[i],"|")==0)
        {
            arg[i] = NULL;
            i++;
            int j = 0;
            //将管道命令后边的命令存入argnext中
            while(arg[i] != NULL)
            {
                argnext[j++]=arg[i++];
            }
            argnext[j] = NULL;
            break;
        }
    }

    //创建子进程
    pid = fork();
    if(pid<0)
    {
        perror("fork failure");
        return;
    }

    switch(how)
    {
        case 0:         //一般命令
                if(pid == 0) //子进程执行用户输入的命令
                {
                    if(!find_command(arg[0])) //判断命令是否可执行
                    {                          //find_commit函数成功返回1,失败返回0
                        printf("%s: command not found\n",arg[0]);
                        exit(0);
                    }
                    execvp(arg[0],arg);//和execv函数函数用法类似,不同的是,参数filename,该参数如果包含"/"就相当于路径名,如果不含"/"就到PATH环境变量定义的目录找可执行文件
                    exit(0);
                }
                break;
        case 1:         //命令中含有重定向符>
            if(pid == 0)  //子进程
            {
                if(!find_command(arg[0]))
                {
                    printf("%s: command not found\n",arg[0]);
                    exit(0);
                }
                //打开或新建输出重定向的文件
                int fd =open(file,O_RDWR | O_CREAT | O_TRUNC, 0644);
                //将标准输出复制到打开的文件描述符,即用文件描述符替换标准输出
                dup2(fd,1);//dup(int oldfd, int neewfd),将其数值指定为1,即标准输出
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 2:         //命令中含有重定向符<
                if(pid == 0)  //子进程
                {
                    if(!find_command(arg[0]))
                    {
                        printf("%s:command not found\n");
                        exit(0);
                    }
                    int fd = open(file, O_RDONLY);
                    dup2(fd,0);//0标准输入
                    execvp(arg[0],arg);
                    exit(0);
                }
                break;
        case 3:         //命令中有管道符
        if(pid == 0)    //子进程
        {
            pid_t pid2;
            int fd2;
            if((pid2 = fork()) < 0) //在当前进程中新建一个子进程
            {
                perror("fork2 failure");
                return ;
            }
            if(pid2 == 0)     //新建的子进程执行管道符前边的命令
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s: command not found\n");
                    exit(0);
                }
                //将管道符前的命令执行结果存入fd2中
                fd2 = open("/tmp/youdonotkowfile",O_WRONLY | O_CREAT | O_TRUNC, 0664);
                dup2(fd2,1); //重定向标准输出
                execvp(arg[0],arg);
                exit(0);
            }
            waitpid(pid2,NULL,0);  //子进程等待孙子进程
            if(!find_command(argnext[0]))
            {
                printf("%s: command not found\n",argnext[0]);
                exit(0);
            }
            fd2 = open("/tmp/youdonotknowfile",O_RDONLY);
            dup2(fd2,0);    //将fd2定义为标准输入
            execvp(argnext[0],argnext); //执行管道命令符后的命令
            exit(0);
        }
            break;
        default:
            break;
        
    }
//命令中有后台运行符,则父进程直接返回,不等待子进程返回
if(background == 1)
{
    printf("[process id %d]\n",pid);
    return;
}
waitpid(pid,NULL,0); //父进程等待子进程返回
}

//判断命令是否可执行,是否有对应的可执行文件
int find_command(char *command)
{
    DIR *dir;
    struct dirent *ptr;
    char *path[] ={"./", "/bin", "/usr/bin",NULL};
    //当用户输入命令如 ./ls时,将ls命令与目录中的ls文件相匹配 如ls存储在/bin/ls 就可以在/bin目录中匹配到
    if(strncmp(command,"./",2) == 0)//最多比较前n个字节
    command = command +2;
    int i=0;
    while(path[i] != NULL)
    {
        if((dir = opendir(path[i])) == NULL)
        printf("can't open /bin\n");
        while((ptr = readdir(dir))!=NULL)
        if(strcmp(ptr->d_name,command)==0)
        {
            closedir(dir);
            return 1; //找到返回1
        }
        closedir(dir);
        i++;
    }
    return 0;    //没找到返回0
}