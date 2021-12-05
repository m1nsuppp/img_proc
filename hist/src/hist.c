#include "../include/bmp.h"
#include "../include/hist.h"

#define MAX_INTENSITY 255

void GetHist(BYTE* input, int* hist, int width, int height) {
    int imgSize = width * height;
    for(int i = 0; i < imgSize; i++) {
        hist[input[i]]++;
    }
}

void CumulativeHist(int* stackHist, int* hist) {
    for(int i = 1; i <= MAX_INTENSITY; i++) {
        stackHist[i] = stackHist[i - 1] + hist[i];
    }
}

void HistEqual(BYTE* input, BYTE* output, int* stackHist, int width, int height) {
    int imgSize = width * height;
    double ratio = MAX_INTENSITY / (double)imgSize;

    BYTE normSum[256] = {0, };
    for(int i = 0; i <= MAX_INTENSITY; i++) {
        normSum[i] = (BYTE)(ratio * stackHist[i]);
    }
    
    for(int i = 0; i < imgSize; i++) {
        output[i] = normSum[input[i]];
    }
}