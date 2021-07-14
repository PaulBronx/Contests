#include <stdio.h>              // пин-понг с mmap/signal
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/mman.h>

volatile sig_atomic_t got_sig = 2;
volatile pid_t sender_pid = 0;


void
handler(int signal, siginfo_t *si, void *data) {
    got_sig = signal;
    sender_pid = si->si_pid;
    // printf("%d: Got signal %d from %d\n", getpid(), signal, sender_pid);
    return;
}

void
kill_handler(int signal) {
    // printf("Killed with signal %d\n", signal);
    exit(0);
}

void pid_cr(int ind, sigset_t *old_mask, int *mem, pid_t *pid, int xmax, int nproc) {
    sigaction(SIGUSR1, &(struct sigaction) {.sa_sigaction = handler, .sa_flags = SA_SIGINFO}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = kill_handler}, NULL);
    sigaction(SIGKILL, &(struct sigaction) {.sa_handler = kill_handler}, NULL);

    printf("%d:%d\n", ind, getpid());
    while (1) {
        sigsuspend(old_mask);
        int x = mem[0];
        printf("%d: %d\n", ind, x);
        fflush(stdout);
        if (++x > xmax) {
            break;
        }
        mem[0] = x;
        int next = (ind+1) % nproc;
        printf("%d: kill to %d:%d\n", ind, next, pid[next]);
        kill(pid[next], SIGUSR1);
    }
    printf("%d: dead\n", ind+1);
    exit(0);
}

void killer(pid_t *pid, int n, pid_t skip){
    for(int i = 0; i < n; i++){
        if(pid[i] != skip){
            printf("parrent: kill child %d\n", i+1);
            kill(pid[i], SIGTERM);
        }
    }
    while(wait(NULL) > 0);
}

int main(int argc, char *argv[]) {
    int xmax = 10;
    int n_proc = 2;

    if (argc > 1) {
        xmax = strtol(argv[1], NULL, 0);
    }

    if (argc > 2) {
        n_proc = strtol(argv[2], NULL, 0);
    }

    sigset_t old_mask, new_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);
    sigaddset(&new_mask, SIGTERM);
    sigaddset(&new_mask, SIGKILL);
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);

    sigaction(SIGUSR1, &(struct sigaction) {.sa_sigaction = handler, .sa_flags = SA_SIGINFO}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = kill_handler}, NULL);
    sigaction(SIGKILL, &(struct sigaction) {.sa_handler = kill_handler}, NULL);

    pid_t *pid1;
    int *data;
    int msize = n_proc*sizeof(pid1[0]) + sizeof(data[0]);
    char *mem = mmap(NULL, msize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (mem == MAP_FAILED) {
        printf("mmap(): errpr %d: %s\n", errno, strerror(errno));
        return 1;
    }
    pid1 = (pid_t*)mem;
    data = (int*)(mem + n_proc*sizeof(pid1[0]));

    for (int i = 0; i < n_proc; i++) {
        pid_t son = fork();
        if (son == 0) { //son 1
            pid_cr(i, &old_mask, data, pid1, xmax, n_proc);
        }
        if(son == (pid_t)-1){
            killer(pid1, i, 0);
            munmap(mem, msize);
            return 1;
        }
        pid1[i] = son;
    }

    data[0] = 0;
    printf("Parent: send SIGUSR1 to child 0:%d\n", pid1[0]);
    kill(pid1[0], SIGUSR1);

    pid_t pid = wait(NULL);
    killer(pid1, n_proc, pid);
    munmap(mem, msize);
    return 0;
}

