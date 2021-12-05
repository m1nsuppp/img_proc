#ifndef BMP_H_
#define BMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(2)

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BMFH;

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    int biWidth;
    int biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    int biXPixPerMeter;
    int biYPixPerMeter;
    DWORD biClrUsed;
    DWORD biClrImporant;
} BMIH;

typedef struct RGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;

/* bmp 파일 쓰는 함수 */
void WriteBmp(unsigned char* data, int width, int height);

/* bmp 파일 읽는 함수 */
BYTE* ReadBmp(char* filename);

#endif /* BMP_H_ */