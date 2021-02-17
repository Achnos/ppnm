#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main( int argc, char* argv[]){

	if ( argc < 2){	// Check that we have passed any arguments
		fprintf(stderr, "Error, no arguments were passed.\n"); // Else print to stderr
	}
	else {
		for (int i = 1; i < argc; i++){ // Run through all arguments
			double argX = atof(argv[i]);  // Convert them from strings to doubles
			fprintf(stdout, "%g	%g	%g\n", argX, sin(argX), cos(argX)); // Print them to stdout
		}

		fprintf(stderr, "Program was successful.\n"); // Print to stderr to confirm success.
	}

	return 0;
}
