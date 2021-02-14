//
// Implemented by Marc B. Sørensen on 2/13/21.
//

#ifndef EPSILON_FUNCS_H
#define EPSILON_FUNCS_H
#include <time.h>

extern double diffClock(clock_t clock1, clock_t clock2);

extern int equal(double a, double b, double tau, double epsilon);

extern void name_digit( int dig );

#endif //EPSILON_FUNCS_H
