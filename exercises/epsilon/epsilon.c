#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <time.h>

double diffclock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock1 - clock2;
    double diffms = (diffticks * 10) / CLOCKS_PER_SEC;
    return diffms;
}

int equal(double a, double b, double tau, double epsilon){
  // This function must be placed in a separate .c file, compiled separately and then linked to the final executable.
  if ( (fabs( a - b ) < tau) || ((fabs( a - b ) / ( fabs(a) + fabs(b) )) < (epsilon / 2)) ) {
    return 1;
  }
  else {return 0; }
}

void name_digit( int dig ){
  switch (dig) {
    case 0:  printf("zero.        \n"); break;
    case 1:  printf("one.         \n"); break;
    case 2:  printf("two.         \n"); break;
    case 3:  printf("three.       \n"); break;
    case 4:  printf("four.        \n"); break;
    case 5:  printf("five.        \n"); break;
    case 6:  printf("six.         \n"); break;
    case 7:  printf("seven.       \n"); break;
    case 8:  printf("eight.       \n"); break;
    case 9:  printf("nine.        \n"); break;
    default: printf("Not a digit. \n");
  }
}

int main(){

  clock_t begin = clock();
  clock_t end   = clock();

  // Exercise epsilon.


  // 1.  INT_MAX -------------------------------------------------------------------
  printf("\ni. INT_MAX.\n");
  begin = clock();

  int i = 1;
  while( i + 1 > i ) {
      i++;
  }
  /*
  i = 1;
  for (; i < i + 1; i++ ){
      ;
  }

  i = 1;
  do {
      i++;
  } while ( i + 1 > i );
  */
  end = clock();

  printf("Done! Elapsed time     = %g      ms \n", (double)(diffclock(end, begin)) );
  printf("My max int             = %i         \n", i           );
  printf("The standard limit is  = %i         \n", INT_MAX     );
  printf("They differ by         = %i         \n", INT_MAX - i );

  return 0;
  // INT_MIN -------------------------------------------------------------------
  printf("ii. INT_MIN.\n");
  begin = clock();

  i = 1;
  while( i - 1 < i ) { i--; }
  i = 1;
  for (; i - 1 < i; i-- ){ ; }
  i = 1;
  do { i-- ; } while ( i - 1 < i);

  end = clock();

  printf("My min int = %i\n",i);
  printf("The standard limit is = %i\n",INT_MIN);

  printf("Done! Elapsed time: %g ms", (double)(diffclock(end, begin)) );

  // iii. The machine epsilon --------------------------------------------------
  printf("iii. The machine epsilon.\n");
  begin = clock();

  float f = 1;
  while(  1 + f  != 1 ){  f /= 2;  }
  f  *= 2;
  f = 1;
  for  (; 1 + f  != 1;    f /= 2){;}
  f  *= 2;
  f = 1;
  do { f /= 2; } while ( 1 + f != 1  );
  f  *= 2;

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

  printf("Calculated epsilon for floats, doubles and long doubles are = %.10f, %g, %Lg. \n", f, d, ld);
  printf("The actual values are %.10f, %g and %Lg. \n", FLT_EPSILON, DBL_EPSILON, LDBL_EPSILON);

  end = clock();
  printf("Elapsed time: %g ms\n", (double)(diffclock(end, begin)) );

  // 2. ------------------------------------------------------------------------

  printf("\n2) Sum_up/down.\n");
  int max = INT_MAX / 2;

  begin = clock();

  float sum_up_float   = 0;
  float sum_down_float = 0;

  for (int i = 1; i <= max; i++ ) { sum_up_float   += 1.0f / i;           }
  for (int i = 0; i <  max; i++ ) { sum_down_float += 1.0f / (max - i); }

  end = clock();

  printf("Sum_up_float = %f.\nSum_down_float = %f.\n", sum_up_float, sum_down_float);
  printf("Elapsed time: %g ms\n", (double)(diffclock(end, begin)) );

  begin = clock();

  double sum_up_double   = 0;
  double sum_down_double = 0;

  for (int i = 1; i <= max; i++ ) { sum_up_double   += 1.0 / i;           }
  for (int i = 0; i <  max; i++ ) { sum_down_double += 1.0 / (max - i); }

  end = clock();

  printf("Sum_up_double = %f.\nSum_down_double = %f.\n", sum_up_double, sum_down_double);
  printf("Elapsed time: %g ms\n", (double)(diffclock(end, begin)) );

  // 3. ------------------------------------------------------------------------
  printf("\n3) Int equal function.\n\nThe function must be placed in a separate .c file, compiled separately and then linked to the final executable. SEE THE EPSILON MATH ASSIGNMENT! It is already written...  ;)\n");

  // 4. ------------------------------------------------------------------------
  int *digit;
  printf("\n4) Name the digit.\n");
  printf("Please input your digit: ");
  //scanf("%i", digit);
  name_digit(*digit);

  return 0;
}
