#include "../include/bmp.h"
#include "../include/conv.h"

#define LEN 40

int main() {
    BMFH fileHeader;
    BMIH infoHeader;
    RGBQUAD hRGB[256];
    FILE *fp = NULL;
    char inputFile[LEN];
    char outputFile[LEN];
    
    printf("test 영상을 입력하세요: ");
    scanf("%s", inputFile);
    fp = fopen(inputFile, "rb");
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
    printf("1. Average Filter\n2. Gaussian Smooth Filter\n3. Sharpening\n4. Sobel\n(정수 입력): ");
    scanf("%d", &selectNum);


    if(selectNum == 1) {
        printf("필터 계수를 입력하세요(정수 입력): ");
        scanf("%d", &maskNum);
        AvgFilter(input, output, infoHeader.biWidth, infoHeader.biHeight, maskNum);
    }
    else if(selectNum == 2)
        GaussSmoothFilter(input, output, infoHeader.biWidth, infoHeader.biHeight);
    else if(selectNum == 3) 
        Sharpening(input, output, infoHeader.biWidth, infoHeader.biHeight);
    else if(selectNum == 4) {
        SobelX(input, output, infoHeader.biWidth, infoHeader.biHeight);
        SobelY(input, output, infoHeader.biWidth, infoHeader.biHeight);
    }
    else
        printf("NO PROCESSING\n");
    
    printf("출력 영상 파일 이름을 입력하세요 : ");
    scanf("%s", outputFile);
    fp = fopen(outputFile, "wb");
    fwrite(&fileHeader, sizeof(BYTE), sizeof(fileHeader), fp);
    fwrite(&infoHeader, sizeof(BYTE), sizeof(infoHeader), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(output, sizeof(BYTE), imgSize, fp);
    fclose(fp);
    
    free(input);
    free(output);
    
    return 0;
}