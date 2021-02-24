#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_sf_gamma.h>
#include "myErf.h"
#include "myTGamma.h"
#include "myComplexGamma.h"

int main( int argc, char* argv[] ){

	if ( argc < 2){	// Check that we have passed any arguments
		fprintf(stderr, "Error, no arguments were passed.\n"); // Else print to stderr
	}
	else {
		FILE* myOutputFileStream_erf 		 =  fopen(argv[1], "w"); // Output stream for values of the true error function
		FILE* myOutputFileStream_tgamma  =  fopen(argv[2], "w"); // Output stream for values of the true gamma function
		FILE* myOutputFileStream_lgamma  =  fopen(argv[3], "w"); // Output stream for values of the logarithm of the true gamma function
		FILE* myOutputFileStream_cgamma  =  fopen(argv[4], "w"); // Output stream for values of the complex valued gamma function

		if ( (myOutputFileStream_erf != NULL) && (myOutputFileStream_tgamma != NULL) ){		 // If input has returned success

			// Plot of erf(x)
			// ---------------------------------------------------------------------------------------------------------------------------------------------------------
			double xMax  =  2			;
			double xMin  =  -xMax	;

			for( double val = xMin; val <= xMax; val += 1.0/8 ){
				fprintf(myOutputFileStream_erf, 	 "%10g %10g %10g %10g\n", val, erf(val), gsl_sf_erf(val), myErf(val) ); // Print the data to myOutputFileStream
			}



			// Plot of gamma(x)
			// ---------------------------------------------------------------------------------------------------------------------------------------------------------
			xMax = 4;
			xMin = -xMax;
			double tol = 0.01; // Tolerance for integer comparison
			for ( double val = xMin; val <= xMax; val += 1.0/20 ){
				if ( fabs( (int)val - val ) > tol ){ // This line is important! I'm trying to exclude negative integer values where the gamma function is not well-defined
					fprintf(myOutputFileStream_tgamma, "%10g %10g %10g %10g\n", val, tgamma(val), gsl_sf_gamma(val), myTGamma(val) );
				}
			}


			// Plot of lgamma(x)
			// ---------------------------------------------------------------------------------------------------------------------------------------------------------
			xMin = 0.5;
			xMax = 4;
			for (double val = xMin; val <= xMax; val += 1.0/20){
				fprintf(myOutputFileStream_lgamma, "%10g %10g %10g %10g\n", val, lgamma(val), gsl_sf_lngamma(val), log(myTGamma(val)));
			}


			// Plot of cgamma(x)
			// ---------------------------------------------------------------------------------------------------------------------------------------------------------
			double realMin = -4.2;
			double realMax = 4.2;
			double imagMin = -4.2;
			double imagMax = 4.2;

			for (double realPart = realMin; realPart < realMax; realPart += 1.0/40){
				for(double imagPart = imagMin; imagPart < imagMax; imagPart += 1.0/40){
					fprintf(myOutputFileStream_cgamma, "%10g %10g %10g\n", realPart, imagPart, fmin( 6, cabs( myComplexGamma(realPart + imagPart*I) )) );
					// Here i have used fmin( 6, cabs( myComplexGamma(realPart + imagPart*I) )), simply to ensure, that if cabs(myComplexGamma()) is greater than 6,
					// like in its divergences, we only plot up to a value of 6 like in the wiki article.
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
