#include "piApproxMultithreaded.h"
#include <pthread.h>

int main( void ){

  int numOfPts = 1e9;
  piApproxMultithreaded( numOfPts );

  return 0;
}
