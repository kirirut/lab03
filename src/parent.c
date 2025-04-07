#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parent.h"
#include "common.h"
pid_t children[MAX_CHILDREN];
int num_children = 0;

void parent_sigusr1_handler(int signo, siginfo_t *info, void *context) {
    (void)signo;
    (void)context;
    if (info != NULL) {
        kill(info->si_pid, SIGUSR2);
    }
}

void setup_parent_signals() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = parent_sigusr1_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
}

void kill_all_children() {
    for (int i = 0; i < num_children; i++) {
        kill(children[i], SIGTERM);
        printf("Parent [PID=%d]: Terminated child PID=%d\n", getpid(), children[i]);
    }
    fflush(stdout);
    while (num_children > 0) {
        int status;
        pid_t pid = wait(&status);
        for (int i = 0; i < num_children; i++) {
            if (children[i] == pid) {
                for (int j = i; j < num_children - 1; j++) {
                    children[j] = children[j + 1];
                }
                num_children--;
                break;
            }
        }
    }
}
