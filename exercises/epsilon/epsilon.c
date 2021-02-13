#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include "funcs.h"

int main(){

  clock_t begin = clock();
  clock_t end   = clock();

  // Exercise epsilon.
  printf("\n-- Exercise epsilon -- \n");


  // 1.  INT_MAX -------------------------------------------------------------------
  printf("\ni. INT_MAX.\n");
  printf("---------------------------------------------- \n\n");
  begin = clock();

  int i = 1;
  while( i + 1 > i ) {
      i++;
  }
  printf("Done! Elapsed time (while loop)    = %g ms \n", (double)(diffClock(end, begin)) );

  i = 1;
  for (; i < i + 1; i++ ){
      ;
  }
  printf("Done! Elapsed time (for loop)      = %g ms \n", (double)(diffClock(end, begin)) );

  i = 1;
  do {
      i++;
  } while ( i + 1 > i );
  printf("Done! Elapsed time (do-while loop) = %g ms \n", (double)(diffClock(end, begin)) );

  end = clock();

  printf("\nMy max int             = %i         \n", i         );
  printf("The standard limit is  = %i         \n", INT_MAX     );
  printf("They differ by         = %i         \n", INT_MAX - i );

  // INT_MIN -------------------------------------------------------------------
  printf("\nii. INT_MIN.\n");
  printf("---------------------------------------------- \n\n");
  begin = clock();

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
  printf("---------------------------------------------- \n\n");

  float f = 1;
  while( 1 + f != 1 ){
    f /= 2;
  }
  f *= 2;

  f = 1;
  for  (; 1 + f != 1; f /= 2){
    ;
  }
  f *= 2;

  f = 1;
  do {
    f /= 2;
  } while ( 1 + f != 1  );
  f *= 2;

  double d = 1;
  while(  1 + d  != 1 ){  d /= 2;  }
  d  *= 2;
  d = 1;
  for  (; 1 + d  != 1;    d /= 2){;}
  d  *= 2;
  d = 1;
  do { d /= 2; } while ( 1 + d != 1 );
  d  *= 2;

  long double ld = 1;
  while(  1 + ld != 1 ){ ld /= 2;  }
  ld *= 2;
  ld = 1;
  for  (; 1 + ld != 1;   ld /= 2){;}
  ld *= 2;
  ld = 1;
  do{ ld /= 2; } while ( 1 + ld != 1 );
  ld *= 2;

  printf("Calculated epsilon for floats, doubles and long doubles are = %.20f, %.20g, %.20Lg. \n", f, d, ld);
  printf("The actual values are %.10f, %g and %Lg. \n", FLT_EPSILON, DBL_EPSILON, LDBL_EPSILON);

  // 2. ------------------------------------------------------------------------

  printf("\n2) Sum_up/down.\n");
  printf("---------------------------------------------- \n\n");

  int max = INT_MAX / 2;

  float sum_up_float   = 0;
  float sum_down_float = 0;

  for (int i = 1; i <= max; i++ ) { sum_up_float   += 1.0f / i;         }
  for (int i = 0; i <  max; i++ ) { sum_down_float += 1.0f / (max - i); }


  printf("Sum_up_float = %f.\nSum_down_float = %f.\n", sum_up_float, sum_down_float);


  double sum_up_double   = 0;
  double sum_down_double = 0;

  for (int i = 1; i <= max; i++ ) { sum_up_double   += 1.0 / i;         }
  for (int i = 0; i <  max; i++ ) { sum_down_double += 1.0 / (max - i); }


  printf("Sum_up_double = %f.\nSum_down_double = %f.\n", sum_up_double, sum_down_double);


  // 3. ------------------------------------------------------------------------
  printf("\n3) Int equal function.\n");
  printf("---------------------------------------------- \n\n");

  printf("\nI implemented the function, and i guess it works. \nNot sure what else to do with this assignment...\n ");

  // 4. ------------------------------------------------------------------------
  int digit;
  printf("\n4) Name the digit.\n");
  printf("---------------------------------------------- \n\n");
  printf("Please input your digit: \n");

  if (scanf("%d", &digit) == 1) {
    printf("Your digit was ");
    name_digit(digit);
  } else {
    printf("Failed to read integer.\n");
  }

  return 0;
}
