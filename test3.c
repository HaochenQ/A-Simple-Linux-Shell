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
    
    char **tokens = malloc(size * sizeof(char*));
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
        for (int k = 0; k < size; k++)
        {
            if (buffer[k]=='\n')
            {
                buffer[k]='\0';
            }
            
        }
        if (buffer[strlen(buffer) - 1] == '\n' || buffer[strlen(buffer) - 1] == EOF)
            buffer[strlen(buffer) - 1] = '\0';
        while (buffer[i] == ' ')
            i++;
        while (buffer[i] != ' ')
        {
            //tokens[j] = buffer[i];
            cmd[j] = buffer[i];
            i++;
            j++;
        }
        while (buffer[i] == ' ')
            i++;
        while (buffer[i] != '\0')
        {   
            if (buffer[i]==' ')
            {
                while (buffer[i+1]==' '){
                    i++;
                }
            }
            if (buffer[i]=='\t')
            {
                buffer[i]=' ';
            }
            //tokens[j]=buffer[i];
            parameter[z] = buffer[i];
            z++;
            i++;
            //j++;
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

            if (execlp(cmd,cmd,parameter,(char *)0) == -1)
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
