/* Exercise "math"

    Calculate (using C mathematical functions):
        Γ(5) (Gamma function). Hint: man -k gamma.
        J1(0.5) (Bessel function). Hint: man -k bessel.
        √-2, e^i, e^iπ, i^e.

    Hints:
        There is no built-in format for complex numbers, you have to print separately the real and the complex parts using creal, creall, cimag, cimagl functions; read man creal and man cimag.
        The header file complex.h defines the imaginary unit as I.
        In some implementations the header math.h defines M_E (the value of e) and M_PI (the value of π). If not, you can define this constants (in double precision) as

        // # define M_E  2.7182818284590452354 /* e */
        // # define M_PI 3.1415926535897932384 /* pi */

        /*

    Find out how many signigicant digits can variables of types float, double, and long double hold in them by trying to store the number 0.1111111111111111111111111111 in the variable and then printing out what is stored. The long double number must end with L:

    long double x = 0.1111111111111111111111111111L;

    otherwise it will be considered as double and truncated. Print numbers with format placeholders "%.25g" for float, "%.25lg" for double, "%.25Lg" for long double.
    */

#include "stdio.h"
#include "math.h"
#include "complex.h"

/*
# define M_E  2.7182818284590452354 // e
# define M_PI 3.1415926535897932384 // pi
*/

int main(){
  double complex gamma    =  tgamma(5);
  double complex bessel   =  j1(0.5);
  double complex sqrtm2   =  csqrt(-2);
  double complex ePowI    =  cexp(I);
  double complex ePowIPi  =  cexp(I * M_PI);
  double complex iPowE    =  cpow(I, M_E);
  double complex iPowI    =  cpow(I, I);

  printf("Gamma(5) \t is equal to %g + %gi \n", crealf(gamma)  , cimagf(gamma)  );
  printf("J_1(5)   \t is equal to %g + %gi \n", crealf(bessel) , cimagf(bessel) );
  printf("Sqrt(-2) \t is equal to %g + %gi \n", crealf(sqrtm2) , cimagf(sqrtm2) );
  printf("e^{i}    \t is equal to %g + %gi \n", crealf(ePowI)  , cimagf(ePowI)  );
  printf("e^{i*pi} \t is equal to %g + %gi \n", crealf(ePowIPi), cimagf(ePowIPi));
  printf("i^{e}    \t is equal to %g + %gi \n", crealf(iPowE)  , cimagf(iPowE)  );
  printf("i^{i}    \t is equal to %g + %gi \n", crealf(iPowI)  , cimagf(iPowE)  );

  printf( "\nFind out how many significant digits variables of types float, double, and long double can hold in them by calculating the ratio 1/9 with the corresponding precision and then printing out the result.\n\n");

       float  xf   =  1.f/9 ;
       double xd   =  1./9  ;
  long double xld  =  1.L/9 ;

  printf("Float:       %.25g  \n", xf  );
  printf("Double:      %.25lg \n", xd  );
  printf("Long Double: %.25Lg \n", xld );

  /*
  Output is going to be:

    Find out how many significant digits variables of types float, double, and long double can hold in them by trying to store the number 0.1111111111111111111111111111

    Float:       0.1111111119389533996582031  ---------> Floats       can store 9  decimal pts
    Double:      0.1111111111111111049432054  ---------> Doubles      can store 16 decimal pts
    Long Double: 0.1111111111111111111096053  ---------> Long doubles can store 19 decimal pts

  */

  return 0;
}
