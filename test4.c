
//自己实现一个简单的shell
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
//1:获取终端输入(scanf接收一个输入信息)
//2:解析输入（按空格解析到一个一个的命令参数）
//3：创建一个子进程：在子进程中级进行程序替换，让子进程运行命令
//4：等待子进程运行完毕，收尸，获取退出状态码
 
int argc;
char *argv[32];
int param_parse(char *buff)
{
    if(buff == NULL)
        return -1;
    char *ptr = buff;
    char *tmp = ptr;
    int argc = 0;
    while((*ptr) != '\0')
    {
        if(isspace(*ptr))//判断是否为： 空格 /f   /n   /r  /t   /v
        {
        //如果返回值为真,且不是回车‘\0’(没有结束)
        //将空格置为‘\0’
        //使用argv[argc]来保存这个字符串位置
        //循环，直到返回值为假或者结束
        //解决l     -s （多空格无法识别的问题）
            while(isspace(*ptr) && *ptr != '\0')
            {
                *ptr++ = '\0';
            }
            argv[argc++] = tmp;
            tmp = ptr;
        }
        ptr++;
   }
    argv[argc++] = tmp;
    argv[argc] = NULL;
    return 0;
}
int do_exec()
{
    int pid = 0;
    pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        execvp(argv[0],argv);
        exit(0);
    }
    //父进程在这里必须等待子进程退出，来观察子进程为什么会退出
    //是否出现了什么错误，通过获取状态码，并且转换退出码所对应
    //的错误信息进行打印
    int statu;
    wait(&statu);
    //判断子进程是否代码运行完毕退出
    if(WIFEXITED(statu))
    {
        //获取到子进程的退出码，转换为文本信息
        printf("%s",strerror(WEXITSTATUS(statu)));
    }
    return 0; 
}
 
int main()
{
    while(1)
    { 
        printf("shell> ");
        fflush(stdout);
        char buff[1024] = {0}; 
        if(scanf("%[^\n]%*c",buff) ==2) //scanf回车代表结束
        {
        getchar();//获取一个回车，防止直接回车出现的死循环
        }
        //scanf本身遇见空格就要获取一次，这样就无法获取完整命令
        //%[^\n]：获取数据直到遇见\n为止
        //%*c    清空缓冲区，数据都不要（不然还存有是上一个\n）
        //从缓冲区取出，直接丢掉。防止回车死循环
        printf("%s\n",buff);
        param_parse(buff);
        do_exec();
    }
    return 0;
}