#include "../include/bmp.h"
#include "../include/hist.h"

int main() {
    BMFH fileHeader;
    BMIH infoHeader;
    RGBQUAD hRGB[256];
    FILE* fp = NULL;
    int hist[256] = {0, };
    int stackHist[256] = {0, };
    
    fp = fopen("../img/map.bmp", "rb");
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

    GetHist(input, hist, infoHeader.biWidth, infoHeader.biHeight);
    CumulativeHist(stackHist, hist);
    HistEqual(input, output, stackHist, infoHeader.biWidth, infoHeader.biHeight);

    fp = fopen("../img/map_hist_equal.bmp", "wb");
    fwrite(&fileHeader, sizeof(BYTE), sizeof(fileHeader), fp);
    fwrite(&infoHeader, sizeof(BYTE), sizeof(infoHeader), fp);
    fwrite(hRGB, sizeof(RGBQUAD), 256, fp);
    fwrite(output, sizeof(BYTE), imgSize, fp);
    fclose(fp);

    free(input);
    free(output);        

    return 0;
}