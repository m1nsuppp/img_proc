#ifndef BMP
#define BMP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint16_t WORD;
typedef uint32_t  DWORD;
typedef int32_t  LONG;
typedef uint8_t  BYTE;

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

/* bmp 파일 쓰는 함수 */
void writeBmp(unsigned char* data, int width, int height);

/* bmp 파일 읽는 함수 */
BYTE* readBmp(char* filename);

#endif /* BMP_H_ */