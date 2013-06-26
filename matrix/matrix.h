#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#define MN	1000
#define ROWA	MN
#define COLA	MN

#define ROWB	MN
#define COLB	MN

#define ROWC	MN
#define COLC	MN

#define ROWD	MN
#define COLD	MN

#define ROWE	MN
#define COLE	MN

int pMatrixMult( float* matrixA, int Am, int An, float* matrixB, int Bm, int Bn, float* restltMatrix );

#endif // MATRIX_H_INCLUDED