#include <stdlib.h>
#include <assert.h>

#include "binarySearch.h"
#include "quadSpline.h"

quadSpline* quadSplineAlloc( int numOfPts, double* pts, double* funcVals ){
  quadSpline* spline = (quadSpline*)malloc(sizeof(quadSpline));

  // NumOfEqs is the number of needed equations for the quadratic spline interpolation,
  // or the number of intervals to interpolate in (between a numOfPts amount of points)
  int numOfEqs  =  numOfPts - 1;

  // Fill out field values
  spline -> firstCoeff   =  (double*)malloc( numOfEqs*sizeof( double ) );
  spline -> secondCoeff  =  (double*)malloc( numOfEqs*sizeof( double ) );
  spline -> pts          =  (double*)malloc( numOfPts*sizeof( double ) );
  spline -> funcVals     =  (double*)malloc( numOfPts*sizeof( double ) );
  spline -> numOfPts     =  numOfPts;

  for ( int it = 0; it < numOfPts; it++ ){
    spline -> pts[it]       =  pts[it];
    spline -> funcVals[it]  =  funcVals[it];
  }

  double ptsDiff[numOfPts - 1];
  double slope[numOfPts - 1];

  for ( int it = 0; it < numOfPts - 1; it++ ){
    ptsDiff[it]  =  pts[it + 1] - pts[it];
    slope[it]    =  (funcVals[it + 1] - funcVals[it]) / ptsDiff[it];
  }

  // Forward recursion
  spline -> secondCoeff[0] = 0;
  for ( int it = 0; it < numOfPts - 2; it++){
    spline -> secondCoeff[it + 1] = (slope[it + 1] - slope[it] - (spline->secondCoeff[it])*ptsDiff[it])/ptsDiff[it + 1];
  }

  // Backward recursion
  spline -> secondCoeff[numOfPts - 2] /=2;
  for ( int it = numOfPts - 3; it >= 0; it--){
    spline -> secondCoeff[it] = (slope[it + 1] - slope[it] - (spline->secondCoeff[it + 1]) * ptsDiff[it + 1]) / ptsDiff[it];
  }

  for ( int it = 0; it < numOfPts - 1; it++ ){
    spline -> firstCoeff[it] = slope[it] - (spline->secondCoeff[it])*ptsDiff[it];
  }

  return spline;
}


double quadSplineEval( quadSpline* spline, double evalPt ){
  assert( (evalPt >=  (spline -> pts[0])) && (evalPt <= (spline -> pts[spline -> numOfPts -1])) );

  //  Use a binary search to determine which subinterval evalPt is in
  int whichInterval = binarySearch(spline -> numOfPts, spline -> pts, evalPt);
  double ptsDiff = evalPt - (spline -> pts[whichInterval]);

  double interpVal = (spline -> funcVals[whichInterval]) + ptsDiff*((spline -> firstCoeff[whichInterval]) + ptsDiff*(spline -> secondCoeff[whichInterval]));
  return interpVal;
}


void quadSplineFree( quadSpline* spline ){
  free(spline -> pts);
  free(spline -> funcVals);
  free(spline -> firstCoeff);
  free(spline -> secondCoeff);
  free(spline);
}
