#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "utilities.h"
#include "cubicSpline.h"


cubicSpline* cubicSpline_init( int numOfPts, double* pts, double* funcVals ){
  //  ------------------------------------------------------------------------------
  /*  cubicSpline constructor to initiallize a cubic spline from a cubicSpline
      struct, by filling the various field values from respective function inputs.

      ¤ int       numOfPts  : The number of points to interpolate in.
      ¤ double*   pts       : A pointer to an array of doubles,
                              the known points {x_i}.
      ¤ double*   funcVals  : A pointer to an array of doubles,
                              the corresponding function values {f(x_i)}

      Returns: An inittialized cubicSpline* struct                                    */
  //  ------------------------------------------------------------------------------

  int numOfEqs           =  numOfPts - 1;
  cubicSpline* spline    =  (cubicSpline*)malloc( sizeof(cubicSpline) );
  spline -> pts          =  (double*)malloc( numOfPts*sizeof(double) );
  spline -> funcVals     =  (double*)malloc( numOfPts*sizeof(double) );
  spline -> firstCoeff   =  (double*)malloc( numOfPts*sizeof(double) );
  spline -> secondCoeff  =  (double*)malloc( numOfEqs*sizeof(double) );
  spline -> thirdCoeff   =  (double*)malloc( numOfEqs*sizeof(double) );
  spline -> numOfPts     =  numOfPts;

  for( int it = 0; it < numOfPts; it++ ){
    spline -> pts[it]       =  pts[it];
    spline -> funcVals[it]  =  funcVals[it];
  }

  double ptsDiff[numOfEqs];
  double slope[numOfEqs];
  for(int it = 0; it < numOfEqs; it++){
    ptsDiff[it] = pts[it + 1] - pts[it];
    assert( ptsDiff[it] > 0 );

    slope[it] = (funcVals[it + 1] - funcVals[it]) / ptsDiff[it];
  }

  double D[numOfPts    ];
  double Q[numOfPts - 1];
  double B[numOfPts    ];

  D[0] = 2            ;
  Q[0] = 1            ;
  B[0] = 3 * slope[0] ;
  for( int it = 0; it < numOfEqs - 1; it++ ) {
    D[it + 1] = 2 * ptsDiff[it] / ptsDiff[it + 1] + 2;
    Q[it + 1] =     ptsDiff[it] / ptsDiff[it + 1];
    B[it + 1] = 3 * (slope[it] + slope[it + 1] * ptsDiff[it] / ptsDiff[it + 1]);
  }
  D[numOfPts - 1] = 2                      ;
  B[numOfPts - 1] = 3 * slope[numOfPts - 2];

  for(int it = 1; it < numOfPts; it++){
    D[it] -= Q[it - 1] / D[it - 1];
    B[it] -= B[it - 1] / D[it - 1];
  }
  spline -> firstCoeff[numOfEqs] = B[numOfPts - 1] / D[numOfPts - 1];
  for( int it = numOfEqs - 1; it >= 0; it--){
    spline -> firstCoeff[it] = (B[it] - Q[it]*(spline -> firstCoeff[it + 1])) / D[it];
  }
  for( int it = 0; it < numOfEqs; it++ ){
    spline -> secondCoeff[it]  =  (-2 * (spline -> firstCoeff[it]) - (spline -> firstCoeff[it + 1]) + 3*slope[it]) / ptsDiff[it];
    spline -> thirdCoeff[it]   =  ((spline -> firstCoeff[it]) + (spline -> firstCoeff[it + 1]) - 2*slope[it]) / ptsDiff[it] /ptsDiff[it];
  }

  return spline;
}

double cubicSpline_eval( cubicSpline* spline, double evalPt ){
  //  ------------------------------------------------------------------------------
  /*  Do cubic spline interpolation, using an already initiallized cubicSpline*
      struct. The cubicSpline* struct may be initiallized using cubicSpline_init().
      The cubic interpolant is computed at the evaluation pt. evalPt.

      ¤ cubicSpline*      : A pointer to an initiallized cubicSpline struct,
                            initiallized using cubicSpline_init()
      ¤ double*   evalPt  : Point at which to evaluate interpolant at

      Returns: The function value of the interpolant at evalPt.                      */
  //  ------------------------------------------------------------------------------
  assert( (evalPt >=  (spline -> pts[0])) && (evalPt <= (spline -> pts[spline -> numOfPts -1])) );

  //  Use a binary search to determine which subinterval evalPt is in
  int whichInterval  =  binarySearch(spline -> numOfPts, spline -> pts, evalPt);

  double ptsDiff     =  evalPt  - ( spline -> pts[whichInterval]                      );
  double thirdDiff   =  ptsDiff * ( spline -> thirdCoeff[whichInterval]               );
  double secondDiff  =  ptsDiff * ((spline -> secondCoeff[whichInterval]) + thirdDiff );
  double firstDiff   =  ptsDiff * ((spline -> firstCoeff[whichInterval])  + secondDiff);

  double interpVal = (spline -> funcVals[whichInterval]) + firstDiff ;
  return interpVal;
}

double cubicSpline_eval_deriv( cubicSpline* spline, double evalPt ){
  //  ------------------------------------------------------------------------------
  /*  Do cubic spline interpolation of derivative, using an already initiallized
      cubicSpline* struct. The cubicSpline* struct may be initiallized using
      cubicSpline_init(). The cubic interpolant derivative is computed at the evaluation
      point evalPt.

      ¤ cubicSpline*      : A pointer to an initiallized quadSpline struct,
                            initiallized using quadSpline_init()
      ¤ double*   evalPt  : Point at which to evaluate interpolant at

      Returns: The function value of the interpolant derivative at evalPt.                      */
  //  ------------------------------------------------------------------------------
  assert( (evalPt >=  (spline -> pts[0])) && (evalPt <= (spline -> pts[spline -> numOfPts -1])) );

  //  Use a binary search to determine which subinterval evalPt is in
  int whichInterval = binarySearch(spline -> numOfPts, spline -> pts, evalPt);
  double ptsDiff = evalPt - (spline -> pts[whichInterval]);

  double interpVal = (spline -> firstCoeff[whichInterval]) + 2*ptsDiff*(spline -> secondCoeff[whichInterval]) + 3*ptsDiff*ptsDiff*(spline -> thirdCoeff[whichInterval]) ;
  return interpVal;
}


double cubicSpline_eval_integ( cubicSpline* spline, double evalPt ){
  //  ------------------------------------------------------------------------------
  /*  Integrate cubic spline interpolation from a set of known points (x_i, f(x_i))
      using a binary search method. This asumes the dataset is an ordered array.
      Otherwise use sorting before passing to the function.

        ¤ cubicSpline*       : A pointer to an initiallized quadSpline struct,
                                  initiallized using quadSpline_init()
        ¤ double*   evalPt  : Point at which to evaluate interpolant at

      Returns: A double P(evalPt), where P() is the interpolant function integrated  */
  //  ------------------------------------------------------------------------------

  //  Use a binary search to determine which subinterval evalPt is in
  int whichInterval   =  binarySearch((spline -> numOfPts), (spline -> pts), evalPt);

  double integral = 0;
  double ptsDiff;
  for ( int Id = 0; Id <= whichInterval; Id++ ){

    if ( Id < whichInterval ){
      ptsDiff = ((spline -> pts[Id + 1]) - (spline -> pts[Id]));
    }
    else {
      ptsDiff = ( evalPt - (spline -> pts[Id]));
    }
    integral += (spline -> funcVals[Id]) * ptsDiff + (spline -> firstCoeff[Id]) * ptsDiff * ptsDiff / 2 + (spline -> secondCoeff[Id]) * ptsDiff * ptsDiff * ptsDiff / 3 + (spline -> thirdCoeff[Id]) * ptsDiff * ptsDiff * ptsDiff * ptsDiff/ 4;
  }

  return integral;
}


void cubicSpline_free(cubicSpline* spline){
  //  ------------------------------------------------------------------------------
  /*  cubicSpline destructor, to free allocated memory.

      ¤ cubicSpline*       : A pointer to an initiallized cubicSpline struct,
                              initiallized using cubicSpline_init()                  */
  //  ------------------------------------------------------------------------------
  free(spline -> pts);
  free(spline -> funcVals);
  free(spline -> firstCoeff);
  free(spline -> secondCoeff);
  free(spline -> thirdCoeff);
  free(spline);
}
