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
#define size 2048
// read and parse input
char *readInput(void)
{
    char *typeIn = NULL;
    size_t bufferSize = 0;
    //use getline/getlim to read stdin and dynamiclly allocate the memory
    getline(&typeIn, &bufferSize, stdin);
}
//parse
char **parseInput(char *line)
{
    int bufsize = 64, position = 0;
    char **cmds = malloc(bufsize * sizeof(char *));
    char *cmd;
    if (cmds == NULL)
    {
        perror("Unable to allocate buffer1");
        exit(1);
    }
    //parse command line input
    cmd = strtok(line, space);
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
    cmds[position] = NULL;
    return cmds;
}
//main
int main(int argc, char *argv[])
{
    pid_t pid;
    char *input;
    char **args;
    int status;
    while (1){
        printf("%% ");
         input = readInput;
         args = parseInput(input);
         pid = fork();
        if (pid < 0)
        {
            perror("fork error");
        }
        // child process
        else if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
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
        free(input);
        free(args);
    } 
    return 0;
}
