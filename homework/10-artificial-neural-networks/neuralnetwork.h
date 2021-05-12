//
// Created by marc on 5/12/21.
//

#ifndef HAVE_NEURALNETWORK_H
#define HAVE_NEURALNETWORK_H

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

typedef struct  {   int             numOfNeurons;
                    double          (*target_function) (double);
                    gsl_vector*     params;
                }
                neural_network;

neural_network*     neural_network_alloc    (int numOfNeurons_input, double (*target_function_input) (double));
void                neural_network_free     (neural_network* network);
double              neural_network_response (neural_network* network, double eval_pt);
void                neural_network_train    (neural_network* network, gsl_vector* input_data, gsl_vector* labels);

#endif //MINIMIZATION_NEURALNETWORK_H
