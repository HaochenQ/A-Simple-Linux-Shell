/**
 * File: 530shell.c
 * Description: A simple Linux Shell
 * Author: Haochen Qi
 * Hornor pledge: This program is finished individually
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define space "\t\r\n\a"
#define size 2048
//main
int main(int argc, char *argv[])
{
    char buffer[size];
    char cmd[size];
    char parameter[size];

    pid_t pid;
    int status;
    //initial position
    int i = 0;
    int j = 0;
    int z = 0;
    //print the first '%'
    printf("%% ");
    while ((fgets(buffer, size, stdin)) != NULL)
    {
        //reset all array and parameter for a new loop
        i = 0;
        j = 0;
        z = 0;
        //a=0;
        memset(cmd, 0, size);
        memset(parameter, 0, size);
        for (int k = 0; k < size; k++)
        {
            if (buffer[k] == '\n' || buffer[k] == EOF)
            {
                buffer[k] = '\0';
            }
        }
        /*if (buffer[strlen(buffer) - 1] == '\n' || buffer[strlen(buffer) - 1] == EOF)
            buffer[strlen(buffer) - 1] = '\0';*/
        while (buffer[i] == ' '&&i<=size) //ignore the space before cmd
            i++;
        while (buffer[i] != ' '&&i<=size) //ignore the space between cmd and para
        {
            cmd[j] = buffer[i];
            i++;
            j++;
        }
        while (buffer[i] == ' '&&i<=size)
            i++;
        while (buffer[i] != '\0'&&i<=size)
        {
            if (buffer[i] == ' '&&i<=size) //convert multiple spaces into one
            {
                while (buffer[i + 1] == ' '&&i<=size)
                {
                    i++;
                }
            }
            if (buffer[i] == '\t'&&i<=size) //convert tab into space
            {
                buffer[i] = ' ';
            }
            parameter[z] = buffer[i];
            z++;
            i++;
        }
        pid = fork();
        if (pid < 0)
        {
            perror("fork error");
        }
        // child process
        else if (pid == 0)
        {
            if (parameter[0] == 0)
            {
                execlp(cmd, cmd, (char *)0);
            }
            //char* cmd1=(char*)cmd;
            //char* para=(char*)parameter;
            if (execlp(cmd, cmd, parameter, (char *)0) == -1)
            {
                perror("execution error");
            }

            exit(127);
        }
        // parent process
        else if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            perror("waitpid error");
        }
        memset(buffer, 0, size);
        printf("%% ");
    }
    return 0;
}
