//
// Implemented by Marc B. Sørensen on 2/13/21.
//

#include <stdio.h>
#include "funcs.h"

void name_digit( int digit ){
  /*
  Function name_digit takes one argument, and integer valued single digit,
  and will print out a string corresponding to that digit.

  ¤ dig : Integer valued digit.

  */

  switch ( digit ) {
    case 0:  printf("zero.        \n"); break;
    case 1:  printf("one.         \n"); break;
    case 2:  printf("two.         \n"); break;
    case 3:  printf("three.       \n"); break;
    case 4:  printf("four.        \n"); break;
    case 5:  printf("five.        \n"); break;
    case 6:  printf("six.         \n"); break;
    case 7:  printf("seven.       \n"); break;
    case 8:  printf("eight.       \n"); break;
    case 9:  printf("nine.        \n"); break;
    default: printf("not a digit. \n");
  }
}
