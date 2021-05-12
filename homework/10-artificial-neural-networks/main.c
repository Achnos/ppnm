#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_vector.h>

#include "neuralnetwork.h"
#include "input2Array.h"

int main(int argc, char* argv[]){
    // _________________________________________________________________________________________________________________

    printf( "\n##############################################  " );
    printf( "\n# ------- ARTIFICIAL NEURAL NETWORKS ------- #  " );
    printf( "\n##############################################\n" );
    printf("\n-- A) ----------------\n");

    int numOfDataPts = 20;
    int numOfNeurons = 5;

    printf("Loading dataset of %d tabulated values of f(x) = sin(x)...\n", numOfDataPts);
    gsl_vector* xData = gsl_vector_alloc(numOfDataPts);
    gsl_vector* yData = gsl_vector_alloc(numOfDataPts);
    input2Array(numOfDataPts, xData, yData, argv[1]);

    printf("Initiallizing a neural network of 1 hidden layer with %d neurons...\n", numOfNeurons);
    neural_network* network = neural_network_alloc(numOfNeurons, &cos);

    printf("Training network...\n");
    neural_network_train(network, xData, yData);

    FILE* myOutputFilestream = fopen(argv[2], "w");
    double xMin = 0;
    double xMax = 11;
    for( double val = xMin; val <= xMax; val += 1.0/8 ){
        fprintf(myOutputFilestream, "%10g %10g %10g\n", val, neural_network_response(network, val), cos(val));
    }
    fclose(myOutputFilestream);

    neural_network_free(network);


    return 0;
}
