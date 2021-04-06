#include <stdio.h>
#include <time.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#include "jacobi.h"
#include "utilities.h"

int main(int argc, char* argv[]){
    unsigned int seed = time(NULL);
    int dims = 5;

    gsl_matrix* matrix      =  gsl_matrix_alloc(dims, dims);
    gsl_matrix* eigVecMat   =  gsl_matrix_alloc(dims, dims);
    gsl_matrix* eigValMat   =  gsl_matrix_alloc(dims, dims);

    set_data_symmetric(matrix, &seed);
    gsl_matrix_memcpy(eigValMat, matrix);

    print_matrix(dims, matrix, "Symmetric matrix A before diagonalization:");
    jacobiDiag(eigValMat, eigVecMat);

    //
    // gsl_blas_dgemm(Cblas)

    gsl_matrix* tmp             =  gsl_matrix_alloc(dims, dims);
    gsl_matrix* testIdentity    =  gsl_matrix_alloc(dims, dims);
    gsl_matrix* testDiag        =  gsl_matrix_alloc(dims, dims);
    gsl_matrix* testMat         =  gsl_matrix_alloc(dims, dims);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, matrix,    eigVecMat, 0.0, tmp          );
    gsl_blas_dgemm(CblasTrans,   CblasNoTrans, 1.0, eigVecMat, tmp,       0.0, testDiag     );
    gsl_blas_dgemm(CblasTrans,   CblasNoTrans, 1.0, eigVecMat, eigVecMat, 0.0, testIdentity );
    gsl_blas_dgemm(CblasNoTrans, CblasTrans,   1.0, eigValMat, eigVecMat, 0.0, tmp          );
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, eigVecMat, tmp,       0.0, testMat      );


    print_matrix(dims, eigVecMat,    "Matrix of eigenvectors V:     ");
    print_matrix(dims, testIdentity, "Testing that V^T  * V = 1:    ");
    print_matrix(dims, eigValMat,    "Matrix of eigenvalues D:      ");
    print_matrix(dims, testDiag,     "Testing that V^T * A * V = D: ");
    print_matrix(dims, matrix,       "Symmetric matrix A:           ");
    print_matrix(dims, testMat,      "Testing that V * D * V^T = A: ");

    return 0;
}

