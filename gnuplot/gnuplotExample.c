#include <stdio.h>
#include "gnuplot.h"

int main(){
  char* filename = "testdata.txt";
  int xColumnId  = 1;
  int yColumnId  = 2;
  char* plotParams = "set ylabel 'y'\nset xlabel 'x'\n set title 'Plottitle'";
  gnuplot(filename, xColumnId, yColumnId, plotParams);
  return 0;
}
