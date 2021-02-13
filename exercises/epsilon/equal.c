//
// Implemented by Marc B. Sørensen on 2/13/21.
//

#ifndef EPSILON_EQUAL_C
#define EPSILON_EQUAL_C

int equal(double a, double b, double tau, double epsilon){
  // This function must be placed in a separate .c file, compiled separately and then linked to the final executable.
  if ( (fabs( a - b ) < tau) || ((fabs( a - b ) / ( fabs(a) + fabs(b) )) < (epsilon / 2)) ) {
    return 1;
  }
  else {return 0; }
}

#endif //EPSILON_EQUAL_C
