/*	Function to implement a Ricker wavelet.  This is a traveling wave version of the function so ezInc() takes arguments of both time and space	*/
/*	This source file belongs to project "Ch8_8.4 (TMz Example)"	*/

//#include <stdafx.h>
#include "ezinc.h"
#include "fdtd-macro-tmz.h"

#define _USE_MATH_DEFINES
#include <math.h>

static double cdtds, ppw = 0;

/*	Initialize source-function variables	*/
void ezIncInit(Grid *g) {

	//printf("Enter the points per wavelength for Ricker source: ");
	//scanf(" %lf", &ppw);
	ppw = 25;
	cdtds = Cdtds;
	return;
}

/*	Calculate source function at given time and location	*/
double ezInc(double time, double location) {
	double arg;

	if (ppw <= 0) {
		fprintf(stderr,
			"ezInc: ezIncInit() must be called before ezInc.\n"
			"		Points per wavelength must be positive.\n");
		exit(-1);
	}

	arg = M_PI * ((cdtds * time - location) / ppw - 1.0);
	arg = arg * arg;

	return (1.0 - 2.0 * arg) * exp(-arg);
}
