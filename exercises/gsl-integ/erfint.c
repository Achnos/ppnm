#include <gsl/gsl_integration.h>
#include <math.h>

double erfIntegral( double x, void* params ){
    /* Defines a function that will be used to declare a GSL_FUNCTION below
     *
     *  ¤ x      : the query points of the function
     *  ¤ params : a set of parameters, to obtain the necessary signature of the function
     *             when using as a GSL_FUNCTION, but will be set to NULL in this case
     *
     *  Returns a double valued function value.
     */
    params = NULL;
    double frontConst   =  2/sqrt(M_PI);
    double funcVal      =  exp(-pow(x, 2));
    double returnVal    =  frontConst*funcVal;

    return returnVal;
}

double integratedErrorFunction( double upperLimit, const gsl_function* myGSLFUNC, double epsabs, double epsrel, size_t limit ){
    /* Function to integrate the GSL_FUNCTION on (0, x)
     *
     */
    double lowerLimit = 0;

    gsl_integration_workspace* workspace = gsl_integration_workspace_alloc( limit );
    double result;
    double absError;

    gsl_integration_qags(myGSLFUNC, lowerLimit, upperLimit, epsabs, epsrel, limit, workspace, &result, &absError);

    gsl_integration_workspace_free(workspace);
    workspace = NULL;

    return result;
}
