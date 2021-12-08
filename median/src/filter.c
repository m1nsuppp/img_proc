#include "../include/bmp.h"
#include "../include/filter.h"

void GaussSmoothFilter3x3(BYTE* input, BYTE* output, int width, int height){
    const int size = 3;
    double mask[size][size] =
//    {
//        1,2,1,
//        2,4,2,
//        1,2,1
//    };
    {
        0.0625, 0.125, 0.0625,
        0.125, 0.25, 0.125,
        0.0625, 0.125, 0.0625,
    };
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

void GaussSmoothFilter5x5(BYTE* input, BYTE* output, int width, int height) {
    const int size = 5;
    double mask[size][size] =
//    {
//        1,4,7,4,1
//        4,16,26,16,4
//        7,26,41,26,7
//        4,16,26,16,4
//        1,4,7,4,1
//    };
    {
        0.003663003663, 0.01465201465, 0.02564102564, 0.01465201465, 0.003663003663,
        0.01465201465, 0.05860805861, 0.09523809524, 0.05860805861, 0.01465201465,
        0.02564102564, 0.09523809524, 0.1501831502, 0.09523809524, 0.02564102564,
        0.01465201465, 0.05860805861, 0.09523809524, 0.05860805861, 0.01465201465,
        0.003663003663, 0.01465201465, 0.02564102564, 0.01465201465, 0.003663003663
    };
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

void MedianFilter3x3(BYTE* input, BYTE* output, int width, int height) {
    BYTE* buffer = NULL;
    buffer = (BYTE*)malloc(sizeof(BYTE) * (9));
    int temp = 0;
    int position = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                output[i * width + j] = (int)(input[i * width + j]);
            }
            else {
                for(int m = -1; m < 2; m++) {
                    for(int n = 0; n < 3; n++) {
                        buffer[position] = (int)(input[(i + m) * width + (j - 1) + n]);
                        position++;
                    }
                }
                position = 0;

                for(int k = 0; k < 9; k++) {
                    for(int l = 0; l < 8; l++) {
                        if(buffer[l] > buffer[l + 1]) {
                            temp = buffer[l];
                            buffer[l] = buffer[l + 1];
                            buffer[l + 1] = temp;
                        }
                    }
                }
                output[i * width + j] = buffer[4];
            }
        }
    }
    free(buffer);
}

void MedianFilter5x5(BYTE* input, BYTE* output, int width, int height) {
    BYTE* buffer = NULL;
    buffer = (BYTE*)malloc(sizeof(BYTE) * (25));
    int temp = 0;
    int position = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(i < 2 || j < 2 || i > height - 3 || j > width - 3) {
                output[i * width + j] = (int)(input[i * width + j]);
            }
            else {
                for(int m = -2; m < 3; m++) {
                    for(int n = 0; n < 5; n++) {
                        buffer[position] = (int)(input[(i + m) * width + (j - 2) + n]);
                        position++;
                    }
                }
                position = 0;

                for(int k = 0; k < 25; k++) {
                    for(int l = 0; l < 24; l++) {
                        if(buffer[l] > buffer[l + 1]) {
                            temp = buffer[l];
                            buffer[l] = buffer[l + 1];
                            buffer[l + 1] = temp;
                        }
                    }
                }
                output[i * width + j] = buffer[13];
            }
        }
    }
    free(buffer);
}