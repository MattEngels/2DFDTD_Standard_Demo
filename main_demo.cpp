/*	TMz simulation with Ricker source at center of grid	*/
/*	This source file belongs to project "Ch8_8.4 (TMz Example)"	*/

//#include <stdafx.h>
#include "fdtd-alloc1.h"
#include "fdtd-macro-tmz.h"
#include "fdtd-proto1.h"
#include "ezinc.h"
#include <chrono>
#include <iostream>

int main()
{

	Grid *g;

	ALLOC_1D(g, 1, Grid);								// Allocate memory for grid

	gridInit(g);										// Initialize the grid
	ezIncInit(g);										// Initialize TFSF and source
	//snapshotInit2d(g);									// Initialize snapshot engine
auto start = std::chrono::high_resolution_clock::now();
	/*	Start time-stepping	*/
	for (Time = 0; Time < MaxTime; Time++) {
		updateH2d(g);									// Update the magnetic field
		updateE2d(g);									// Update the electric field
		Ez(SizeX / 2, SizeY / 2) = ezInc(Time, 0.0);	// Add a source
		//snapshot2d(g);									// Take a snapshot
	} /*	End time-stepping	*/

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	return 0;
}
