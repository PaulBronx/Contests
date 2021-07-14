#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <inttypes.h>

volatile int32_t speed = 0;
volatile int64_t distance = 0;
volatile sig_atomic_t  flag = 0;

void
handlerAl(int signal) {
    distance += speed;
    return;
}

void
handlerTE(int signal) {
    flag = 1;
    return;
}

void
handlerU1(int signal) {
    speed++;
    return;
}

void
handlerU2(int signal) {
    speed--;
    return;
}


int main(int argc, char *argv[]) {
    if (argc > 1) {
        speed = strtol(argv[1], NULL, 0);
    }

    sigset_t old_mask, new_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGALRM);
    sigaddset(&new_mask, SIGTERM);
    sigaddset(&new_mask, SIGUSR1);
    sigaddset(&new_mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);

    sigaction(SIGALRM, &(struct sigaction) {.sa_handler = handlerAl}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = handlerTE}, NULL);
    sigaction(SIGUSR1, &(struct sigaction) {.sa_handler = handlerU1}, NULL);
    sigaction(SIGUSR2, &(struct sigaction) {.sa_handler = handlerU2}, NULL);

    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    while(!flag ){
        sigsuspend(&old_mask);
    }
    printf("%"PRId64"\n",distance);
    return 0;
}
