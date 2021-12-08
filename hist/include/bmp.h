#ifndef BMP_H_
#define BMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#pragma pack(2)

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
#pragma pack(pop)

typedef struct RGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;

#pragma pack()

#endif /* BMP_H_ */