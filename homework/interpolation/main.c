#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

#include "linSpline.h"
#include "gslIntFunc.h"

void inputToArray(double* XData, double* YData, char* inputFileName );

int main( int argc, char* argv[]) {
  int numOfPts = 100;
  int numOfQueryPts = (int)1e3;

  double* expXData = malloc( numOfPts*sizeof(double) );
  double* expYData = malloc( numOfPts*sizeof(double) );

  if ( argc < 2){	// Check that we have passed any arguments
    fprintf(stderr, "Error, no arguments were passed.\n"); // Else print to stderr
  }
  else {
    char* inputFileName = argv[1];
	  inputToArray( expXData, expYData, inputFileName );
  }

  double interpValTmp = 0;

  FILE* myOutputFileStream = fopen(argv[2], "w");

  double resolution = fabs(expXData[numOfPts-1] - expXData[0]) / numOfQueryPts;
  for ( double evalPt = expXData[0]; evalPt < expXData[numOfPts]; evalPt += resolution ){
    interpValTmp = linSplineInterp( numOfPts, expXData, expYData, evalPt);
    fprintf(myOutputFileStream, "%g\t%g\n", evalPt, interpValTmp);
  }

  double lowerLimit       =   expXData[0] ;
  double upperLimit       =   2*M_PI      ;
  double absError         =   1e-6        ;
  double relError         =   1e-6        ;
  size_t iterationLimit   =   999         ;

  double integralVal = linSplineInterp_integrate( numOfPts, expXData, expYData, upperLimit );

  gsl_function gslFuncExp;

  gslFuncExp.function  =  &exp;
  gslFuncExp.params    =  NULL;
  double integralValComp = integratedFunction( lowerLimit, upperLimit, &gslFuncExp, absError, relError, iterationLimit );

  printf("The integrated interpolant up to 2pi is = %g\n", integralVal);
  printf("Integrating exp(x) from 0 to 2pi using GSL = %g\n", integralValComp);

  free(expXData);
  free(expYData);

  return 0;
}
