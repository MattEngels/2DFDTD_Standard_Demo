/*	This header file belongs to project "Ch8_8.4 (TMz Example)"	*/

#ifndef _FDTD_PROTO1_H
#define _FDTD_PROTO1_H

#include "fdtd-grid1.h"

/*	Function prototypes	*/
void gridInit(Grid *g);

void snapshotInit2d(Grid *g);
void snapshot2d(Grid *g);

void updateE2d(Grid *g);
void updateH2d(Grid *g);

#endif
