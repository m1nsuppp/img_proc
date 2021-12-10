#ifndef GEO_H_
#define GEO_H_

#include "bmp.h"

#define PI 3.141592

int imit(int value);

/* Nearest Neighbor Interpolation */
void NearestInterpolation(BYTE* input, BYTE* output, double alpah, int width, int height);

/*  Bi-linear Interpolation */
void BilinearInterpolation(BYTE* input, BYTE* output, double alpha, int width, int height);

void MoveImg(BYTE* input, BYTE* output, int width, int height, int xd, int yd);

void MirrorImg(BYTE* input, BYTE* output, int width, int height);

void FlipImg(BYTE* input, BYTE* output, int width, int height);

void RotationImg(BYTE* input, BYTE* output, int width, int height, double degree);

void ResizeNearest(BYTE* input, BYTE* output, double alpha, int width, int height);

void ResizeBilinear(BYTE* input, BYTE* output, double alpha, int width, int height);

#endif /*  GEO_H_ */