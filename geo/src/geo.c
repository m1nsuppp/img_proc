#include "geo.h"

BYTE* NearestInterpolation(BYTE* input, BYTE* output, int newWidth, int newHeight, int width, int height) {
    int tmpHeight = 0, tmpWidth = 0, addrIndex = 0;

    double stepX = (double)newHeight / (double)height;
    double stepY = (double)newWidth / (double)width;

    for(int i = 0; i < newWidth; i++) {
        for(int j = 0; j < newHeight; j++) {
            tmpHeight = (int)((j / stepX) + 0.5);
            tmpWidth = (int)((i / stepY) + 0.5);
            addrIndex = tmpWidth * height + tmpHeight;
            output[i * newWidth + j] = input[addrIndex];
        }
    }
    return output;
}

BYTE* BilinearInterpolation(BYTE* input, BYTE* output, int newWidth, int newHeight, int width, int height) {
    int newImgSize = newWidth * newHeight;
    int intX = 0, intY = 0, low = 0, high = 0;
    BYTE* tmpImg = (BYTE*)calloc(sizeof(BYTE), newImgSize);
    double stepX = 0.0, stepY = 0.0, realX = 0.0, realY = 0.0;

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
                tmpImg[(i * newHeight + j)] = input[(i * height) + intX];
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
    return output;
}