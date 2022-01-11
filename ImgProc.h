#ifndef IMGPROC_H_
#define IMGPROC_H_

#define MAX_INTENSITY 255
#define PI 3.14

#include "bmp.h"

void Convolution(BYTE* input, BYTE* output, int width, int height, double** mask);
void SobelConv(BYTE* input, BYTE* output, int width, int height, double** mask);
void GetHist(BYTE* input, int* hist, int width, int height);
void CumulativeHist(int* stackHist, int* hist);
void HistEqual(BYTE* input, BYTE* output, int* stackHist, int width, int height);
void NearestInterpolation(BYTE* input, BYTE* output, double alpha, int width, int height);
void BilinearInterpolation(BYTE* input, BYTE* output, double alpha, int width, int height);
void MoveImg(BYTE* input, BYTE* output, int width, int height, int xd, int yd);
void MirrorImg(BYTE* input, BYTE* output, int width, int height);
void FlipImg(BYTE* input, BYTE* output, int width, int height);
void RotationImg(BYTE* input, BYTE* output, int width, int height, double degree);
void Binarization(BYTE* input, BYTE* output, int width, int height, BYTE threshold);


#endif /* IMGPROC_H_ */