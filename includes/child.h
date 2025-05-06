#define _POSIX_C_SOURCE 200809L

#ifndef CHILD_H
#define CHILD_H

#include <signal.h>

typedef struct {
    int a;
    int b;
} pair_t;

extern volatile pair_t data;
extern volatile sig_atomic_t stats[4];
extern volatile sig_atomic_t cycles;

void handle_alarm(int signo);

#endif