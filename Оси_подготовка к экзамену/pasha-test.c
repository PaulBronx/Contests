/*
 * pasha-test.c
 *
 * Получает SIGUSR1, читает из stdin число
 *  возводит в квадрат, печатает на stdout
 *  отправляет SIGUSR1 тому, кто послал сигнал.
 * По SIGUSR2 умирает
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <inttypes.h>

static volatile sig_atomic_t gotsig;
static volatile pid_t sender;

void
handler(int signal, siginfo_t *si, void *data)
{
    gotsig = signal;
    sender = si->si_pid;
}

int
main()
{
    sigset_t old_mask, new_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);
    sigaddset(&new_mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &new_mask, &old_mask);
    sigaction(SIGUSR1, &(struct sigaction ) { .sa_sigaction = handler,
                              .sa_flags = SA_RESTART | SA_SIGINFO },
              NULL);
    sigaction(SIGUSR2, &(struct sigaction ) { .sa_sigaction = handler,
                              .sa_flags = SA_RESTART | SA_SIGINFO },
              NULL);

    pid_t iam = getpid();

    while(1) {
        uint32_t x;
        fprintf(stderr, "test %d: waiting\n", iam);
        sigsuspend(&old_mask);
        if(gotsig == SIGUSR2) {
            fprintf(stderr, "test %d: break on SIGUSR2\n", iam);
            break;
        }
        if(gotsig == SIGUSR1) {
            fprintf(stderr, "test %d: got signal SIGUSR1\n", iam);
            if(scanf("%"SCNu32, &x) != 1) {
                fprintf(stderr, "test %d: break on end of file or error\n",
                        iam);
                break;
            }
            fprintf(stderr, "test %d: got %" PRIu32 "\n", iam, x);
            uint32_t z = x * x;
            fprintf(stderr, "test %d: send %" PRIu32 "\n", iam, z);
            printf("%" PRIu32, z);
            fflush(stdout);
            fprintf(stderr, "test %d: send signal SIGUSR1 to %d\n", iam, sender);
            kill(sender, SIGUSR1);
        } else {
            fprintf(stderr, "test %d: got unknown signal\n", iam);
        }
    }

    return 0;
}

