#ifndef HAVE_QUADSPLINE_H
#define HAVE_QUADSPLINE_H

#include <stdlib.h>
#include <assert.h>

typedef struct { int      numOfPts    ; /* n   */
                 double*  pts         ; /* x's */
                 double*  funcVals    ; /* y's */
                 double*  firstCoeff  ; /* b_i */
                 double*  secondCoeff ; /* c_i */ } quadSpline;

quadSpline* quadSplineAlloc( int numOfPts, double* pts, double* funcVals );
double quadSplineEval( quadSpline* spline, double evalPt );
void quadSplineFree( quadSpline* spline );

#endif
