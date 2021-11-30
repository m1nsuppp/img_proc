#include "../include/bmp.h"
#include "../include/conv.h"

int main() {
    BMFH fileHeader;
    BMIH infoHeader;
    RGBQUAD hRGB[256];
    FILE *fp = NULL;
    fp = fopen("../img/blurred_7x7.bmp", "rb");
    if(fp == NULL) {
        printf("FILE OPEN ERROR!\n");
        return -1;
    }

    fread(&fileHeader,sizeof(fileHeader), 1, fp);
    fread(&infoHeader,sizeof(infoHeader), 1, fp);
    fread(hRGB, sizeof(RGBQUAD), 256, fp);
    
    int imgSize = infoHeader.biWidth * infoHeader.biHeight;
    BYTE* input = (BYTE*)calloc(sizeof(BYTE), imgSize);
    BYTE* output = (BYTE*)calloc(sizeof(BYTE), imgSize);
   
    fread(input, sizeof(BYTE), imgSize, fp);
    fclose(fp);
    
    int selectNum = 0;
    int maskNum = 0;

    printf("수행할 작업을 택하세요.\n");
    printf("1. Average Filter\n2. Gaussian Smooth Filter\n3. Sharpening(정수 입력): \n");
    scanf("%d", &selectNum);


    if(selectNum == 1) {
        printf("필터 계수를 입력하세요(정수 입력): ");
        scanf("%d", &maskNum);
        avgFilter(input, output, infoHeader.biWidth, infoHeader.biHeight, maskNum);
    }
    else if(selectNum == 2)
        gaussSmoothFilter(input, output, infoHeader.biWidth, infoHeader.biHeight);
    else if(selectNum == 3) 
        sharpening(input, output, infoHeader.biWidth, infoHeader.biHeight);
    else
        printf("NO PROCESSING\n");
    
    fp = fopen("../img/blurred_7x7_sharpening.bmp", "wb");
    fwrite(&fileHeader, sizeof(BYTE), sizeof(fileHeader), fp);
    fwrite(&infoHeader, sizeof(BYTE), sizeof(infoHeader), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(output, sizeof(BYTE), imgSize, fp);
    fclose(fp);
    
    free(input);
    free(output);
    
    return 0;
}