#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gramSchmidt.h"
#include "utilities.h"
#include "diffClock.h"

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

int main (int argc, char* argv[]){
  if (argc < 2){
    fprintf(stdout, "No input arguments taken.");
    exit(-1);
  }
  unsigned int seed   =   time(NULL) ;

  int numOfRows = 5;
	int numOfCols = 4;

  gsl_matrix* ortgnlMatTall    =  gsl_matrix_alloc(numOfRows, numOfCols);
  gsl_matrix* ortgnlMatSquare  =  gsl_matrix_alloc(numOfRows, numOfRows);
  gsl_matrix* testMatTall      =  gsl_matrix_alloc(numOfRows, numOfCols);
  gsl_matrix* testMatSquare    =  gsl_matrix_alloc(numOfRows, numOfRows);
  gsl_matrix* triangMatTall    =  gsl_matrix_alloc(numOfCols, numOfCols);
  gsl_matrix* triangMatSquare  =  gsl_matrix_alloc(numOfRows, numOfRows);
  gsl_vector* RHSvecTall       =  gsl_vector_alloc(numOfRows           );
  gsl_vector* RHSvecSquare     =  gsl_vector_alloc(numOfRows           );
  gsl_vector* varVec           =  gsl_vector_alloc(numOfRows           );
  gsl_vector* varVecTall       =  gsl_vector_alloc(numOfCols           );
  gsl_matrix* checkOrtgnl      =  gsl_matrix_alloc(numOfCols, numOfCols);
  gsl_matrix* checkRes         =  gsl_matrix_alloc(numOfRows, numOfCols);
  gsl_vector* checkRHS         =  gsl_vector_alloc(numOfRows           );
  gsl_matrix* inverseMatrix    =  gsl_matrix_alloc(numOfRows, numOfRows);
  gsl_matrix* checkInverse     =  gsl_matrix_alloc(numOfRows, numOfRows);

	set_data(testMatTall, RHSvecTall, &seed);
  set_data(testMatSquare, RHSvecSquare, &seed);
  gsl_matrix_memcpy(ortgnlMatTall, testMatTall);

  gramSchmidt_decomp(ortgnlMatTall, triangMatTall);

  print_matrix(numOfCols, triangMatTall, "Triangular matrix:");

  gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, ortgnlMatTall, ortgnlMatTall, 0, checkOrtgnl);
  print_matrix(numOfCols, checkOrtgnl, "Q^T * Q:");

  gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, ortgnlMatTall, triangMatTall, 0, checkRes);
  print_matrix(numOfRows, checkRes, "QR :");
  print_matrix(numOfRows, testMatTall, "Tall test matrix:");

  print_matrix(numOfRows, testMatSquare, "Square test matrix for solver:");
  gsl_matrix_memcpy(ortgnlMatSquare, testMatSquare);
  gramSchmidt_decomp(ortgnlMatSquare, triangMatSquare);
  gramSchmidt_solve(ortgnlMatSquare, triangMatSquare, RHSvecSquare, varVec);
  gsl_blas_dgemv(CblasNoTrans, 1, testMatSquare, varVec, 0, checkRHS);
  vector_print( "\nFrom gramSchmidt_solve             Ax = ", checkRHS);
  vector_print( "\nShould be equal to right-hand side  b = ", RHSvecSquare);

  gramSchmidt_inverse(ortgnlMatSquare, triangMatSquare, inverseMatrix);
  gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, testMatSquare, inverseMatrix, 0, checkInverse);
  print_matrix(numOfRows, checkInverse, "\nChecking A*A^{-1} = I :");

  gsl_matrix_free (ortgnlMatTall);
  gsl_matrix_free (ortgnlMatSquare);
	gsl_matrix_free (testMatTall);
	gsl_matrix_free (testMatSquare);
	gsl_matrix_free (triangMatTall);
	gsl_matrix_free (triangMatSquare);
	gsl_vector_free (RHSvecTall);
	gsl_vector_free (RHSvecSquare);
	gsl_vector_free (varVec);
  gsl_matrix_free (checkOrtgnl);
  gsl_matrix_free (checkRes);
	gsl_vector_free (checkRHS);
  gsl_matrix_free (inverseMatrix);
  gsl_matrix_free (checkInverse);

  int numOfReps = 1e2;
  double scale = 0;
  int startRep = 10;
  FILE* myOutputFileStream = fopen(argv[1], "w");
  for (int rep = startRep; rep < numOfReps; rep++){
    numOfRows = rep;

    gsl_matrix* my_ortg    =  gsl_matrix_alloc(numOfRows, numOfRows);
    gsl_matrix* my_triang  =  gsl_matrix_alloc(numOfRows, numOfRows);
    gsl_vector* my_vecTmp  =  gsl_vector_alloc(numOfRows);
    gsl_matrix* gsl_ortg    =  gsl_matrix_alloc(numOfRows, numOfRows);
    gsl_matrix* gsl_triang  =  gsl_matrix_alloc(numOfRows, numOfRows);

    set_data(my_ortg, my_vecTmp , &seed);
    set_data(gsl_ortg, my_vecTmp , &seed);

    clock_t my_begin  = clock(); // We define variables to hold the times used for timing the computations.
    clock_t my_end    = clock(); // These are defined in <time.h> and used in diffClock(). It is my own implementation.
    clock_t gsl_begin = clock();
    clock_t gsl_end   = clock();

    my_begin = clock(); // Begin timing

    // time something....
    gramSchmidt_decomp(my_ortg, my_triang);

    my_end = clock(); // end timing
    gsl_begin = clock();
    gsl_linalg_QR_decomp(gsl_ortg, my_vecTmp);
    gsl_end = clock();

    if (rep == startRep){
      scale = (double)(diffClock(my_end, my_begin));
    }

    fprintf(myOutputFileStream, "%d\t%g\t%g\t%g\n", numOfRows, (double)(diffClock(my_end, my_begin)), pow(((double)numOfRows)/startRep, 3)*scale, (double)(diffClock(gsl_end, gsl_begin)));

    gsl_matrix_free(my_ortg);
    gsl_matrix_free(my_triang);
  }
  fclose(myOutputFileStream);

  return 0;
}
