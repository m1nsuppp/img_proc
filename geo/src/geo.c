#include "geo.h"

int limit(int value) {
    return ((value > 255) ? 255 : ((value < 0) ? 0 : value));
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

void ResizeNearest(BYTE* input, BYTE* output, double alpha, int width, int height) {
    int newWidth = alpha * width;
    int newHeight = alpha * height;
    int x = 0, y = 0;
    double rx = 0.0, ry = 0.0;

    for(int j = 0; j < newHeight; j++)
        for(int i = 0; i < newWidth; i++) {
            rx = (double)(width - 1) * i / (newWidth - 1);
            ry = (double)(height - 1) * j / (newHeight - 1);
            x = (int)(rx + 0.5);
            y = (int)(ry + 0.5);

            if(x >= width) {
                x = width - 1;
            }
            if(y >= height) {
                y = height - 1;
            }
            output[j * width + i] = input[y * width + x];
    }
}

void ResizeBilinear(BYTE* input, BYTE* output, double alpha, int width, int height) {
    int newWidth = alpha * width;
    int newHeight = alpha * height;
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    double rx = 0.0, ry = 0.0, p = 0.0, q = 0.0, value = 0.0;

    for (int j = 0; j < newHeight; j++)
    for (int i = 0; i < newWidth; i++)
    {
        rx = (double)(width - 1) * i / (newWidth - 1);
        ry = (double)(height - 1) * j / (newHeight - 1);

        x1 = (int)(rx);
        y1 = (int)(ry);

        x2 = x1 + 1; if (x2 == width) x2 = width - 1;
        y2 = y1 + 1; if (y2 == height) y2 = height - 1;

        p = rx - x1;
        q = ry - y1;

        value = (1. - p) * (1. - q) * input[y1 * width + x1]
            + p * (1. - q) * input[y1 * width + x2]
            + (1. - p) * q * input[y2 * width + x1]
            + p * q * input[y2 * width + x2];

        output[j * width + i] = (BYTE)(limit(value + 0.5));
    }
}