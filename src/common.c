#include "common.h"

volatile struct Pair sharedPair = {0, 0};
volatile sig_atomic_t count00 = 0, count01 = 0, count10 = 0, count11 = 0;
volatile sig_atomic_t cycle_count = 0;
volatile sig_atomic_t print_allowed = 0;
