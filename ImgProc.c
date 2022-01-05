#include "ImgProc.h"

void Convolution(BYTE* input, BYTE* output, int width, int height, double** mask) {
    const int size = sqrt(mask);
    int margin = size / 2;
    double convValue = 0.0;
    for(int i = margin; i < height - margin; i++){
        for(int j = margin; j < width - margin; j++){
            for(int m = -margin; m <= margin; m++){
                for(int n = -margin; n <= margin; n++){
                    convValue += input[(i + m) * width + (j + n)] * mask[m + margin][n + margin];
                }
            }
            output[i * width + j] = (BYTE)convValue;
            convValue = 0.0;
        }
    }
}

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

void NearestInterpolation(BYTE* input, BYTE* output, double alpha, int width, int height) {
    int tmpHeight = 0, tmpWidth = 0, addrIndex = 0;
    int newWidth = alpha * width;
    int newHeight = alpha * height;
    double stepX = (double)newHeight / (double)height;
    double stepY = (double)newWidth / (double)width;

    for(int i = 0; i < newWidth; i++) {
        for(int j = 0; j < newHeight; j++) {
            tmpHeight = round(j / stepX);
            tmpWidth = round(i / stepY);
            addrIndex = (tmpWidth * height) + tmpHeight;
            output[(i * height) + j] = input[addrIndex];
        }
    }
}

void BilinearInterpolation(BYTE* input, BYTE* output, double alpha, int width, int height) {
    int newWidth = alpha * width;
    int newHeight = alpha * height;
    int newImgSize = newWidth * newHeight;
    int intX = 0, intY = 0, low = 0, high = 0;
    double stepX = 0.0, stepY = 0.0, realX = 0.0, realY = 0.0;

    BYTE* tmpImg = (BYTE*)calloc(sizeof(BYTE), newImgSize);
    stepX = (double)height / (double)newHeight;
    stepY = (double)width / (double)newWidth;

    // first pass - expand in X direction
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < newHeight; j++) {
            realX = j * stepX;
            intX = (int)realX;

            if((intX + 1) < width) {
                low = input[(i * height) + intX];
                high = input[(i * height) + (intX + 1)];
                tmpImg[(i * newHeight) + j] = low + (BYTE)((high - low) * (realX - intX));
            }
            else {
                tmpImg[(i * newHeight) + j] = input[(i * height) + intX];
            }
        }
    }

    // second pass - expand in Y direction
    for(int i = 0; i < newWidth; i++) {
        for(int j = 0; j < newWidth; j++) {
            realY = i * stepY;
            intY = (int)realY;

            if((intY + 1) < width) {
                low = tmpImg[(intY * newHeight) + j];
                high = tmpImg[((intY + 1) * newHeight) + j];
                output[(i * newHeight) + j] = low + (BYTE)(high - low) * (realY - intY);
            }
            else {
                output[(i * newHeight) + j] = tmpImg[(intY * newHeight) + j];
            }
        }
    }
}

void MoveImg(BYTE* input, BYTE* output, int width, int height, int xd, int yd) {
    int newX = 0, newY = 0;

    for(int i = 0; i < height; i++) {
        newY = i + yd;
        if(newY < 0 || newY >= height) {
            continue;
        }
        for(int j = 0; j < width; j++) {
            newX = j + xd;
            if(newX < 0 || newX >= width) {
                continue;
            }
            output[newY * width + newX] = input[i * width + j];
        }
    }
}

void MirrorImg(BYTE* input, BYTE* output, int width, int height) {
    int newX = 0;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            newX = width - j - 1;
            output[i * width + newX] = input[i * width + j];
        }
    } 
}

void FlipImg(BYTE* input, BYTE* output, int width, int height) {
    int newY = 0;

    for(int i = 0; i < height; i++) {
        newY = height - i - 1;
        for(int j = 0; j < width; j++) {
            output[newY * width + j] = input[i * width + j];
        }
    }
}

void RotationImg(BYTE* input, BYTE* output, int width, int height, double degree) {
    double theta = PI / (180.0 / degree);
    int centerX = width / 2;
    int centerY = height / 2;
    int newX = 0, newY = 0;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            newX = (i - centerY) * sin(theta) + (j - centerX) * cos(theta) + centerX;
            newY = (i - centerY) * cos(theta) + (j - centerX) * sin(theta) + centerY;

            if(newX < 0) continue;
            if(newX >= width) continue;
            if(newY < 0) continue;
            if(newY >= height) continue;

            output[newY * width + newX] = input[i * width + j];
        }
    }
}