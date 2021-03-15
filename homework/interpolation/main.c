#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_interp.h>

#include "linSpline.h"
#include "gslIntFunc.h"

void inputToArray(double* XData, double* YData, char* inputFileName );

int main( int argc, char* argv[]) {
  int numOfPts = 20;
  int numOfQueryPts = (int)1e3;

  double* xData     =  malloc( numOfPts*sizeof(double) );
  double* yData     =  malloc( numOfPts*sizeof(double) );

  if ( argc < 2){	// Check that we have passed any arguments
    fprintf(stderr, "Error, no arguments were passed.\n"); // Else print to stderr
  }
  else {
    char* inputFileName = argv[1];
	  inputToArray( xData, yData, inputFileName );
  }


  double interpValTmp        =  0;
  double interpValGSLTmp     =  0;
  double interpValIntTmp     =  0;
  double interpValIntGSLTmp  =  0;

  double lowerLimit       =   xData[0] ;
  double upperLimit       =   11       ;
  double absError         =   1e-6     ;
  double relError         =   1e-6     ;
  size_t iterationLimit   =   999      ;


  gsl_interp* GSLinterpLin = gsl_interp_alloc(gsl_interp_linear, numOfPts);
  gsl_interp_init(GSLinterpLin, xData, yData, numOfPts);

  FILE* myOutputFileStream = fopen(argv[2], "w");

  double resolution = fabs(xData[numOfPts-1] - xData[0]) / numOfQueryPts;
  for ( double evalPt = xData[0]; evalPt < xData[numOfPts]; evalPt += resolution ){

    interpValTmp        =  linSplineInterp(        numOfPts,       xData, yData,           evalPt       );
    interpValGSLTmp     =  gsl_interp_eval(        GSLinterpLin,   xData, yData,           evalPt, NULL );
    interpValIntTmp     =  linSplineIntInterp(     numOfPts,       xData, yData,           evalPt       );
    interpValIntGSLTmp  =  gsl_interp_eval_integ(  GSLinterpLin,   xData, yData, xData[0], evalPt, NULL );

    fprintf(myOutputFileStream, "%g\t%g\t%g\t%g\t%g\n", evalPt, interpValTmp, interpValGSLTmp, interpValIntTmp, interpValIntGSLTmp);
  }

  double integralVal = linSplineIntInterp( numOfPts, xData, yData, upperLimit );

  gsl_function gslFuncCos;

  gslFuncCos.function    =  &cos;
  gslFuncCos.params      =  NULL;
  double integralValComp = integratedFunction( lowerLimit, upperLimit, &gslFuncCos, absError, relError, iterationLimit );

  printf("The integral of the interpolant            from x[0] = %g to z = %g is         = %g\n", lowerLimit, upperLimit, integralVal);
  printf("The integral of cos(x) (from math.h)       from        %g to     %g using GSL  = %g\n", lowerLimit, upperLimit, integralValComp);
  printf("The integral of cos(x) (from WolframAlpha) from        %g to     %g            = -0.99999\n", lowerLimit, upperLimit );

  gsl_interp_free(GSLinterpLin);
  return 0;
}
