#include "bmp.h"

/* N x N Average Filter */
void avgFilter(BYTE* input, BYTE* output, int width, int height, int size);

/* N x N Gaussian Smooth Filter */
void gaussSmoothFilter(BYTE* input, BYTE* output, int width, int height);

/* Sharpening (HPF)*/
void sharpening(BYTE* input, BYTE* output, int width, int height);