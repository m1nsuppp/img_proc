#ifndef GEO_H_
#define GEO_H_

#include "bmp.h"

/* Nearest Neighbor Interpolation */
BYTE* NearestInterpolation(BYTE* input, BYTE* output, int newWidth, int newHeight, int width, int height);

/*  Bi-linear Interpolation */
BYTE* BilinearInterpolation(BYTE* input, BYTE* output, int newWidth, int newHeight, int width, int height);

#endif /*  GEO_H_ */