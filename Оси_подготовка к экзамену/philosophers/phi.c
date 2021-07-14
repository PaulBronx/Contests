#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <inttypes.h>
#include <sys/msg.h>

#include <errno.h>
#include <string.h>

struct buff {
    int64_t type;
    int64_t val1;
    int64_t val2;
};


int main (int argc, char *argv[]){

    key_t key = strtol(argv[1], NULL, 0);
    int n  = strtol(argv[2], NULL, 0);
    int64_t val1 = strtol(argv[3], NULL, 0);
    int64_t val2 = strtol(argv[4], NULL, 0);
    int64_t maxval = strtol(argv[5], NULL, 0);

    int ms = msgget(key, 0660 | IPC_CREAT | IPC_EXCL);
    struct buff c;
    if (ms == -1){
        fprintf(stderr,"msgget crush: %s\n", strerror(errno));
        return -1;
    }
    for (int i = 0; i < n; i++){
        pid_t pid;
        if ((pid = fork()) == 0){
            while (1){
                ssize_t rea = msgrcv(ms, &c, sizeof(c), i + 1, 0) ;
                if (rea == -1){
                    fprintf(stderr,"msgrcv cruch in %d\n", i);
                    break;
                }
                int64_t sum = c.val1 + c.val2;
                fprintf(stdout,"%d ""%"PRId64"\n", i, sum);
                if (sum <= maxval){
                    c.val1 = c.val2;
                    c.val2 = sum;
                    c.type = (sum % n) + 1;
                    msgsnd(ms, &c, sizeof(c), 0);
                } else {
                    break;
                }
            }
            exit(0);
        }else if (pid < 0)  {
            fprintf(stderr,"fork cruch on %d\n", i);
            msgctl(ms, IPC_RMID, NULL);
            while(wait (NULL) > 0);
            return -1;
        }
    }
    
    c.val1 = val1;
    c.val2 = val2;
    c.type = ((val1 + val2) % n) + 1;
    msgsnd (ms, &c, sizeof(c), 0);

    wait(NULL);
    msgctl(ms, IPC_RMID, NULL);
    while(wait (NULL) > 0);

    return 0;
}
