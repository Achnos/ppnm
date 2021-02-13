//
// Implemented by Marc B. Sørensen on 2/13/21.
//

#ifndef EPSILON_DIFFCLOCK_C
#define EPSILON_DIFFCLOCK_C

#include <time.h>

double diffClock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock1 - clock2;
    double diffms = (diffticks * 10) / CLOCKS_PER_SEC;
    return diffms;
}

#endif //EPSILON_DIFFCLOCK_C
