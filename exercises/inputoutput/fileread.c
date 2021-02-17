#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main( int argc, char* argv[]){

	if ( argc < 2){	// Check that we have passed any arguments
		fprintf(stderr, "Error, no arguments were passed.\n"); // Else print to stderr
	}
	else {
		int input = 1; 			// Input will receive the return value from fscanf
		int argX;						// Variable to hold the data from stdin
		
		FILE* myInputFileStream  = fopen(argv[1], "r");
		FILE* myOutputFileStream = fopen(argv[2], "w");

		while( input != EOF) { // While we are not at the end of the input stream
			if ( input == 1){		 // If input has returned success
				input = fscanf(myInputFileStream, "%d", &argX); // Fetch data from stream and place it at the address of argX
				fprintf(myOutputFileStream, "%d	%g	%g\n", argX, sin(argX), cos(argX)); // Print the data to myOutputFileStream
			}
			else { // If we are not successfull, say if there was an error with fscanf()
			fprintf(stderr, "Failed to read input.\n"); // Print this to stderr so we know
			exit(-1); 																	// Terminate program
			}
		}

		fprintf(stderr, "Program was successful.\n"); // Let us know we were successful
	}
	return 0;
}
