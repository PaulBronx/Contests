#include <stdio.h>              // пин-понг с mmap/semaphore
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semblock (int semid, int s)
{
    struct sembuf ops[] ={
        {.sem_num = s, .sem_op = -1, .sem_flg = SEM_UNDO}
    };
    return semop(semid, ops, 1);
}

int semunblock (int semid, int s)
{
    struct sembuf ops[] ={
        {.sem_num = s, .sem_op = 1, .sem_flg = 0}
    };
    return semop(semid, ops, 1);
}

void pid_cr(int ind, int semid, int *mem, int xmax, int nproc) {
    printf("%d:%d semid = %d\n", ind, getpid(), semid);
    while (1) {
        if(semblock(semid,ind) < 0) {
            printf("%d: %d[%d]: %s\n", ind, semid, ind, strerror(errno) );
            break;
        }
        int x = mem[0];
        printf("%d: %d\n", ind, x);
        fflush(stdout);
        if (++x > xmax) {
            break;
        }
        mem[0] = x;
        int next = (ind+1) % nproc;
        printf("%d: unblock %d\n", ind, next);
        if(semunblock(semid, next) < 0) {
            break;
        }
    }
    printf("%d: dead\n", ind);
    exit(0);
}

int main(int argc, char *argv[]) {
    int xmax = 10;
    int n_proc = 2;
    key_t key = 0xBEEF;

    if (argc > 1) {
        xmax = strtol(argv[1], NULL, 0);
    }
    if (argc > 2) {
        n_proc = strtol(argv[2], NULL, 0);
    }
    if (argc >3) {
        key = strtol(argv[3], NULL, 0);
    }

    int sem = semget(key, n_proc, 0660 | IPC_CREAT | IPC_EXCL);
    printf("semget(0x%04X,%d) = %d\n", key, n_proc, sem);
    if(sem < 0) {
        printf("semget(): %s\n", strerror(errno));
        sem = semget(key, n_proc, 0);
        semctl(sem, 0, IPC_RMID);
        return 1;
    }
    for ( int i = 0; i < n_proc ; i++){
        semctl(sem, i, SETVAL, 0);
    }
    
    int *data;
    int msize = sizeof(data[0]);
    char *mem = mmap(NULL, msize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (mem == MAP_FAILED) {
        printf("mmap(): errpr %d: %s\n", errno, strerror(errno));
        semctl(sem, n_proc, IPC_RMID);
        return 1;
    }
    data = (int*)(mem);

    for (int i = 0; i < n_proc; i++) {
        pid_t son = fork();
        if (son == 0) { //son 1
            pid_cr(i, sem, data, xmax, n_proc);
        }
        if(son == (pid_t)-1){
            semctl(sem, n_proc, IPC_RMID);
            while(wait(NULL) > 0);
            munmap(mem, msize);
            return 1;
        }
    }

    data[0] = 0;
    printf("Parent: unblock child 0\n");
    semunblock(sem, 0);

    wait(NULL);
    semctl(sem, n_proc, IPC_RMID);
    while(wait(NULL) > 0);
    munmap(mem, msize);
    return 0;
}

