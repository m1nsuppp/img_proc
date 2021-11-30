#include "../include/bmp.h"
#include <math.h>

void avgFilter(BYTE* input, BYTE* output, int width, int height, int size){
    float** mask = NULL; 
    mask = (float**)malloc(sizeof(float*) * size); 
    for(int i = 0; i < size;i++) 
        mask[i] = (float*)malloc(sizeof(float) * size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            mask[i][j] = (float)1 / pow(size, 2);
        }
    }

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

    for (int i = 0; i < size; i++) 
        free(mask[i]); 
        
    free(mask);
}

void gaussSmoothFilter(BYTE * input, BYTE * output, int width, int height){
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

void sharpening(BYTE* input, BYTE* output, int width, int height){
    const int size = 3;
    float mask[3][3] = {{-1.0, -1.0, -1.0},
                        {-1.0, 9.0, -1.0},
                        {-1.0, -1.0, -1.0}};

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