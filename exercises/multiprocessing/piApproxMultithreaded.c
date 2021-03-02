#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#include "rndNum.h"
#include "piApproxMultithreaded.h"

typedef struct placePtsArgStruct {
    unsigned int seed;
    double numOfPts;
    int* ptsInCircle;
    double unitCircleRadius;
} placePtsArgStruct;

void* placePts( void* placePtsArgStructInput ){
  placePtsArgStruct* args   =   ( placePtsArgStruct* )placePtsArgStructInput;

  unsigned int seed         =   args->seed              ;
  double numOfPts           =   args->numOfPts          ;
  int* ptsInCircle          =   args->ptsInCircle       ;
  double unitCircleRadius   =   args->unitCircleRadius  ;

  double xpos   =   0;
  double ypos   =   0;

  for ( int iteration = 0; iteration < numOfPts/2; iteration++ ){
    xpos = randomNumber(&seed);
    ypos = randomNumber(&seed);

    if ( sqrt( pow(xpos, 2) + pow(ypos, 2) ) <= unitCircleRadius ){
      (*ptsInCircle)++;
      //printf("%d\n", *ptsInCircle);
    }
  }

  return NULL;
}


void piApproxMultithreaded( int numOfPts ){
  unsigned int masterSeed   =   time(NULL) ;
  unsigned int firstSeed    =   masterSeed ;
  unsigned int secondSeed   =   masterSeed + 1 ;



  double unitCircleRadius   =   1.0        ;

  int* ptsInCircle_first = malloc(sizeof(int));
  *ptsInCircle_first = 0;
  int* ptsInCircle_second = malloc(sizeof(int));
  *ptsInCircle_second = 0;

  placePtsArgStruct placePtsArgStruct_firstPart   =  { firstSeed,  numOfPts, ptsInCircle_first,  unitCircleRadius };
  placePtsArgStruct placePtsArgStruct_secondPart  =  { secondSeed, numOfPts, ptsInCircle_second, unitCircleRadius };

  pthread_t firstPart;
  pthread_t secondPart;

  pthread_attr_t* attributes = NULL;
  pthread_create( &firstPart,  attributes, placePts, (void*)&placePtsArgStruct_firstPart  );
	pthread_create( &secondPart, attributes, placePts, (void*)&placePtsArgStruct_secondPart );

  void* status = NULL;
	pthread_join(firstPart,  status);
	pthread_join(secondPart, status);

  double ptsInCircle   =   (*ptsInCircle_first + *ptsInCircle_second);
  double myPiApprox    =   4.0*ptsInCircle/((double)numOfPts);

  printf("My approximation of pi = %g\n"  , myPiApprox                    );
  printf("Pi is actually = %g\n"          , M_PI                          );
  printf("Deviation is %g percent\n"      , fabs(1.0-myPiApprox/M_PI)*100 );
}
