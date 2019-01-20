/*	Grid initialization function for a TMz simulation.  The grid here is a simply homogeneous free space	*/
/*	This source file belongs to project "Ch8_8.4 (TMz Example)"	*/

//#include <stdafx.h>
#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include <math.h>

void gridInit(Grid *g) {
	double imp0 = 377.0;
	int mm, nn;

	Type = tmZGrid;
	SizeX = 4096;				//	Size of X-Domain
	SizeY = 4096;					//	Size of Y-Domain
	MaxTime = 1000;				//	Duration of simulation
	Cdtds = 1.0 / sqrt(2.0);	//	Courant number

	ALLOC_2D(g->hx,		SizeX,		SizeY - 1,	double);
	ALLOC_2D(g->chxh,	SizeX,		SizeY - 1,	double);
	ALLOC_2D(g->chxe,	SizeX,		SizeY - 1,	double);
	ALLOC_2D(g->hy,		SizeX - 1,	SizeY,		double);
	ALLOC_2D(g->chyh,	SizeX - 1,	SizeY,		double);
	ALLOC_2D(g->chye,	SizeX - 1,	SizeY,		double);
	ALLOC_2D(g->ez,		SizeX,		SizeY,		double);
	ALLOC_2D(g->ceze,	SizeX,		SizeY,		double);
	ALLOC_2D(g->cezh,	SizeX,		SizeY,		double);

	/*	Set the electric-field update coefficients	*/
	for (mm = 0; mm < SizeX; mm++){
		for (nn = 0; nn < SizeY; nn++) {
			Ceze(mm, nn) = 1.0;
			Cezh(mm, nn) = Cdtds * imp0;
		}}

	/*	Set the magnetic-field update coefficients	*/
	for (mm = 0; mm < SizeX; mm++) {
		for (nn = 0; nn < SizeY - 1; nn++) {
			Chxh(mm, nn) = 1.0;
			Chxe(mm, nn) = Cdtds / imp0;
		}}

	/*	Still part of updating the magnetic-field update coefficients	*/
	for (mm = 0; mm < SizeX - 1; mm++) {
		for (nn = 0; nn < SizeY - 1; nn++) {
			Chyh(mm, nn) = 1.0;
			Chye(mm, nn) = Cdtds / imp0;
		}}

	return;
}

