#include "bmp.h"
#include "geo.h"

int main() {
    BMFH fileHeader;
    BMIH infoHeader;
    RGBQUAD hRGB[256];
    FILE* fp = NULL;
    BYTE* input = NULL;
    BYTE* output = NULL;
    int tmpHeight = 0, tmpWidth = 0, addrIndex = 0;
    double alpha = 4;

    fp = fopen("../img/baboon.bmp", "rb");
    if(fp == NULL) {
        printf("FILE OPEN ERROR!\n");
        return 0;
    }

    fread(&fileHeader, sizeof(fileHeader), 1, fp);
    fread(&infoHeader, sizeof(infoHeader), 1, fp);
    fread(hRGB, sizeof(RGBQUAD), 256, fp);
    
    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int imgSize = width * height;

    int newWidth = alpha * width;
    int newHeight = alpha * height;
    int newImgSize = newWidth * newHeight;

    input = (BYTE*)calloc(sizeof(BYTE), imgSize);
    output = (BYTE*)calloc(sizeof(BYTE), newImgSize);
    
    fread(input, sizeof(BYTE), imgSize, fp);
    fclose(fp);

    ResizeNearest(input, output, alpha, width, height);

    fp = fopen("../img/out3.bmp", "wb");
    fwrite(&fileHeader, sizeof(BYTE), sizeof(fileHeader), fp);
    fwrite(&infoHeader, sizeof(BYTE), sizeof(infoHeader), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(output, sizeof(BYTE), newImgSize, fp);
    fclose(fp);

    free(input);
    free(output);

    return 0;
}