#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid, pid1, pid2, pid3, pid4;
    int status;
    printf("1 pid: %d  ppid: %d\n", getpid(), getppid());//1
    pid = fork();
    if(pid == 0)
    {
        printf("3 pid: %d  ppid: %d\n", getpid(), getppid());//3
        pid3 = fork();
        if(pid3 == 0)
        {
            printf("5 pid: %d  ppid: %d\n", getpid(), getppid());//5
        }else{
            pid4 = fork();
            if(pid4 == 0)
            {
                printf("6 pid: %d  ppid: %d\n", getpid(), getppid());//6
            }else{
                waitpid(pid4, &status, 0);
            }
            waitpid(pid3, &status, 0);
        }
    }else{
        pid1 = fork();
        if(pid1 == 0)
        {
            printf("2 pid: %d  ppid: %d\n", getpid(), getppid());//2
            pid2 = fork();
            if(pid2 == 0)
            {
                printf("4 pid: %d  ppid: %d\n", getpid(), getppid());//4
            }else{
                waitpid(pid2, &status, 0);
            }
        }else{
            waitpid(pid1, &status, 0);
        }
        waitpid(pid, &status, 0);
    }
    exit(0);
}