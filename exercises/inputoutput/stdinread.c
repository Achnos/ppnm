#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main( int argc, char* argv[]){
	int input = 1; 			// Input will receive the return value from fscanf
	int argX;						// Variable to hold the data from stdin

	while( input != EOF) { // While we are not at the end of the input stream
		if ( input == 1){		 // If input has returned success
			input = fscanf(stdin, "%d", &argX); // Fetch data from stream and place it at the address of argX
			fprintf(stdout, "%d	%g	%g\n", argX, sin(argX), cos(argX)); // Print the data to stdout
		}
		else { // If we are not successfull, say if there was an error with fscanf()
		fprintf(stderr, "Failed to read input.\n"); // Print this to stderr so we know
		exit(-1); 																	// Terminate program
		}
	}

	fprintf(stderr, "Program was successful.\n"); // Let us know we were successful

	return 0;
}
