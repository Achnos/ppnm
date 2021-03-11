#ifndef HAVE_LINSPLINE_H
#define HAVE_LINSPLINE_H

#include <assert.h>

double linSplineInterp( int numOfPts, double* pts, double* funcVals, double evalPt);

//double linSplineInterp_integrate(gsl_vector x, gsl_vector y, double z);

#endif
