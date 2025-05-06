#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "child.h"

volatile pair_t data;
volatile sig_atomic_t stats[4] = {0};
volatile sig_atomic_t cycles = 0;

void handle_alarm(int signo) {
    int index = data.a * 2 + data.b;
    if (index >= 0 && index < 4) {
        stats[index]++;
    }

    cycles++;
    if (cycles >= 101) {
        printf("CHILD PPID=%d PID=%d %d %d %d %d\n", getppid(), getpid(),
               stats[0], stats[1], stats[2], stats[3]);
        fflush(stdout);
        for (int i = 0; i < 4; i++) stats[i] = 0;
        cycles = 0;
    }
}

int main() {
    struct sigaction sa = {0};
    sa.sa_handler = handle_alarm;
    sigaction(SIGALRM, &sa, NULL);

    struct itimerval timer = {
        .it_interval = {0, 50000},
        .it_value = {0, 50000}
    };
    setitimer(ITIMER_REAL, &timer, NULL);

    struct timespec ts = {
        .tv_sec = 0,
        .tv_nsec = 3000000L
    };

    while (1) {
        nanosleep(&ts, NULL);
        data.a = 0;
        nanosleep(&ts, NULL);
        data.b = 0;
        nanosleep(&ts, NULL);
        data.a = 1;
        nanosleep(&ts, NULL);
        data.b = 1;
    }

    return 0;
}