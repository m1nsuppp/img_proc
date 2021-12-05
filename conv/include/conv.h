#ifndef CONV_H_
#define CONV_H_

#include "bmp.h"

/* N x N Average Filter */
void AvgFilter(BYTE* input, BYTE* output, int width, int height, int size);

/* N x N Gaussian Smooth Filter */
void GaussSmoothFilter(BYTE* input, BYTE* output, int width, int height);

/* Sharpening (HPF)*/
void Sharpening(BYTE* input, BYTE* output, int width, int height);

/* Sobel X Conv */
void SobelX(BYTE* inpu, BYTE* output, int width, int height);

/* Sobel Y conv */
void SobelY(BYTE* input, BYTE* output, int width, int height);

/* Color Image to Gray-scale Image */
void ClrToGrayscale(BYTE* input, BYTE* output, int width, int height);

#endif /* CONV_H_ */