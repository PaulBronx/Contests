#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


/*
P{
    +fd[]
    +C1
    !fd[0]
    0 > fd[1]
    !fd[1]
    C1{
        in = fd[0]
        fd_1[]
        out = fd_1[1]
        +C2 (fd, fd_1)
        !fd_1[0]
        !fd[1]
        { n<in, n++>out }
    }
    C2{
        !fd_1[1]
        !in
        in=fd_1[0]
        +fd_1[]
        out = fd_1[1]
        +C3(fd, in, fd_1)
        !fd[0]
        !fd[1]
        !fd_1[0]
        { n<in, n++>out }
    }
    ...
    Cn{
        !in
        !fd[0]
        !fd_1[1]
        in=fd_1[0]
        out=fd[1]
        { n<in, n++>out }
    }
*/

int main(int argc, char *argv[])
{
    int max = strtol(argv[1], NULL, 10);
    int fd12[2], fd21[2];
    if(pipe(fd12) < 0 || pipe(fd21) < 0){
        _exit(-1);
    }
    int val = 0;
    if(fork() == 0){// 1 son
        close(fd12[0]);
        close(fd21[1]);
        while (1) {
            if (read(fd21[0], &val, sizeof(val)) <= 0){
                    break;
            }
            printf("son1 %d\n", val);
            fflush(stdout);
            val++;
            if (val > max){
                break;
            }
            if (write(fd12[1], &val, sizeof(val)) < 0){
                     break;
            }
        }
        close(fd12[1]);
        close(fd21[0]);
        exit(0);
    }
    if (fork() == 0){// 2 son
        close(fd21[0]);
        close(fd12[1]);
        while(1){
            if (read(fd12[0], &val, sizeof(val)) <= 0){
                    break;
            }
            printf("son2 %d\n",val);
            fflush(stdout);
            val++;
            if(val > max){
                break;
            }
            if (write(fd21[1], &val, sizeof(val)) < 0){
                    break;
            }
        }
        close(fd21[1]);
        close(fd12[0]);
        exit(0);
    }
    close(fd21[0]);
    if (write(fd21[1], &val, sizeof(val)) < 0){
            ;
    }
    close(fd21[1]);
    close(fd12[0]);
    close(fd12[1]);
    while(wait(NULL) > 0);
    return 0;
}
