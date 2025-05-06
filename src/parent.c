#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "parent.h"

pid_t children[MAX_CHILDREN];
int child_count = 0;

void spawn_child() {
    if (child_count >= MAX_CHILDREN) {
        printf("PARENT %d: Maximum number of children reached.\n", getpid());
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        execl("./child", "child", NULL);
        perror("execl failed");
        exit(1);
    } else {
        children[child_count++] = pid;
        printf("PARENT %d: Spawned CHILD %d\n", getpid(), pid);
    }
}

void kill_last_child() {
    if (child_count <= 0) {
        printf("PARENT %d: No children to kill.\n", getpid());
        return;
    }

    pid_t pid = children[--child_count];
    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
    printf("PARENT %d: Killed CHILD %d, remaining: %d\n", getpid(), pid, child_count);
}

void list_processes() {
    printf("PARENT %d: Active children:\n", getpid());
    for (int i = 0; i < child_count; i++) {
        printf("  CHILD %d\n", children[i]);
    }
}

void kill_all_children() {
    for (int i = 0; i < child_count; i++) {
        kill(children[i], SIGKILL);
        waitpid(children[i], NULL, 0);
        printf("PARENT %d: Killed CHILD %d\n", getpid(), children[i]);
    }
    child_count = 0;
}

int main() {
    printf("PARENT %d: Ready. Use + to spawn, - to kill last, l to list, k to kill all, q to quit.\n", getpid());

    char command;
    while ((command = getchar()) != EOF) {
        switch (command) {
            case '+':
                spawn_child();
                break;
            case '-':
                kill_last_child();
                break;
            case 'l':
                list_processes();
                break;
            case 'k':
                kill_all_children();
                break;
            case 'q':
                kill_all_children();
                printf("PARENT %d: Quitting.\n", getpid());
                exit(0);
            default:
                break;
        }
    }

    return 0;
}