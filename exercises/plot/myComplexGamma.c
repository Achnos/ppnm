#include <math.h>
#include "myTGamma.h"
#include <complex.h>

double complex myComplexGamma(double complex num){
  /*
  Implementation of a single precision error function approximation
  (Gergo Nemes, from Wikipedia)

  ¤ Val: The query point at which to evaluate the function; erf(val).

  */

  if( creal(num) < 0 ){
    return M_PI / csin( M_PI*num ) / myComplexGamma( 1 - num );
  }
  if( creal(num) < 9 ){
    return myComplexGamma( num + 1 ) / num;
  }

  double complex lnGamma  =  num * clog( num + 1 / ( 12 * num - 1 /(num*10) ) ) - num + clog( 2 * M_PI / num ) / 2;
  double complex result   =  cexp(lnGamma);

  return result;
}
