#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "linSpline.h"

void inputToArray(double* XData, double* YData, char* inputFileName );

int main( int argc, char* argv[]) {
  int numOfPts = 10;
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

  free(expXData);
  free(expYData);

  return 0;
}
