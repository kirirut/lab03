#ifndef COMMON_H
#define COMMON_H

#include <signal.h>

#define MAX_CHILDREN 100
#define CYCLES 101
#define SLEEP_NSEC 25000000  // 25 мс
#define TIMER_INTERVAL_USEC 100000 // 100 мкс

struct Pair {
    int a;
    int b;
};

extern volatile struct Pair sharedPair;
extern volatile sig_atomic_t count00, count01, count10, count11;
extern volatile sig_atomic_t cycle_count;
extern volatile sig_atomic_t print_allowed;

#endif // COMMON_H
