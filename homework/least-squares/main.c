#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_matrix.h>

#include "input2Array.h"
#include "gramSchmidt.h"
#include "leastSquares.h"

void compute_deviations(int numOfPts, double* yData, double* yDev){
    for (int dev = 0; dev < numOfPts; dev++){
        yDev[dev] = yData[dev]/20;
    }
}

void log_featureTransform( int numOfPts, double* yData, double* yDataTrans, double* yDev, double* yDevTrans ){
    for (int id = 0; id < numOfPts; id++ ){
        yDataTrans[id]  =  log(yData[id]);
        yDevTrans[id]        =  yDev[id] / yData[id];
    }
}

double funcs(int order, double x){
	switch(order){
		case  0: return 1  ; break;
		case  1: return x  ; break;
		case  2: return x*x; break;
		default: return NAN;
	}
}


int main (int argc, char* argv[]){
  if ( argc < 2){	// Check that we have passed any arguments
    fprintf(stderr, "Error, no arguments were passed.\n"); // Else print to stderr
    exit(-1);
  }

  // __ Hyperparameters ________________________________________________________
  int numOfPts      =  10;
  int numOfFuncs    =  3;
  int numOfSamples  =  (int)1e3;

  char* inputFilename  =  argv[1];
  FILE* outFileStream  =  fopen(argv[2], "w");

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

  leastSquares( numOfPts, numOfFuncs, dataMat, dataVec, coeffsVec, &funcs, xData, yDataTrans, yDevTrans );

  return 0;
}
