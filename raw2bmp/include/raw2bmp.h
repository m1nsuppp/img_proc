#ifndef RAW2BMP_H_
#define RAW2BMP_H_

#include <stdio.h>
#include <stdlib.h>

/* MacOS 64 bits or Linux 64 bits data types, NOT WINDOWS.*/
typedef uint16_t WORD;
typedef uint32_t  DWORD;
typedef int32_t  LONG;
typedef uint8_t  BYTE;

/* Bitmap header structure*/

/* raw data에 붙여줄 Bitmap File Header*/
#pragma pack(1)

typedef struct BMFH {
	WORD   bfType; // type         
	DWORD  bfSize; // 전체 크기 
	WORD   bfReserved1; 
	WORD   bfReserved2;     
	DWORD  bfOffBits; // bmp data 영역의 시작. (offset)    
} BMFH;

typedef struct BMIH {
	DWORD   biSize;           // 구조체 크기 
	LONG    biWidth;          
	LONG    biHeight;         
	WORD    biPlanes;         
	WORD    biBitCount;       // bit depth  
	DWORD   biCompression;    // 압축률  
	DWORD   biSizeImage;      // bitmap 이미지 크기
	LONG    biXPelsPerMeter;   // x방향
	LONG    biYPelsPerMeter;   // y방향
	DWORD   biClrUsed;        
	DWORD   biClrImportant;      
} BMIH;

typedef struct RGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;

#pragma pack()

/* raw 파일을 bmp로 변환하는 함수 */
int Raw2Bmp(char* rawFilePath, DWORD rawWidth, DWORD rawHeight, char* bmpFilePath);

#endif /* RAW2BMP_H_ */