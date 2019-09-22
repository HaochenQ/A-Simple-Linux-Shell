#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define MAXLINE 2048
int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    char com[MAXLINE];
    char para[MAXLINE];
    int i = 0, p_l = 0, c_l = 0;
    pid_t pid;  //存储子进程的id
    int status; //waitpid函数返回的子进程的状态

    printf("%% "); //输出提示符%
    while ((fgets(buf, MAXLINE, stdin)) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        //重新设置命令和参数
        i = 0;
        p_l = 0;
        memset(com, 0, MAXLINE);
        c_l = 0;
        memset(para, 0, MAXLINE);

        printf("buf:%s\n", buf);
        while (buf[i] == ' ') //将命令开始的空格都给忽略掉
            i++;
        while (buf[i] != ' ') //读取命令
        {
            com[c_l] = buf[i];
            i++;
            c_l++;
        }
        while (buf[i] == ' ') //将命令和参数之间的空格都给忽略掉
            i++;
        while (buf[i] != '\0') //读取参数
        {
            if (buf[i] != ' ') //将参数中间的空格忽略掉
            {
                para[p_l] = buf[i];
                p_l++;
            }
            i++;
        }
        //printf("com:%s para:%s\n", com, para);

        pid = fork(); //创建子进程
        if (pid < 0)  //创建子进程出错
        {
            perror("fork error");
        }

        else if (pid == 0) //子进程的执行部分
        {
            if (para[0] != 0)
                execlp(com, com, para, (char *)0);
            execlp(com, com, (char *)0);
            perror("execlp error"); //如果execlp()函数无法执行，则输出错误信息！
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0) //父进程等待子进程结束
        {
            perror("waitpid error");
        }
        memset(buf, 0, MAXLINE); //重新设置buf的缓存空间
        printf("%%");
    }
    return 0;
}
