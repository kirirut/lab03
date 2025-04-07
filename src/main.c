#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/wait.h>
#include "child.h"
#include "parent.h"
#include "common.h"

extern pid_t children[MAX_CHILDREN];
extern int num_children;

void set_noncanonical_mode(struct termios *oldt) {
    struct termios newt;
    tcgetattr(STDIN_FILENO, oldt);
    newt = *oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restore_terminal_mode(struct termios *oldt) {
    tcsetattr(STDIN_FILENO, TCSANOW, oldt);
}

int main(void) {
    struct termios oldt;
    set_noncanonical_mode(&oldt);
    setup_parent_signals();

    printf("Parent [PID=%d]: Program started. Commands: '+' create, '-' kill last, 'l' list, 'k' kill all, 'q' quit.\n", getpid());
    fflush(stdout);

    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '+') {
            if (num_children >= MAX_CHILDREN) {
                printf("Max children reached.\n");
            } else {
                pid_t pid = fork();
                if (pid == 0) {
                    child_process();
                } else if (pid > 0) {
                    children[num_children++] = pid;
                    printf("Parent: Created child PID=%d (total: %d)\n", pid, num_children);
                } else {
                    perror("fork");
                }
            }
        } else if (ch == '-') {
            if (num_children > 0) {
                pid_t pid = children[--num_children];
                kill(pid, SIGTERM);
                waitpid(pid, NULL, 0);
                printf("Parent: Terminated child PID=%d\n", pid);
            } else {
                printf("No children to kill.\n");
            }
        } else if (ch == 'l') {
            printf("Parent PID=%d\n", getpid());
            for (int i = 0; i < num_children; i++) {
                printf("  Child %d: PID=%d\n", i+1, children[i]);
            }
        } else if (ch == 'k') {
            kill_all_children();
        } else if (ch == 'q') {
            kill_all_children();
            break;
        }
        fflush(stdout);
    }

    restore_terminal_mode(&oldt);
    return EXIT_SUCCESS;
}
