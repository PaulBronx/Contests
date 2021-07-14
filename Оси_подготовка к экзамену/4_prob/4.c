#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <inttypes.h>

int main (int argc, char *argv[]){
    int fd12[2], fd21[2];
    char *prog = argv[1];
    pipe(fd12);
    pipe(fd21);
    int64_t m;
    scanf("%"SCNd64, &m);
    if(fork() == 0){//son exec
        close(fd12[1]);
        close(fd21[0]);
        dup2(fd12[0],0);
        dup2(fd21[1],1);
        close(fd12[0]);
        close(fd21[1]);
        execlp(prog, prog,NULL);
        _exit(-1);
    }
    if(fork() == 0){//son sum
        close(fd12[0]);
        close(fd12[1]);
        close(fd21[1]);
        int64_t sum = 0;
        FILE *in = fdopen(fd21[0], "r");
        while(fscanf(in,"%" SCNd64, &m) > 0){
                sum += m;
        }
        fclose(in);
        printf("%" PRId64"\n", sum);
        fflush(stdout);
        _exit(0);
    }
    close(fd12[0]);
    close(fd21[0]);
    close(fd21[1]);
    FILE *out = fdopen(fd12[1], "w");
    for(int64_t i = 1; i < m; i++){
            fprintf(out,"%" PRId64"\n", i*i);
    }
    fclose(out);
    return 0;
}
