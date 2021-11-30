#include "../include/filter.h"
#include <string.h>

int main() {
    BMFH fileHeader;
    BMIH infoHeader;
    RGBQUAD hRGB[256];
    FILE* fp = NULL;
    char outputImg[40] = "..img/";
    int selectNum = 0;
    
    fp = fopen("../img/akiyo_noise.bmp", "rb");
    if(fp == NULL) {
        printf("FILE OPEN ERROR!\n");
        return 0;
    }


    fread(&fileHeader, sizeof(fileHeader), 1, fp);
    fread(&infoHeader, sizeof(infoHeader), 1, fp);
    fread(hRGB, sizeof(RGBQUAD), 256, fp);

    int imgSize = infoHeader.biWidth * infoHeader.biHeight;
    BYTE* input = (BYTE*)calloc(sizeof(BYTE), imgSize);
    BYTE* output = (BYTE*)calloc(sizeof(BYTE), imgSize);
   
    fread(input, sizeof(BYTE), imgSize, fp);
    fclose(fp);

    printf("수행할 작업을 택하세요.\n");
    printf("1. 3 X 3 Median Filtering\n2. 5 X 5 Median Filtering\n3. 3 X 3 Gaussian Filtering\n4. 5 X 5 Gaussian Filtering\n");
    scanf("%d", &selectNum);

    switch(selectNum) {
        case 1 :
        MedianFilter3x3(input, output, infoHeader.biWidth, infoHeader.biHeight);
        strcpy(outputImg, "../img/akiyo_med_3x3.bmp");
        break;

        case 2 : 
        MedianFilter5x5(input, output, infoHeader.biWidth, infoHeader.biHeight);
        strcpy(outputImg, "../img/akiyo_med_5x5.bmp");
        break;

        case 3 :
        GaussSmoothFilter3x3(input, output, infoHeader.biWidth, infoHeader.biHeight);
        strcpy(outputImg, "../img/akiyo_gauss_3x3.bmp");
        break;

        case 4 :
        GaussSmoothFilter5x5(input, output, infoHeader.biWidth, infoHeader.biHeight);
        strcpy(outputImg, "../img/akiyo_gauss_5x5.bmp");
        break;

        default :
        printf("잘못 선택하셨습니다.\n");
        break;
    }
    
    fp = fopen(outputImg, "wb");
    fwrite(&fileHeader, sizeof(BYTE), sizeof(fileHeader), fp);
    fwrite(&infoHeader, sizeof(BYTE), sizeof(infoHeader), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(output, sizeof(BYTE), imgSize, fp);
    fclose(fp);

    free(input);
    free(output);

    return 0;
}