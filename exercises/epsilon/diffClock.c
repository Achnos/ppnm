//
// Implemented by Marc B. Sørensen on 2/13/21.
//

#include <time.h>
#include "funcs.h"

double diffClock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock1 - clock2;
    double diffms = (diffticks * 10) / CLOCKS_PER_SEC;
    return diffms;
}
