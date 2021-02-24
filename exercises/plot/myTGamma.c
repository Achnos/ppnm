#include <math.h>
#include "myTGamma.h"


double myTGamma(double val){
  /*
  Implementation of a single precision error function approximation
  (Gergo Nemes, from Wikipedia)

  ¤ Val: The query point at which to evaluate the function; erf(val).

  */

  if( val < 0 ){
    return M_PI / sin( M_PI*val ) / myTGamma( 1 - val );
  }
  if( val < 9 ){
    return myTGamma( val + 1 ) / val;
  }

  double lnGamma  =  val * log( val + 1 / ( 12 * val - 1 /(val*10) ) ) - val + log( 2 * M_PI / val ) / 2;
  double result   =  exp(lnGamma);

  return result;
}
