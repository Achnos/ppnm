#include <assert.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>

#include "gramSchmidt.h"
#include "backsub.h"

void gramSchmidt_decomp( gsl_matrix* matrixToQR, gsl_matrix* inputTriangularMatrix ){
  /*  Method to compute the QR decomposition of a matrix A; A = QR
   *  where A is an n x m matrix, Q is an n x m orthogonal matrix
   *  Q^T * Q = 1_[n x m], and R is an upper triangular matrix
   *
   *  ¤ gsl_matrix* matrixToQR            : Pointer to gsl_matrix A
   *                                        to do QR decomposition on, after
   *                                        returning, holds the matrix Q.
   *  ¤ gsl_matrix* inputTriangularMatrix : Pointer to gsl_matrix R to hold
   *                                        the upper triangular matrix.
   *
   *  Returns: Void. After call return, matrixToQR holds the matrix Q.
   */

  int numOfRows   =  (int) matrixToQR -> size1;
  int numOfCols   =  (int) matrixToQR -> size2;

  assert( numOfRows >= numOfCols );

  // Do modified gram-schmidt orthogonalization
  for (int colId = 0; colId < numOfCols; colId++ ){

    // Begin by normalizing the i'th (colId) column of A (matrixToQR), a_i.
    gsl_vector* col   =   gsl_vector_alloc(numOfRows);
    *col              =   (gsl_matrix_column( matrixToQR, colId )).vector;
    double colNorm    =   gsl_blas_dnrm2(col);                                  //  Compute euclidean R^2-norm

    gsl_matrix_set( inputTriangularMatrix, colId, colId, colNorm );             //  Set diagonal element of triangular matrix equal to this norm


    // Compute the i'th (colId) column of the orthogonal matrix Q
    gsl_vector* orthgnMatCol  =   gsl_vector_alloc(numOfRows);                  //  gsl_vector to hold column

    gsl_vector_memcpy(orthgnMatCol, col);                                       //  Copy contents of col into orthgnMatCol
    gsl_vector_scale(orthgnMatCol, 1.0/colNorm);                                //  Scale orthognMatCol, dividing each element by the norm
    gsl_matrix_set_col(matrixToQR, colId, orthgnMatCol);                        //  Set the i'th (colId) column of A (matrixToQR) equal to the orthogonal column

    // Make the remaining columns of the matrix orthogonal to the new normalized column
    for (int nextColId = colId + 1; nextColId < numOfCols; nextColId++ ){           //  Loop over remaining columns j (nextColId)

      gsl_vector* nextCol   =   gsl_vector_alloc(numOfRows);
      *nextCol              =   (gsl_matrix_column( matrixToQR, nextColId )).vector;

      double triangMatElement;                                                      //  Matrix element of upper triangular matrix, R_ij
      gsl_blas_ddot(orthgnMatCol, nextCol, &triangMatElement);                      //  Compute the matrix element R_ij = q_i^T * a_j
      gsl_matrix_set( inputTriangularMatrix, colId, nextColId, triangMatElement );  //  Set the ij'th element of the upper triangular matrix to be R_ij (triangMatElement)
      gsl_vector* ortColScaled = gsl_vector_alloc(numOfRows);                       //  Vector to hold the scaled i'th (colId) orthognal vector
      gsl_vector_memcpy(ortColScaled, orthgnMatCol);                                //  Copy q_i, the i'th (colId) orthogonal column into this new vector
      gsl_vector_scale(ortColScaled, triangMatElement);                             //  Compute q_i*R_ij
      gsl_vector_sub(nextCol, ortColScaled);                                        //  Compute orthogonal complement by subtracting the component along q_i, q_i*R_ij, from a_j,
                                                                                    //  that is, do exactly a_j = a_j - q_i*R_ij

      gsl_matrix_set_col(matrixToQR, nextColId, nextCol);                           //  Go back and set the j'th (nextColId) column of A (matrixToQR)
                                                                                    //  equal to the column from before. This makes all the reamining columns of
                                                                                    //  A (matrixToQR), from j = i + 1,, orthogonal to the i'th orhogonal column q_i
    }
  }
}


void gramSchmidt_solve( gsl_matrix* orthogonalMatrix  ,
                        gsl_matrix* triangularMatrix  ,
                        gsl_vector* rhsVec            ,
                        gsl_vector* var                 ){

  gsl_blas_dgemv(CblasTrans, 1.0, orthogonalMatrix, rhsVec, 0.0, var);
  backsub(triangularMatrix, var);

}
