#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include "funcs.h"

void printDashes(){
  /*
  Prints a series of dashes to obtain separation in the output.
  */
  printf("---------------------------------------------- \n\n");
}


int main(){

  clock_t begin = clock(); // We define variables to hold the times used for timing the computations.
  clock_t end   = clock(); // These are defined in <time.h> and used in diffClock(). It is my own implementation.

  // Exercise epsilon.
  printf("\n-- Exercise epsilon -- \n");


  // 1.  INT_MAX -------------------------------------------------------------------
  printf("\ni. INT_MAX.\n");
  printDashes();
  begin = clock(); // Begin timing

  // We compute the INT_MAX using the while-loop
  int i = 1;
  while( i + 1 > i ) {
      i++;
  }
  printf("Done! Elapsed time (while loop)    = %g ms \n", (double)(diffClock(end, begin)) );

  // And then using a for-loop
  i = 1;
  for (; i < i + 1; i++ ){
      ;
  }
  printf("Done! Elapsed time (for loop)      = %g ms \n", (double)(diffClock(end, begin)) );

  // Lastly we try to use the do-while-loop
  i = 1;
  do {
      i++;
  } while ( i + 1 > i );
  printf("Done! Elapsed time (do-while loop) = %g ms \n", (double)(diffClock(end, begin)) );

  end = clock(); // End timing

  // Print out the values. The computations are the same between the three methods.
  printf("\nMy max int             = %i         \n", i         );
  printf("The standard limit is  = %i         \n", INT_MAX     ); // Compare with <limits.h>
  printf("They differ by         = %i         \n", INT_MAX - i );

  // INT_MIN -------------------------------------------------------------------
  printf("\nii. INT_MIN.\n");
  printDashes();
  begin = clock();

  // Now we'll do the same for INT_MIN, using the three methods again, once again timing.
  i = 1;
  while( i - 1 < i ) {
    i--;
  }
  printf("Done! Elapsed time (while loop)    = %g ms \n", (double)(diffClock(end, begin)) );

  i = 1;
  for (; i - 1 < i; i-- ){
    ;
  }
  printf("Done! Elapsed time (for loop)      = %g ms \n", (double)(diffClock(end, begin)) );

  i = 1;
  do {
    i--;
  } while ( i - 1 < i);
  printf("Done! Elapsed time (do-while loop) = %g ms \n", (double)(diffClock(end, begin)) );

  end = clock();


  printf("\nMy min int             = %i         \n", i         );
  printf("The standard limit is  = %i         \n", INT_MIN     );
  printf("They differ by         = %i         \n", INT_MIN - i );

  // iii. The machine epsilon --------------------------------------------------
  printf("\niii. The machine epsilon.\n");
  printDashes();
  // IT APPEARS THAT THE OPTIMIZATION SCHEME -OFAST WILL CAUSE THE COMPUTATIONS OF EPSILONS BELOW
  // TO BE BROKEN, SINCE WE WILL EVALUATE f!=0 INSTEAD, AND GET INFINITE PRECISION.

  // Here we compute the machine epsilon
  float f = 1.0f; // Start from a float, let's say 1.0...
  float prev_f; // This is where my solution differs from that of Dmitris.

  // We'll compute it using each of the three methods.
  while( (float) 1 + f != 1 ){ // Keep dividing 1.0, untill f is zero.
    prev_f = f; // We place the intermediate value in prev_f, since f ultimately ends up being 0 in the last step for some reason.
    f /= 2;     // We simply keep dividing by two untill the while loop cancels.
  }
  //prev_f *= 2;  // We multiply by two to actually get the difference between two adjacent floats. Otherwise we only have half the difference.

  f = 1.0f;
  for  (; (float) 1 + f != 1; f /= 2){  // Same for for-loops
    prev_f = f;
  }
  //prev_f *= 2;

  f = 1.0f;
  do {  // Same for do-while-loops
    prev_f = f;
    f /= 2;
  } while ( (float) 1 + f != 1  );
  //prev_f *= 2;

  double d = 1; // Do the same for doubles
  double prev_d;
  while(  1 + d  != 1 ){
    prev_d = d;
    d /= 2;
  }
  prev_d  *= 2;

  d = 1;
  for  (; 1 + d  != 1;    d /= 2){
    prev_d = d;
  }
  prev_d  *= 2;

  d = 1;
  do {
    prev_d = d;
    d /= 2;
  } while ( 1 + d != 1 );
  prev_d  *= 2;

  long double ld = 1.0L; // Finally do the same for long doubles
  long double prev_ld;
  while(  1 + ld != 1 ){
    prev_ld = ld;
    ld /= 2;
  }
  prev_ld *= 2;

  ld = 1.0L;
  prev_ld = 1;
  for  (; 1 + ld != 1;   ld /= 2){
    prev_ld = ld;
  }
  prev_ld *= 2;

  ld = 1.0L;
  prev_ld = 1;
  do{
    prev_ld = ld;
    ld /= 2;
  } while ( 1 + ld != 1 );
  prev_ld *= 2;

  printf("Calculated epsilon for floats, doubles and long doubles are\n%.10g,\n%.10g,\n%.10Lg. \n\n", prev_f, prev_d, prev_ld);
  printf("The actual values are \n%.10f,\n%.10g\n%.10Lg. \n", FLT_EPSILON, DBL_EPSILON, LDBL_EPSILON);

  // 2. ------------------------------------------------------------------------

  printf("\n2) Sum_up/down.\n");
  printDashes();

  int max = INT_MAX / 2;

  float sum_up_float   = 0;
  float sum_down_float = 0;

  for (int i = 1; i <= max; i++ ) { sum_up_float   += 1.0f / i;         }
  for (int i = 0; i <  max; i++ ) { sum_down_float += 1.0f / (max - i); }


  printf("Sum_up_float = %f.\nSum_down_float = %f.\n\n", sum_up_float, sum_down_float);


  double sum_up_double   = 0;
  double sum_down_double = 0;

  for (int i = 1; i <= max; i++ ) { sum_up_double   += 1.0 / i;         }
  for (int i = 0; i <  max; i++ ) { sum_down_double += 1.0 / (max - i); }


  printf("Sum_up_double = %f.\nSum_down_double = %f.\n\n", sum_up_double, sum_down_double);

  printf("ii)  Explain the difference.\n");
  printf("      ¤ The difference between the forward and backward sums of floats, and the difference between floats and doubles,\n");
  printf("        are due to the noncommutative nature of floating point arithmetic, and a lack of precision. Say we're forward \n");
  printf("        summing a bunch of floats. At some point the intermediate sum will larger than the precision, such that when  \n");
  printf("        we attempt to add another float, we'll get a rounding error. An example of this could be if we tried to sum   \n");
  printf("        10000000.0 and 1.0 with single precision floating point numbers (7 decimal pt. precision). The sum in this    \n");
  printf("        case would be 10000000.0 as it is rounded down to comply with precision. Thus the sum will terminate at some  \n");
  printf("        point before convergence, and will no longer seem to be updated. In the case of the backward sum we are       \n");
  printf("        trying to sum small numbers starting from a large number, and the sum terminates very early. This problem does\n");
  printf("        not pop up with doubles since we have double the decimal point precision and wont run into this issue.      \n\n");

  printf("iii) Does this sum converge as function of max?\n");
  printf("      ¤ I guess the answer here would seem to be no, since we'll get a rounding error before convergence.           \n\n");


  // 3. ------------------------------------------------------------------------
  printf("\n3) Int equal function.\n");
  printDashes();

  double a = 64.31235;
  double b = 11.9;

  printf("\nI implemented the function, and i guess it works. \nNot sure what else to do with this assignment...\n");

  printf("\n\nTesting if %g and %g are equal:\n", a, b);
  int returnval = equal(a, b, 1e-5, 1e-5);
  if(returnval == 1){
    printf("Yes, they are equal\n");
  }
  else{
    printf("No, they are not equal\n");
  }
  returnval = printf("Testing if %g and %g are equal: \n", a, a);
  if(returnval == 1){
    printf("Yes, they are equal\n");
  }
  else{
    printf("No, they are not equal\n");
  }
  // 4. ------------------------------------------------------------------------
  int digit;
  printf("\n4) Name the digit.\n");
  printDashes();
  printf("Please input your digit: \n");

  if (scanf("%d", &digit) == 1) {
    printf("Your digit was ");
    name_digit(digit);
  } else {
    printf("Failed to read integer.\n");
  }

  return 0;
}
