#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

#define rand (double)rand()/RAND_MAX

void vector_print( char* string, gsl_vector* vector){
	printf("%s\n", string);
	for(int iter = 0; iter < vector->size; iter++){
		printf("%10g ", gsl_vector_get(vector, iter));
	}
}

int main( ) {
	int numOfRows = 3;
	int numOfCols = 3;

	gsl_matrix* matrix_A = gsl_matrix_alloc(numOfRows, numOfCols);
	gsl_matrix* matrix_A_copy = gsl_matrix_alloc(numOfRows, numOfCols);
	gsl_vector* vector_b = gsl_vector_alloc(numOfRows);
	gsl_vector* vector_x = gsl_vector_alloc(numOfRows);
	gsl_vector* vector_y = gsl_vector_calloc(numOfRows);

	for (int iter_X = 0; iter_X < matrix_A->size1; iter_X++ ){
		for(int iter_Y = 0; iter_Y < matrix_A->size2; iter_Y++){
			double matrixElement_A_XY = rand;
			gsl_matrix_set(matrix_A, iter_X, iter_Y, matrixElement_A_XY);
		}
	}
	gsl_matrix_memcpy(matrix_A_copy, matrix_A);

	for (int iter = 0; iter < vector_b->size; iter++){
		double element_b = rand;
		gsl_vector_set(vector_b, iter, element_b);
	}

	gsl_linalg_HH_solve(matrix_A_copy, vector_b, vector_x);
	gsl_blas_dgemv(CblasNoTrans, 1, matrix_A, vector_x, 0, vector_y);

	vector_print("Righthand side b = ", vector_b);
	printf("\n");
	vector_print("Check: A*x should be equal to b...:", vector_y);
	printf("\n");

	gsl_matrix_free(matrix_A);
	gsl_vector_free(vector_b);
	gsl_vector_free(vector_x);

	return 0;
}
