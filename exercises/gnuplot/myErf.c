#include <math.h>
#include "myErf.h"

double myErf( double val ){
	/*
	Implementation of a single precision error function approximation
	(Abramowitz and Stegun, from Wikipedia)

	¤ Val: The query point at which to evaluate the function; erf(val).

	*/

	if( val < 0 ) {
		return - myErf( -val );
	}

	double coeffs[]  =  { 0.254829592, -0.284496736, 1.421413741, -1.453152027, 1.061405429 };
	double scale 		 =  1 / ( 1 + 0.3275911*val );
	double coeffSum  =  scale * ( coeffs[0] + scale*( coeffs[1] + scale * ( coeffs[2] + scale * ( coeffs[3] + scale * coeffs[4] ) ) ) );
	double funcVal   =  1 - coeffSum * exp( -val*val );

	return funcVal;
}
