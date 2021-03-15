#include <stdlib.h>
#include <assert.h>

typedef struct { int      numOfPts    ; /* n   */
                 double*  pts         ; /* x's */
                 double*  funcVals    ; /* y's */
                 double*  firstCoeff  ; /* b_i */
                 double*  secondCoeff ; /* c_i */ } quadSpline;

quadSpline* quadSplineAlloc( int numOfPts, double* pts, double* funcVals ){
  quadSpline* s = (quadSpline*)malloc(sizeof(quadSpline));

  // NumOfEqs is the number of needed equations for the quadratic spline interpolation,
  // or the number of intervals to interpolate in (between a numOfPts amount of points)
  numOfEqs        =   numOfPts - 1

  // Fill out field values
  s -> firstCoeff   =  (double*)malloc( numOfEqs*sizeof( double ) );
  s -> secondCoeff  =  (double*)malloc( numOfEqs*sizeof( double ) );
  s -> pts          =  (double*)malloc( numOfPts*sizeof( double ) );
  s -> funcVals     =  (double*)malloc( numOfPts*sizeof( double ) );
  s -> numOfPts     =  numOfPts;

}
