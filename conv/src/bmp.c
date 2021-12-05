#include "../include/bmp.h"

/* bmp 파일 읽는 함수 */
BYTE* ReadBmp(char* fileName){

    FILE* fpBmp = fopen(fileName, "rb");

    int width, height, offset;

   
    fseek(fpBmp, 18, SEEK_SET);
    fread(&width, 4, 1, fpBmp);
    fseek(fpBmp, 22, SEEK_SET);
    fread(&height, 4, 1, fpBmp);
    fseek(fpBmp, 10, SEEK_SET);
    fread(&offset, 4, 1, fpBmp);

    BYTE* data = (BYTE*)malloc(sizeof(BYTE) * height * width);
    fseek(fpBmp, offset, SEEK_SET);
    fread(data, sizeof(unsigned char), height * width, fpBmp);

    fclose(fpBmp);

    return data;
}

/* bmp 파일 쓰는 함수 */
void WriteBmp(unsigned char* data, int width, int height){
    BMFH fileHeader;
    BMIH infoHeader;    

    fileHeader.bfType = 0x4D42; // 'BM'
    fileHeader.bfSize = width * height + 54;
    fileHeader.bfOffBits = 1078;

    infoHeader.biSize = 40;
    infoHeader.biWidth = width;
    infoHeader.biHeight = height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 8;
    infoHeader.biCompression = 0;
    infoHeader.biSizeImage = width * height;
    infoHeader.biXPixPerMeter = 0;
    infoHeader.biYPixPerMeter = 0;
    infoHeader.biClrUsed = 256;
    infoHeader.biClrImporant = 0;

    char padding[2];

    BYTE* colorTable = (BYTE*)malloc(1024);
    for(int i = 0; i < 256; i++) {
        colorTable[i * 4] = (BYTE)i;
        colorTable[i * 4 + 1] = (BYTE)i;
        colorTable[i * 4 + 2] = (BYTE)i;
        colorTable[i * 4 + 3] = 0;
    }

    FILE* fpOut = fopen("../img/baboon_blur_3x3avg.bmp", "w+");
    fwrite((void*)&fileHeader.bfType, 1, 2, fpOut);
    fwrite((void*)&fileHeader, 1, 12, fpOut);
    fwrite((void*)&infoHeader, 1, 40, fpOut);
    fwrite((void*)colorTable, 1, 1024, fpOut);
    fwrite((void*)data, 1, width * height, fpOut);
    fwrite((void*)&padding,1, 2, fpOut);
    fclose(fpOut);
}