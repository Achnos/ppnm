#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_matrix.h>

#include "input2Array.h"
#include "gramSchmidt.h"

double funcs(int order, double x){
	switch(order){
		case  0: return 1  ; break;
		case  1: return x  ; break;
		case  2: return x*x; break;
		default: return NAN;
	}
}

void compute_deviations(int numOfPts, double* yData, double* yDev){
  for (int dev = 0; dev < numOfPts; dev++){
    yDev[dev] = yData[dev]/20;
  }
}

void set_data(int numOfPts        ,
              int numOfFuncs      ,
              gsl_matrix* dataMat ,
              gsl_vector* dataVec ,
              double* xData       ,
              double* yData       ,
              double* yDev         ){
  for (int row = 0; row < numOfPts; row++){
    for (int col = 0; col < numOfFuncs; col++){
      gsl_matrix_set(dataMat, row, col, funcs(col, xData[row])/yDev[row]);
    }
    gsl_vector_set(dataVec, row, yData[row]/yDev[row]);
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

  double* xData  =  malloc( numOfPts*sizeof(double) );
  double* yData  =  malloc( numOfPts*sizeof(double) );
  double* yDev   =  malloc( numOfPts*sizeof(double) );

	input2Array( xData, yData, inputFilename );
  compute_deviations( numOfPts, yData, yDev);

  gsl_matrix* dataMat    =  gsl_matrix_alloc(numOfPts,   numOfFuncs);
  gsl_matrix* ortgMat    =  gsl_matrix_alloc(numOfPts,   numOfFuncs);
  gsl_matrix* triangMat  =  gsl_matrix_alloc(numOfFuncs, numOfFuncs);
  gsl_vector* dataVec    =  gsl_vector_alloc(numOfPts              );
  gsl_vector* coeffsVec  =  gsl_vector_alloc(numOfFuncs            );

  set_data(numOfPts, numOfFuncs, dataMat, dataVec, xData, yData, yDev);
  gsl_matrix_memcpy(ortgMat, dataMat);
  gramSchmidt_decomp(ortgMat, triangMat);
  gramSchmidt_solve( ortgMat, triangMat, dataVec, coeffsVec);

  return 0;
}
