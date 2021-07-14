#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main (int argc, char *argv[]) {
     int fd[2];
     pipe(fd);
     if ( fork() == 0){
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1],NULL);
        _exit(1);
     }
     close(fd[0]);
     dup2(fd[1],1);
     close(fd[1]);
     int g;
     while((g = getchar()) != EOF){
        putchar(g);
     }
     fflush(stdout);
     close(1);
     wait(NULL);
     return 0;
}
