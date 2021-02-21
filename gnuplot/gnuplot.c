#include <stdio.h>
#include "gnuplot.h"

void gnuplot( char* filename, int xColumnId, int yColumnId, char* plotParams){
  /*
  Function gnuplot() takes one argument, the file name
  and plots the data contained in that file, piping
  it into gnuplot for plotting. Modyfy fprintf statements
  below to set styles.

  ¤ filename is a char* (string) containing the filename such as "filename.txt"
    - Data should be tabulated in columns. For example (x,y) data, where column
      one is the x-data, with column two the corresponding y-data

  ¤ xColumnId the column index containing x-data

  ¤ yColumnId the column index containing y-data

  */

  FILE *pipe = popen("gnuplot -persist","w");
  fprintf(pipe, "%s\n", plotParams);
  fprintf(pipe, "plot '%s' using %d:%d with lines\n", filename, xColumnId, yColumnId);
  pclose(pipe);
}
