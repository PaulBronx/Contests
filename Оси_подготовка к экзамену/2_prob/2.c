#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    if(fork() == 0) {
        int fd[2];
        if (pipe(fd) == -1){
            _exit(-1);
        }
        if(fork() == 0){
            close(fd[0]);
            pid_t pp[2];
            pp[0] =  getppid();
            pp[1] = getpid();
            if (write(fd[1], pp, sizeof(pp)) < 0){
                _exit(-1);
            }
            close(fd[1]);
            _exit(0);
        }
        if(fork() == 0){
            close(fd[1]);
            pid_t pp[2];
            if(read(fd[0], pp, sizeof(pp)) < 0){
                _exit(-1);
            }
            printf("%d %d\n", pp[0], pp[1]);
            fflush(stdout);
            close(fd[0]);
            _exit(0);
        }
        close(fd[0]);
        close(fd[1]);
        while (wait(NULL) > 0);
        _exit(0);
    }
    wait(NULL);
    return 0;
}
