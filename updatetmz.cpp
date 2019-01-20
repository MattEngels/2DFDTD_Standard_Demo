/*	Functions to update the fields.  Depending on the type of grid, the fields can be treated as 1D or 2D	*/
/*	This source file belongs to project "Ch8_8.4 (TMz Example)"	*/

//#include <stdafx.h>
#include "fdtd-macro-tmz.h"

/*	Update the magnetic field	*/
void updateH2d(Grid *g) {
	int mm, nn;

	if (Type == oneDGrid) {
		for (mm = 0; mm < SizeX - 1; mm++)
			Hy1(mm) = Chyh1(mm) * Hy1(mm) + Chye1(mm) * (Ez1(mm + 1) - Ez1(mm)); }
	else {
		for (mm = 0; mm < SizeX; mm++) {
			for (nn = 0; nn < SizeY - 1; nn++)
			  Hx(mm, nn) = Chxh(mm, nn) * Hx(mm, nn) - Chxe(mm, nn) * (Ez(mm, nn + 1) - Ez(mm, nn));
		}
		for (mm = 0; mm < SizeX - 1; mm++) {
		  for (nn = 0; nn < SizeY; nn++)
			  Hy(mm, nn) = Chyh(mm, nn) * Hy(mm, nn) + Chye(mm, nn) * (Ez(mm + 1, nn) - Ez(mm, nn));
		}
	}
	return;
}

/*	Update the electric field	*/
void updateE2d(Grid *g) {
	int mm, nn;

	if (Type == oneDGrid) {
		for (mm = 1; mm < SizeX - 1; mm++)
			Ez1(mm) = Ceze1(mm) * Ez1(mm) + Cezh1(mm) * (Hy1(mm) - Hy1(mm - 1)); }
	else {
		for (mm = 1; mm < SizeX - 1; mm++) {
			for (nn = 1; nn < SizeY - 1; nn++)
				Ez(mm, nn) = Ceze(mm, nn) * Ez(mm, nn) +
				  Cezh(mm, nn) * ((Hy(mm, nn) - Hy(mm - 1, nn)) -
							   (Hx(mm, nn) - Hx(mm, nn - 1))); }
	}

	return;
}
