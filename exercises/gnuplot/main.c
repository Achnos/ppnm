#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_sf_gamma.h>
#include "myErf.h"
#include "myTGamma.h"

int main( int argc, char* argv[] ){

	if ( argc < 2){	// Check that we have passed any arguments
		fprintf(stderr, "Error, no arguments were passed.\n"); // Else print to stderr
	}
	else {
		FILE* myOutputFileStream_erf 		 =  fopen(argv[1], "w");
		FILE* myOutputFileStream_tgamma  =  fopen(argv[2], "w");

		if ( (myOutputFileStream_erf != NULL) && (myOutputFileStream_tgamma != NULL) ){		 // If input has returned success

			double xMax  =  2			;
			double xMin  =  -xMax	;

			for( double val = xMin; val <= xMax; val += 1.0/8 ){
				fprintf(myOutputFileStream_erf, 	 "%10g %10g %10g %10g\n", val, erf(val), gsl_sf_erf(val), myErf(val) ); // Print the data to myOutputFileStream
			}

			xMax = 4;
			xMin = -xMax;
			double tol = 0.01; // Tolerance for integer comparison
			for ( double val = xMin; val <= xMax; val += 1.0/20 ){
				if ( fabs( (int)val - val ) > tol ){ // This line is important! I'm trying to exclude negative integer values where the gamma function is not well-defined
					fprintf(myOutputFileStream_tgamma, "%10g %10g %10g %10g\n", val, tgamma(val), gsl_sf_gamma(val), myTGamma(val) );
				}
			}
		}
		else { // If we are not successfull, say if there was an error with fscanf()
			fprintf(stderr, "Failed to open file.\n"); // Print this to stderr so we know
			exit(-1); 																	// Terminate program
		}

		fprintf(stderr, "Program was successful.\n"); // Let us know we were successful
	}


	/*
	// Ready data fpr plot of erf(x) for testing of implementation.
	for( double val = xMin; val <= xMax; val += 1.0/8 ){
		printf("%10g %10g %10g %10g\n", val, erf(val), gsl_sf_erf(val), myErf(val));
	}
	*/
	return 0;
}
