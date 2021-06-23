//
// Created by marc on 5/12/21.
//

#include <time.h>

#include "neuralnetwork.h"
#include "minimization.h"
#include "utilities.h"

neural_network*     neural_network_alloc    (int numOfNeurons_input, double (*target_function_input) (double),  double (*target_derivative_input) (double), double (*target_integral_input) (double)){

    int numOfParams                 =   3;

    neural_network* network         =   (neural_network*)malloc(sizeof(neural_network));
    network -> params               =   gsl_vector_alloc(numOfNeurons_input * numOfParams);
    network -> target_function      =   target_function_input;
    network -> target_derivative    =   target_derivative_input;
    network -> target_integral      =   target_integral_input;
    network -> numOfNeurons         =   numOfNeurons_input;

    return network;
}

void                neural_network_free     (neural_network* network){

    gsl_vector_free(network -> params);
    free(network);

}

double              neural_network_response (neural_network* network, double eval_pt){

    int     numOfParams     =   2;
    int     numOfNeurons    =   network -> numOfNeurons;
    double  response        =   0;

    for ( int neuronId = 0; neuronId < numOfNeurons; ++neuronId){

        double neuron_shift         =   gsl_vector_get( network -> params, numOfParams * neuronId + 0 );
        double neuron_scale         =   gsl_vector_get( network -> params, numOfParams * neuronId + 1 );
        double neuron_edge_weight   =   gsl_vector_get( network -> params, numOfParams * neuronId + 2 );

        response += ( network -> target_function( (eval_pt - neuron_shift) / neuron_scale) ) * neuron_edge_weight;
    }

    return response;
}

double              neural_network_response_derivative (neural_network* network, double eval_pt){

    int     numOfParams     =   2;
    int     numOfNeurons    =   network -> numOfNeurons;
    double  response        =   0;

    for ( int neuronId = 0; neuronId < numOfNeurons; ++neuronId){

        double neuron_shift         =   gsl_vector_get( network -> params, numOfParams * neuronId + 0 );
        double neuron_scale         =   gsl_vector_get( network -> params, numOfParams * neuronId + 1 );
        double neuron_edge_weight   =   gsl_vector_get( network -> params, numOfParams * neuronId + 2 );

        response += ( network -> target_derivative( (eval_pt - neuron_shift) / neuron_scale) ) * neuron_edge_weight / neuron_scale;
    }

    return response;
}

double              neural_network_response_integral   (neural_network* network, double rightPt, double leftPt){

    int     numOfParams     =   2;
    int     numOfNeurons    =   network -> numOfNeurons;
    double  response        =   0;

    for ( int neuronId = 0; neuronId < numOfNeurons; ++neuronId){

        double neuron_shift         =   gsl_vector_get( network -> params, numOfParams * neuronId + 0 );
        double neuron_scale         =   gsl_vector_get( network -> params, numOfParams * neuronId + 1 );
        double neuron_edge_weight   =   gsl_vector_get( network -> params, numOfParams * neuronId + 2 );

        response += (((network -> target_integral)((leftPt - neuron_shift) / neuron_scale)) * neuron_edge_weight * neuron_scale) - (((network -> target_integral)((rightPt - neuron_shift) / neuron_scale)) * neuron_edge_weight * neuron_scale);
    }

    return response;
}

void                neural_network_train    (neural_network* network, gsl_vector* input_data, gsl_vector* labels){

    unsigned int seed = time(NULL);

    int numOfParams = 3;
    int numOfpts = input_data -> size;
    int numOfNeurons = network -> numOfNeurons;

    /*
     * Please never use inline functions... In this case it is an easy, dirty, workaround
     * but should generally be avoided
     */
    double cost_function (gsl_vector* next_params){
        int numOfNeurons = network -> numOfNeurons;
        gsl_vector* updated_params = gsl_vector_alloc(numOfNeurons * numOfParams);

        for (int neuronId = 0; neuronId < numOfNeurons; ++neuronId){
            for (int paramId = 0; paramId < numOfParams; ++paramId) {
                gsl_vector_set(updated_params, numOfParams * neuronId + paramId, gsl_vector_get(next_params, numOfParams * neuronId + paramId));
            }
        }
        network -> params = updated_params;

        double cost =  0;
        for (int ptId = 0; ptId < numOfpts; ++ptId){

            double eval_pt      =   gsl_vector_get(input_data, ptId);
            double pt_label     =   gsl_vector_get(labels, ptId);
            double response     =   neural_network_response(network, eval_pt);

            cost += (response - pt_label) * (response - pt_label) ;
        }

        return cost;
    }

    double tolerance = 1e-5;

    gsl_vector* learned_params = gsl_vector_alloc(numOfNeurons * numOfParams);

    double shift_interp = -5;
    double scale_interp = 5;

    for(int id = 0; id < numOfNeurons; id++){
        double shift    =   -5 + (scale_interp - shift_interp) * id / (numOfNeurons - 1);
        double scale    =   1;
        double weight   =   1;

        gsl_vector_set(learned_params, 3 * id, 1);
        gsl_vector_set(learned_params, 3 * id + 1, scale);
        gsl_vector_set(learned_params, 3 * id + 2, weight);
    }
    /*
    for (int id = 0; id < numOfNeurons * numOfParams; ++id){
        gsl_vector_set(learned_params, id, randomNumber(&seed));
    }
    */

    quasi_newtonMethod(cost_function, learned_params, tolerance);

    network -> params = learned_params;
}
