#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_vector.h>

#include "input2Array.h"

void input2Array(int numOfDataPts, gsl_vector* XData, gsl_vector* YData, char* inputFilename ){
  int numOfReturnVals = 2;  // The return value of fscanf() is the number of fetched variables

  int    input = numOfReturnVals; 			// Input will receive the return value from fscanf
  double argX;						              // Variable to hold the X data from stdin
  double argY;						              // Variable to hold the Y data from stdin

  FILE* myInputFileStream  = fopen(inputFilename, "r");

  int id = 0;
  while( input != EOF && id < numOfDataPts ) { // While we are not at the end of the input stream
    if ( input == numOfReturnVals){		 // If input has returned success
      input = fscanf(myInputFileStream, "%lg\t%lg", &argX, &argY); // Fetch data from stream and place it at the address of argX

      gsl_vector_set(XData, id, argX);
      gsl_vector_set(YData, id, argY);
      id++;
    }
    else { // If we are not successfull, say if there was an error with fscanf()
      fprintf(stderr, "Failed to read input.\n"); // Print this to stderr so we know
      exit(-1); 																	// Terminate program
    }
  }

  fclose(myInputFileStream);
}
