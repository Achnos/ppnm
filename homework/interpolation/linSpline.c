#include <assert.h>
#include "linSpline.h"
#include "binarySearch.h"

double linSplineInterp( int numOfPts, double* pts, double* funcVals, double evalPt){
  //  ------------------------------------------------------------------------------
  /*  Do linear spline interpolation on a set of known points (x_i, f(x_i))
      using a binary search method. This asumes the dataset is an ordered array.
      Otherwise use sorting before passing to the function.

      ¤ int       numOfPts  : The number of points to interpolate in.
      ¤ double*   pts       : A pointer to an array of doubles,
                              the known points {x_i}.
      ¤ double*   funcVals  : A pointer to an array of doubles,
                              the corresponding function values {f(x_i)}
      ¤ double    evalPt    : The query point, double values at which to evaluate
                              the interpolant.

      Returns: A double P(evalPt), where P() is the interpolant function             */
  //  ------------------------------------------------------------------------------

  //  We should start by ensuring we have more than one point, and that the
  //  query point, evalPt is within the interval defined by the dataset
  assert( (numOfPts > 1) && (evalPt >= pts[0]) && (evalPt <= pts[numOfPts - 1]) );

  //  Use a binary search to determine which subinterval evalPt is in
  int whichInterval = binarySearch(numOfPts, pts, evalPt);

  double funcValDiff = (funcVals[whichInterval + 1] - funcVals[whichInterval]);
  double ptsDiff = (pts[whichInterval + 1] - pts[whichInterval]);

  assert( ptsDiff > 0 );

  double interpVal  =  funcVals[whichInterval] + funcValDiff / ptsDiff * (evalPt - pts[whichInterval]);
  return interpVal;
}

//double linSplineInterp_integrate(gsl_vector x, gsl_vector y, double z){
  //return 0.0;
//}
