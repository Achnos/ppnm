//
// Implemented by Marc B. Sørensen on 2/13/21.
//

#include "funcs.h"
#include <math.h>

int equal(double a, double b, double tau, double epsilon){
  /*
  Function equal, takes two doubles, compares and checks if they are the same.

  ¤ a, b    : Doubles to be compared.
  ¤ tau     : Small tolerance for absolute precision comparison
  ¤ epsilon : Small tolerance for relative precision comparison

  */

  if ( (fabs( a - b ) < tau) || ((fabs( a - b ) / ( fabs(a) + fabs(b) )) < (epsilon / 2)) ) {
    return 1;
  }
  else {return 0; }
}
