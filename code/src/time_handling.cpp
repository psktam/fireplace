#include "time_handling.h"


unsigned long time_diff(unsigned long former_time, unsigned long current_time) {

    unsigned long max_ulong_val = 0;
    max_ulong_val -= 1;

    if (former_time > current_time) {
        return current_time + (max_ulong_val - former_time);
    }
    else {
        return current_time - former_time;
    }
}