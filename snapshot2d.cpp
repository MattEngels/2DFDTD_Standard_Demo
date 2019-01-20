/*	Function to record the 2D field to a file.  The data is stored as binary (raw) data.	*/
/*	This source file belongs to project "Ch8_8.4 (TMz Example)	*/

//#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macro-tmz.h"

static int temporalStride = -2, frame = 0, startTime,
	startNodeX, endNodeX, spatialStrideX,
	startNodeY, endNodeY, spatialStrideY;
static char basename[80];

void snapshotInit2d(Grid *g) {

	int choice;

	printf("Do you want 2D snapshots? (1=yes, 0=no) ");
	scanf("%d", &choice);
	if (choice == 0) {
		temporalStride = -1;
		return;
	}

	printf("duration of simulation is %d steps.\n", MaxTime);
	printf("Enter start time and temporal stride: ");
	scanf(" %d %d", &startTime, &temporalStride);
	printf("In the x-direction, the grid has %d total nodes"
		  " (ranging from 0 to %d)\n", SizeX, SizeX - 1);
	printf("Enter first node, last node, and spatial stride: ");
	scanf(" %d %d %d", &startNodeX, &endNodeX, &spatialStrideX);
	printf("In the y-direction, the grid has %d total nodes"
		  " (ranging from 0 to %d)\n", SizeY, SizeY - 1);
	printf("Enter first node, last node, and spatial stride: ");
	scanf(" %d %d %d", &startNodeY, &endNodeY, &spatialStrideY);
	printf("Enter the base name: ");
	scanf(" %s", basename);

	return;
}

void snapshot2d(Grid *g) {
	int mm, nn;
	float dim1, dim2, temp;
	char filename[100];
	FILE *out;

	/*	Ensure temporal stride is a reasonable value	*/
	if (temporalStride == -1) {
		return;
	} if (temporalStride < -1) {
		fprintf(stderr,
			"snapshot2d: snapshotInit2d must be called before snapshot.\n"
			"			 Temporal stride must be set to positive value.\n");
		exit(-1);
	}

	/*	Get snapshot if temporal conditions met	*/
	if (Time >= startTime && (Time - startTime) % temporalStride == 0) {
		sprintf(filename, "%s.%d", basename, frame++);
		out = fopen(filename, "wb");

		/*	Write dimensions to output file -- express dimensions as floats	*/
		dim1 = (endNodeX - startNodeX) / spatialStrideX + 1;
		dim2 = (endNodeY - startNodeY) / spatialStrideY + 1;
		fwrite(&dim1, sizeof(float), 1, out);
		fwrite(&dim2, sizeof(float), 1, out);

		/*	Write remaining data	*/
		for (nn = endNodeY; nn >= startNodeY; nn -= spatialStrideY)
			for (mm = startNodeX; mm <= endNodeX; mm += spatialStrideX) {
				temp = (float)Ez(mm, nn);									//	This stores the data as a float through type-casting
				fwrite(&temp, sizeof(float), 1, out);						//	Actually write the float
			}

		fclose(out);	//close file
	}

	return;
}

