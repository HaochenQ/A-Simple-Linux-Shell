/**
 * File: 530shell.c
 * Description: A simple Linux Shell
 * Author: Haochen Qi
 * Hornor pledge: This program is finished individually
 * Reference: https://brennan.io/2015/01/16/write-a-shell-in-c/
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define space "\t\r\n\a"
#define size 1048576
// read and parse input
/*  char *readInput(void)
{
    char *typeIn = NULL;
    //char *parsedInput = NULL;
    size_t bufferSize = 0;
    //typeIn =(char *)malloc(bufferSize * sizeof(char));
    if (typeIn == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
    //use getline/getlim to read stdin and dynamiclly allocate the memory
    getline(&typeIn, &bufferSize, stdin);
    int bufsize = 64, position = 0;
    char *cmds = malloc(bufsize * sizeof(char *));
    char *cmd;
    if (cmds == NULL)
    {
        perror("Unable to allocate buffer1");
        exit(1);
    }
    //parse command line input
    cmd = strtok(typeIn, space);
    while (cmd != NULL)
    {
        cmds[position] = cmd;
        position++;
        if (position >= bufsize)
        {
            bufsize += 64;
            cmds = realloc(cmds, bufsize * sizeof(char *));
            if (cmds == NULL)
            {
                perror("Unable to allocate buffer1");
                exit(1);
            }
        }
        cmd = strtok(NULL, space);
    }
    cmds[position]=NULL;
    return cmds;
}*/
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
    printf("%% ");
    while ((fgets(buffer, size, stdin)) != NULL)
    {
        //reset all array and parameter for a new loop
        i = 0;
        j = 0;
        z = 0;
        memset(cmd, 0, size);
        memset(parameter, 0, size);
        if (buffer[strlen(buffer) - 1] == '\n' || buffer[strlen(buffer) - 1] == EOF)
            buffer[strlen(buffer) - 1] = '\0';
        while (buffer[i] == ' ')
            i++;
        while (buffer[i] != ' ')
        {
            cmd[j] = buffer[i];
            i++;
            j++;
        }
        while (buffer[i] == ' ')
            i++;
        while (buffer[i] != '\0')
        {

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
            if (parameter[0] == NULL)
            {
                execlp(cmd, cmd, (char *)0);
            }

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
