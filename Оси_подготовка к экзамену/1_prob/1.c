#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    printf("Parent: %d\n", getpid());
    fflush(stdout);
    pid = fork();
    if(pid == 0) {
        printf("Child: %d\n", getpid());
        fflush(stdout);
        _exit(0);
    }
    else if(pid < 0) {
        printf("Parent: fork() error\n");
    } else {
        pid = wait(NULL);
        printf("Parent: child %d  done\n", pid);
    }
    return 0;
}
