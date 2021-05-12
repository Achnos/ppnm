#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_vector.h>

#include "minimization.h"
#include "input2Array.h"

double energy;
double bound_energy;
double maxPt;
double bound_maxPt;

int numOfDataPts;
double *energy_BW ;
double *crossSection ;
double *error  ;

double testFunc (gsl_vector* vals){
    // 1 + (x-a)^2 + (y-b)^2
    double x = gsl_vector_get(vals, 0);
    double y = gsl_vector_get(vals, 1);

    double a = 6;
    double b = 13;

    double funcVal = 1 + (x-a)*(x-a) + (y-b)*(y-b);

    return funcVal;
}

double simplex_testFunc (double* vals){
    // 1 + (x-a)^2 + (y-b)^2
    double x = vals[0];
    double y = vals[1];

    double a = 6;
    double b = 13;

    double funcVal = 1 + (x-a)*(x-a) + (y-b)*(y-b);

    return funcVal;
}

double rosenbrockValley(gsl_vector* vals) {
    double x = gsl_vector_get(vals, 0);
    double y = gsl_vector_get(vals, 1);

    double funcVal = (1-x)*(1-x) + 100*(y-x*x)*(y-x*x);
    return funcVal;
}

double himmelblau(gsl_vector* vals) {
    double x = gsl_vector_get(vals, 0);
    double y = gsl_vector_get(vals, 1);

    double funcVal = (x*x+y-11)*(x*x + y - 11) + (x + y*y - 7)*(x + y*y - 7);
    return funcVal;
}

double breitWigner(double mass, double width, double scaleFactor, double energies){
    return scaleFactor/((energies-mass)*(energies-mass) + (width*width)/4);
}

double deviation(gsl_vector* vals){
    double mass = gsl_vector_get(vals, 0);
    double width = gsl_vector_get(vals, 1);
    double scaleFactor = gsl_vector_get(vals, 2);

    double sum = 0;
    for (int pt = 0; pt < numOfDataPts; pt++){
        sum += pow(breitWigner(mass, width, scaleFactor, energy_BW[pt]) - crossSection[pt], 2) / pow(error[pt], 2);
    }

}

int main(int argc, char* argv[]){
    // _________________________________________________________________________________________________________________

    printf( "\n################################  " );
    printf( "\n# ------- MINIMIZATION ------- #  " );
    printf( "\n################################\n" );
    printf("\n-- A) Quasi-Newton method with numerical gradient, back-tracking linesearch, and rank-1 update --\n");

    printf("\nTesting the minimization routine, on f(x,y) = 1 + x² + y² ...\n");
    double minimum_x = 6;
    double minimum_y = 13;
    double initial_x_val = minimum_x - 2;
    double initial_y_val = minimum_y - 3;

    int dims = 2;
    double tolerance = 1e-5;
    gsl_vector* minimum = gsl_vector_alloc(dims);
    gsl_vector_set(minimum, 0, initial_x_val );
    gsl_vector_set(minimum, 0, initial_y_val );

    printf("The initial value is at (x, y) = (%g, %g)\n", initial_x_val, initial_y_val);
    quasi_newtonMethod(testFunc, minimum, tolerance);
    printf("The found  minima is at (x, y) = (%g, %g)\n", gsl_vector_get(minimum, 0), gsl_vector_get(minimum, 1));
    printf("The actual minima is at (x, y) = (%g, %g)\n", minimum_x, minimum_y);


    printf("\nTesting the minimization routine, on Rosenbrock's valley function, f(x,y) = (1 - x)² + 100*(y - x²)² ...\n");
    minimum_x = 1;
    minimum_y = 1;
    initial_x_val = minimum_x - 1;
    initial_y_val = minimum_y - 1;

    gsl_vector_set(minimum, 0, initial_x_val );
    gsl_vector_set(minimum, 0, initial_y_val );

    printf("The initial value is at (x, y) = (%g, %g)\n", initial_x_val, initial_y_val);
    quasi_newtonMethod(rosenbrockValley, minimum, tolerance);
    printf("The found  minima is at (x, y) = (%g, %g)\n", gsl_vector_get(minimum, 0), gsl_vector_get(minimum, 1));
    printf("The actual minima is a parabola");

    printf("\nTesting the minimization routine, on himmelblaus function, f(x,y) = (x² + y - 11)² + (x + y² - 7)² ...\n");
    minimum_x = 3;
    minimum_y = 2;
    initial_x_val = minimum_x - 0.2;
    initial_y_val = minimum_y - 0.2;

    gsl_vector_set(minimum, 0, initial_x_val );
    gsl_vector_set(minimum, 0, initial_y_val );

    printf("The initial value is at (x, y) = (%g, %g)\n", initial_x_val, initial_y_val);
    quasi_newtonMethod(himmelblau, minimum, tolerance);
    printf("The found  minima is at (x, y) = (%g, %g)\n", gsl_vector_get(minimum, 0), gsl_vector_get(minimum, 1));
    printf("The actual minima are at (x, y) = (%g, %g), (-2.80, 3.13), (-3.78, -3.28), (3.58, -1.84)\n", minimum_x, minimum_y);

    // _________________________________________________________________________________________________________________


    printf("\n\n-- B) Higgs discovery --\n");

    printf("\n Fitting to the Higgs particle dataset:\n");
    printf("---------------------------------------\n");
    double measured_mass = 125.3;

    numOfDataPts    =   30;
    energy_BW       =   (double*)malloc( numOfDataPts * sizeof(double) );
    crossSection    =   (double*)malloc( numOfDataPts * sizeof(double) );
    error           =   (double*)malloc( numOfDataPts * sizeof(double) );

    input2Array(energy_BW, crossSection, error, "higgs_data.txt");
    printf("c.m. energy E[GeV], cross-section σ(E)[certain units], error δσ [same units]\n");
    for (int i = 0; i < numOfDataPts; i++){
        printf("%g\t%g\t%g\n", energy_BW[i], crossSection[i], error[i]);
    }
    printf("\n");

    dims = 3;
    gsl_vector* minimum_bw = gsl_vector_alloc(dims);
    gsl_vector_set(minimum_bw, 0, measured_mass + 1 );
    gsl_vector_set(minimum_bw, 1, 2.5 );
    gsl_vector_set(minimum_bw, 2, 9);
    quasi_newtonMethod(deviation, minimum_bw, tolerance);

    printf("The initial value is at (m, Γ, A) = (%g, %g, %g)\n", measured_mass + 20, 2.5, 9.0);
    printf("The found  minima is at (m, Γ, A) = (%g, %g, %g)\n", gsl_vector_get(minimum_bw, 0), gsl_vector_get(minimum_bw, 1), gsl_vector_get(minimum_bw, 2));

    FILE* myOutputFilestream = fopen("higgs_fit.txt", "w");
    for(int pt = 0; pt < numOfDataPts; ++pt){
        double funcVal = breitWigner(gsl_vector_get(minimum_bw, 0), gsl_vector_get(minimum_bw, 1), gsl_vector_get(minimum_bw, 2), energy_BW[pt]);
        fprintf(myOutputFilestream, "%g\t%g\t%g\t%g\n", energy_BW[pt], crossSection[pt], error[pt], funcVal);
    }
    fclose(myOutputFilestream);

    // _________________________________________________________________________________________________________________

    printf("\n\n-- C) Implement the downhill simplex method --\n");

    printf("\nTesting the simplex method, on f(x,y) = 1 + x² + y² ...\n\n");
    dims = 2;
    int numOfPts = dims + 1;
    double** simplex = malloc(numOfPts*sizeof(double));
    for(int ptId = 0; ptId < numOfPts; ptId++){
        simplex[ptId] = malloc(dims * sizeof(double));
    }
    simplex[0][0] = 4;
    simplex[0][1] = 10;
    simplex[1][0] = 2;
    simplex[1][1] = 2;
    simplex[2][0] = -3;
    simplex[2][1] = 1;
    printf("Starting points are { (x_0, y_0), (x_1, y_1), (x_2, y_2) } = { (%g, %g), (%g, %g), (%g, %g) }\n", simplex[0][0], simplex[0][1], simplex[1][0], simplex[1][1], simplex[2][0], simplex[2][1]);

    int numOfsteps = downhillsimplex(simplex_testFunc, simplex, dims, tolerance);
    printf("Number of steps used to converge: %d\n", numOfsteps);
    printf("Found minimum, is at:  (x, y) = (%g, %g)\n", simplex[0][0], simplex[0][1]);
    printf("Actual minimum, is at: (x, y) = (%d, %d)\n\n", 6, 13);

    return 0;
}
