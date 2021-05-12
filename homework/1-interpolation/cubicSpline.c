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

      All equations are based on
      [Fedorov, D.V.. Introduction to Numerical methods, 2021]

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

  // Fill field values from input data
  for( int it = 0; it < numOfPts; it++ ){
    spline -> pts[it]       =  pts[it];
    spline -> funcVals[it]  =  funcVals[it];
  }

  // Set up slope array (p_i and h_i) variables
  double ptsDiff[numOfEqs];
  double slope[numOfEqs];
  for(int it = 0; it < numOfEqs; it++){
    ptsDiff[it] = pts[it + 1] - pts[it];
    assert( ptsDiff[it] > 0 );

    slope[it] = (funcVals[it + 1] - funcVals[it]) / ptsDiff[it];
  }

  /*
    Set up the tridiagonal system of equations
    where D are the diagonal elements, Q the above diagonal,
    and B the right hand side vector elements. The system
    of equations is of the form

      [ D_1, Q_1,  0,  0, ... ]   ( b_1 )     ( B_1 )
      [  1 , D_2, Q_2, 0, ... ]   ( .   )     (  .  )
      [  .    .    .   .  .   ] * ( .   )  =  (  .  )
      [ ...  ...   0,  1, D_n ]   ( .   )     ( B_n )

     [Fedorov, D.V.. INM, 2021]
  */

  double LHS_matrixDiag[numOfPts];
  double LHS_matrixAboveDiag[numOfPts - 1];
  double RHS_vec[numOfPts];

  /* Starting recursion based on eq. (21) from [INM] */
  LHS_matrixDiag[0]       = 2             ;
  LHS_matrixAboveDiag[0]  = 1             ;
  RHS_vec[0]              = 3 * slope[0]  ;

  /*  Fill arrys according to eq (21) from [INM] */
  for( int it = 0; it < numOfEqs - 1; it++ ) {
    LHS_matrixDiag[it + 1]        =  2 * ptsDiff[it] / ptsDiff[it + 1] + 2;
    LHS_matrixAboveDiag[it + 1]   =      ptsDiff[it] / ptsDiff[it + 1];
    RHS_vec[it + 1]               =  3 * (slope[it] + slope[it + 1] * ptsDiff[it] / ptsDiff[it + 1]);
  }
  LHS_matrixDiag[numOfPts - 1]  =  2                      ;
  RHS_vec[numOfPts - 1]         =  3 * slope[numOfPts - 2];

  /* Perform Gauss elimination to reduce the LHS matrix
     using eq (29) from [INM]                            */
  for(int it = 1; it < numOfPts; it++){
    LHS_matrixDiag[it]  -=  LHS_matrixAboveDiag[it - 1]  / LHS_matrixDiag[it - 1];
    RHS_vec[it]         -=  RHS_vec[it - 1]              / LHS_matrixDiag[it - 1];
  }

  /* Do backwards substitution to find the b_i coefficient
     (firstCoeff[i]) using eq (29) from [INM]              */
  spline -> firstCoeff[numOfEqs] = RHS_vec[numOfPts - 1] / LHS_matrixDiag[numOfPts - 1];
  for( int it = numOfEqs - 1; it >= 0; it--){
    spline -> firstCoeff[it] = (RHS_vec[it] - LHS_matrixAboveDiag[it]*(spline -> firstCoeff[it + 1])) / LHS_matrixDiag[it];
  }

  /* Since we know how the b_i's, c_i's and d_i's relate we may now compute the
     remaining coefficients using eq (20) from [INM]                            */
  for( int it = 0; it < numOfEqs; it++ ){
    spline -> secondCoeff[it]  =  (-2 * (spline -> firstCoeff[it]) - (spline -> firstCoeff[it + 1]) + 3*slope[it]) / ptsDiff[it];
    spline -> thirdCoeff[it]   =  (     (spline -> firstCoeff[it]) + (spline -> firstCoeff[it + 1]) - 2*slope[it]) / ptsDiff[it] /ptsDiff[it];
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
