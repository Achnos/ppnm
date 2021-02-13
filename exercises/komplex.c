#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "komplex.h"

void komplex_print (char *s, komplex a) {
	printf ("%s (%g,%g)\n", s, a.re, a.im);
}

void komplex_set (komplex* z, double x, double y) {
	(*z).re = x;
	(*z).im = y;
}

komplex komplex_new (double x, double y) {
	komplex z = { x, y };
	return z;
}

komplex komplex_add (komplex a, komplex b) {
	komplex result = { a.re + b.re , a.im + b.im };
	return result;
}

komplex komplex_sub (komplex a, komplex b) {
	komplex result = { a.re - b.re , a.im - b.im };
	return result;
}

int komplex_equal (komplex a, komplex b, double acc, double eps){
	 if (
		 	 (    (fabs( a.re - b.re ) < acc)
	      &&  (fabs( a.im - b.im ) < acc)
			 )
	 	    ||
			 (   ((fabs( a.re - b.re ) / ( fabs(a.re) + fabs(b.re) )) < (eps / 2))
	      && ((fabs( a.im - b.im ) / ( fabs(a.re) + fabs(b.re) )) < (eps / 2))
			 )
		  )  { return 1; }
	  else { return 0; }
}

komplex komplex_mul (komplex a, komplex b) {
	komplex result = { a.re * b.re + a.im * b.im, a.im * b.re + a.re * b.im };
	return result;
}
/*
komplex komplex_div (komplex a, komplex b){
	komplex result = { a.re * b.re + a.im * b.im, a.im * b.re + a.re * b.im };
	return result;
}
*/
komplex komplex_conjugate(komplex z){
	z.im = -(z.im);
	return z;
}
/*
double  komplex_abs      (komplex z){}
komplex komplex_exp      (komplex z){}
komplex komplex_sin      (komplex z){}
komplex komplex_cos      (komplex z){}
komplex komplex_sqrt     (komplex z){}
*/
