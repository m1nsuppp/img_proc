#ifndef FILTER_H_
#define FILTER_H_

#include "bmp.h"


/* 3 x 3 Gaussian Smooth Filter */
void GaussSmoothFilter3x3(BYTE* input, BYTE* output, int width, int height);

/* 5 x 5 Gaussian Smooth Filter */
void GaussSmoothFilter5x5(BYTE* input, BYTE* output, int width, int height);

/* 3 x 3 Median Filter */
void MedianFilter3x3(BYTE* input, BYTE* output, int width, int height);

/* 5 x 5 Median Filter */
void MedianFilter5x5(BYTE* input, BYTE* output, int width, int height);

#endif /* FILTER_H_ */