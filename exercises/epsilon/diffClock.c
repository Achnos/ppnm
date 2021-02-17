//
// Implemented by Marc B. Sørensen on 2/13/21.
//

#include <time.h>
#include "funcs.h"

double diffClock(clock_t startTime, clock_t endTime){
  /*
  Function diffClock, takes two arguments, the time stamp
  of the start and end of a time interval of interest.

  ¤ startTime : Timestamp of beginning of time interval
  ¤ endTime   : Timestamp of ending of time interval

  */

  double diffTicks  =  clock1 - clock2;
  double diffms     =  (diffticks * 10) / CLOCKS_PER_SEC;

  return diffms;
}
