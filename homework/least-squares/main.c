#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_matrix.h>

#include "utilities.h"
#include "input2Array.h"
#include "gramSchmidt.h"
#include "leastSquares.h"

double funcs(int order, double x){
    switch(order){
        case  0: return 1  ; break;
        case  1: return x  ; break;
        default: return NAN;
    }
}
int main(int argc, char* argv[]){

  int numOfPts      =  9;
  int numOfFuncs    =  2;

  char* inputFilename   =  argv[1];
  char* outputFilename  =  argv[2];

  double* xData       =  malloc( numOfPts*sizeof(double) );
  double* yData       =  malloc( numOfPts*sizeof(double) );
  double* yDataTrans  =  malloc( numOfPts*sizeof(double) );
  double* yDev        =  malloc( numOfPts*sizeof(double) );
  double* yDevTrans   =  malloc( numOfPts*sizeof(double) );

  input2Array( xData, yData, inputFilename );
  compute_deviations( numOfPts, yData, yDev);
  log_featureTransform( numOfPts, yData, yDataTrans, yDev, yDevTrans );

  gsl_matrix* dataMat    =  gsl_matrix_alloc(numOfPts,   numOfFuncs);
  gsl_vector* dataVec    =  gsl_vector_alloc(numOfPts              );
  gsl_vector* coeffsVec  =  gsl_vector_alloc(numOfFuncs            );
  gsl_matrix* covMat     =  gsl_matrix_alloc(numOfFuncs, numOfFuncs);


  covMat = leastSquares( numOfPts, numOfFuncs, dataMat, dataVec, coeffsVec, &funcs, xData, yDataTrans, yDevTrans );
  coeffs_exp_featureTransform(coeffsVec, covMat);

  double scale   =  gsl_vector_get(coeffsVec, 0); // a
  double lambda  =  gsl_vector_get(coeffsVec, 1); // -lambda
  write_coeffs(outputFilename, lambda, scale, sqrt(gsl_matrix_get(covMat, 0, 0)), sqrt(gsl_matrix_get(covMat, 1, 1)));

  printf("\n-- Found coefficients from fit: ------------------------------------ \n");
  printf("C_0 (a)      = %lg    +/- %lg   \n", scale,  sqrt(gsl_matrix_get(covMat, 0, 0)));
  printf("C_1 (Lambda) =  %lg +/- %lg \n", lambda, sqrt(gsl_matrix_get(covMat, 1, 1)));

  print_matrix(numOfFuncs, covMat, "The covariance matrix is: ");

  printf("\nThe half-life of ThX is                        \tt_1/2 = %lg +/- %lg days\n", log(2)/(-lambda), log(2)/(sqrt(gsl_matrix_get(covMat, 1, 1))));
  printf("This should be equal to the half-life of 224Ra \tt_1/2 = %lg days\n", 3.66                );


  return 0;
}
