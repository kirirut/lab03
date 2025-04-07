#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "child.h"
#include <stdlib.h>     // Для EXIT_SUCCESS
#include <sys/time.h>   // Для struct itimerval, setitimer и ITIMER_REAL


void child_sigusr2_handler(int signo) {
    (void)signo;
    print_allowed = 1;
}

void child_sigalrm_handler(int signo) {
    (void)signo;
    int a = sharedPair.a;
    int b = sharedPair.b;

    if(a == 0 && b == 0) count00++;
    else if(a == 0 && b == 1) count01++;
    else if(a == 1 && b == 0) count10++;
    else if(a == 1 && b == 1) count11++;

    cycle_count++;
}

void setup_child_signals() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = child_sigalrm_handler;
    sigaction(SIGALRM, &sa, NULL);

    sa.sa_handler = child_sigusr2_handler;
    sigaction(SIGUSR2, &sa, NULL);
}

void setup_timer() {
    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = TIMER_INTERVAL_USEC;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = TIMER_INTERVAL_USEC;
    setitimer(ITIMER_REAL, &timer, NULL);
}

void child_process() {
    setup_child_signals();
    setup_timer();

    struct timespec req = {0, SLEEP_NSEC};

    while (1) {
        while (cycle_count < CYCLES) {
            sharedPair.a = 0;
            nanosleep(&req, NULL);
            sharedPair.b = 0;
            nanosleep(&req, NULL);
            sharedPair.a = 1;
            nanosleep(&req, NULL);
            sharedPair.b = 1;
        }

        kill(getppid(), SIGUSR1);
        while (!print_allowed);

        printf("Child [PPID=%d, PID=%d]: {0,0}=%d, {0,1}=%d, {1,0}=%d, {1,1}=%d\n",
               getppid(), getpid(), count00, count01, count10, count11);
        fflush(stdout);

        print_allowed = 0;
        cycle_count = 0;
        count00 = count01 = count10 = count11 = 0;
    }

    _exit(EXIT_SUCCESS);
}
