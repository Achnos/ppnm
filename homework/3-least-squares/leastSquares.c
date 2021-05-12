//
// Created by marc on 3/24/21.
//
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "leastSquares.h"
#include "gramSchmidt.h"
#include "utilities.h"

void set_data(int         numOfPts, int         numOfFuncs, double (*fitFuncs)(int, double),
              gsl_matrix* dataMat , gsl_vector* dataVec   ,
              double*     xData   , double*     yData     , double* yDev                   ){
    for (int row = 0; row < numOfPts; row++){
        for (int col = 0; col < numOfFuncs; col++){
            gsl_matrix_set(dataMat, row, col, (fitFuncs(col, xData[row]))/yDev[row]);
        }
        gsl_vector_set(dataVec, row, yData[row]/yDev[row]);
    }
}

gsl_matrix* leastSquares(  int         numOfPts,   int         numOfFuncs,
                           gsl_matrix* dataMat,    gsl_vector* dataVec,
                           gsl_vector* coeffsVec,  double      (*fitFuncs)(int, double),
                           double*     xData    ,  double*     yData                   ,  double* yDev  ){

    set_data(numOfPts, numOfFuncs, fitFuncs, dataMat, dataVec, xData, yData, yDev);

    gsl_matrix* ortgMat           =  gsl_matrix_alloc(numOfPts,   numOfFuncs); // Orthogonal matrix
    gsl_matrix* triangMat         =  gsl_matrix_alloc(numOfFuncs, numOfFuncs); // Upper triangular matrix
    gsl_matrix* triangMatInverse  =  gsl_matrix_alloc(numOfFuncs, numOfFuncs);
    gsl_vector* tmpRes            =  gsl_vector_alloc(numOfFuncs            );

    gsl_matrix_memcpy(ortgMat, dataMat);
    gramSchmidt_decomp(ortgMat, triangMat);
    gramSchmidt_solve(ortgMat, triangMat, dataVec, coeffsVec);

    // - Compute covariance matrix ---------
    gsl_matrix* covMat  =  gsl_matrix_alloc(numOfFuncs, numOfFuncs);
    gramSchmidt_inverseTriang( triangMat, triangMatInverse );
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1, triangMatInverse, triangMatInverse,  0, covMat);

    return covMat;
}