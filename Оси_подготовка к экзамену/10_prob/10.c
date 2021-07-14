#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    double x0 = 0, dx = 0;
    int n = 0;
    if (argc > 1){
        x0 = strtod(argv[1], NULL);
    }
    if (argc > 2){
        n = strtol(argv[2], NULL, 0);
    }
    if (argc > 3){
        dx = strtod(argv[3], NULL);
    }
    int fd12[2], fd21[2];
    pipe (fd12);
    pipe (fd21);
    if(fork() == 0){       //son  1
        close(fd12[0]);
        close(fd21[1]);
        if(fork() == 0){    //gson 1
            double val, sum = 0;
            for(int i = 0; i <= n; i++){
                val = sin (x0 + i * dx);
                write(fd12[1], &val, sizeof(val));
            }
            close(fd12[1]);
            for(int i = 0; i <= n; i++){
                read(fd21[0], &val, sizeof(sum));
                sum += val * val;
            }
            close(fd21[0]);                                    // e - в экспаненте +-x.xxxxxxe+-nnn
                                                               // g - 
            printf("1 %.10g\n", sum);
            exit(0);
        }
        close(fd12[1]);
        close(fd21[0]);
        wait(NULL);
        exit(0);
    }

    if(fork() == 0){       //son  2
        close(fd21[0]);
        close(fd12[1]);
        if(fork() == 0){    //gson 2
            double val, sum = 0;
            for(int i = 0; i <= n; i++){
                val = cos (x0 + i * dx);
                write(fd21[1], &val, sizeof(val));
            }
            close(fd21[1]);
            for(int i = 0; i <= n; i++){
                read(fd12[0], &val, sizeof(sum));
                sum += fabs(val);
            }
            close(fd12[0]);
            printf("2 %.10g\n", sum);
            exit(0);
        }
        close(fd12[0]);
        close(fd21[1]);
        wait(NULL);
        exit(0);
    }

    close(fd12[0]);
    close(fd12[1]);
    close(fd21[0]);
    close(fd21[1]);

    while(wait(NULL) > 0);
    printf("0 0\n");
    return 0;
}
