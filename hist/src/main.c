#include "../include/bmp.h"

#define WIDTH 512
#define HEIGHT 512
#define SIZE 512 * 512
#define CLR_DEPTH 255

int main(int argc, char** argv) {
    unsigned char* image = readBmp(argv[1]);
    unsigned char* outHistogram = malloc(sizeof(BYTE) * SIZE);

    // Step 1. image의 histogram 구하기
    int* histogram = (int*)calloc(sizeof(int), CLR_DEPTH); 
    for(int i = 0; i < SIZE; i++){
        histogram[image[i]]++;
    }

    // Step 2 & Step 3. 누적 빈도 구하고, 정규화합 histogram으로 변형.
    float* normalizedSum = (float*)calloc(sizeof(float), CLR_DEPTH);
    for(int i = 0; i < CLR_DEPTH; i++){
        for(int j = 0; j < i + 1; j++){
            normalizedSum[i] += CLR_DEPTH * ((float)histogram[j]) / (SIZE);
        }
    }

    // Step 4. 원본 image에 다시 mapping.
    for(int i = 0; i < SIZE; i++){
        outHistogram[i] = normalizedSum[image[i]];
    }

    writeBmp(outHistogram, WIDTH, HEIGHT);

    return 0;
}