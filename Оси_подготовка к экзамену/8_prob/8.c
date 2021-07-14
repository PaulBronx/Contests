#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>

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

void pid_cr(int ind, sigset_t *old_mask, int *fd, int xmax) {
    sigaction(SIGUSR1, &(struct sigaction) {.sa_sigaction = handler, .sa_flags = SA_SIGINFO}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = kill_handler}, NULL);
    sigaction(SIGKILL, &(struct sigaction) {.sa_handler = kill_handler}, NULL);

    printf("%d:\n", ind);

    sigsuspend(old_mask);
    pid_t pid;
    int n = read(fd[0], &pid, sizeof(pid));
    printf("%d: got pid %d\n", ind, pid);
    kill(getppid(), SIGUSR1);
    if (n <= 0) {
        exit(1);
    }

    while (1) {
        sigsuspend(old_mask);
        int x;
        if (read(fd[0], &x, sizeof(x)) <= 0) {
            break;
        }
        printf("%d: %d\n", ind, x);
        fflush(stdout);
        if (++x > xmax) {
            break;
        }
        if (write(fd[1], &x, sizeof(x)) <= 0) {
            break;
        }
        kill(pid, SIGUSR1);
    }
    printf("%d: dead\n", ind);
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
    free(pid);
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
    //sigaddset(&new_mask, SIGUSR2);
    sigaddset(&new_mask, SIGTERM);
    sigaddset(&new_mask, SIGKILL);
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);

    sigaction(SIGUSR1, &(struct sigaction) {.sa_sigaction = handler, .sa_flags = SA_SIGINFO}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = kill_handler}, NULL);
    sigaction(SIGKILL, &(struct sigaction) {.sa_handler = kill_handler}, NULL);

    pid_t *pid1;
    pid1 = malloc(n_proc * sizeof(pid1[0]));
    if (!pid1) {
        return 1;
    }

    int fd[2];
    if (pipe(fd) < 0) {
        free(pid1);
        return 1;
    }
    for (int i = 0; i < n_proc; i++) {
        pid1[i] = fork();
        if (pid1[i] == 0) { //son 1
            pid_cr(i + 1, &old_mask, fd, xmax);
        }
        if(pid1[i] == (pid_t)-1){
            killer(pid1, i,0);
            close(fd[1]);
            close(fd[0]);
            return 1;
        }
    }
    for (int i = 0; i < n_proc; i++) {
        int w;
        printf("Parent: init child %d\n", i + 1);
        if (i+1 < n_proc) {
            w = write(fd[1], &pid1[i + 1], sizeof(pid1[0]));
        } else {
            w = write(fd[1], &pid1[0], sizeof(pid1[0]));
        }
        if(w <= 0){
            killer(pid1,n_proc,0);
            close(fd[1]);
            close(fd[0]);
            return 1;
        }
        kill(pid1[i], SIGUSR1);
        sigsuspend(&old_mask);
    }
    
    int x = 0;
    if (write(fd[1], &x, sizeof(x)) <= 0) {
        printf("Parent: wrtie error\n");
        killer(pid1, n_proc, 0);
        close(fd[1]);
        close(fd[0]);
        return 1;
    }
    close(fd[0]);
    close(fd[1]);
    printf("Parent: send SIGUSR1 to child 1\n");
    kill(pid1[0], SIGUSR1);

    pid_t pid = wait(NULL);
    killer(pid1, n_proc, pid);
    return 0;
}
