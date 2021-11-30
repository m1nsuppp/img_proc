#include "../include/raw2bmp.h"

/* raw 파일을 bmp 파일로 변환해주는 함수. */
int Raw2Bmp(char* rawFilePath, DWORD rawWidth, DWORD rawHeight, char* bmpFilePath) {
	FILE* raw = NULL; 
	FILE* bmp = NULL;
	BMFH fileHeader;
	BMIH infoHeader;
	RGBQUAD rgb[256];
	DWORD dwRawSize = 0;
	DWORD dwBmpSize = 0;
	DWORD dwLine = 0;
	long lCount = 0;
	char* pData = NULL;

	raw = fopen(rawFilePath, "rb");
	if(raw == NULL) {
		printf("FILE OPEN ERROR!\n");
		return 0;
	}
	bmp = fopen(bmpFilePath, "wb");

	fileHeader.bfType = 0x4D42; // 'BM'
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(rgb) + sizeof(BMFH) + sizeof(BMIH);

	infoHeader.biSize = sizeof(BMIH);
	infoHeader.biWidth = (DWORD)rawWidth;
	infoHeader.biHeight = (DWORD)rawHeight;
	infoHeader.biPlanes = 1;
	infoHeader.biBitCount = 8; // 흑백 이미지 8 bits.
	infoHeader.biCompression = 0;
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;

	dwLine = ((((infoHeader.biWidth * infoHeader.biBitCount) + 31) & ~31) >> 3); // 영상 가로길이를 4바이트의 배수로 만들어주기.
	dwBmpSize = dwLine * infoHeader.biHeight;
	infoHeader.biSizeImage = dwBmpSize; // 이미지 크기 (BMP Data 부분만)
	fileHeader.bfSize = dwBmpSize + fileHeader.bfOffBits + 2; // 최종 전체 크기 할당.
	dwRawSize = infoHeader.biWidth * infoHeader.biHeight;
    pData = (char *)malloc(sizeof(char) * dwRawSize + 16);  // 64bit 운영체제, 컴파일러 사용 중 --> 포인터의 크기는 8 bytes.

	if(pData) {
		fread(pData, 1, dwRawSize, raw); 

		for(int i = 0; i < 256; i++) {
			rgb[i].rgbRed = (BYTE)(i % 256);
			rgb[i].rgbGreen = rgb[i].rgbRed;
			rgb[i].rgbBlue = rgb[i].rgbRed;
			rgb[i].rgbReserved = 0; 
		}

		fwrite((char *)&fileHeader, 1, sizeof(BMFH), bmp);
		fwrite((char *)&infoHeader, 1, sizeof(BMIH), bmp);
		fwrite((char *)rgb, 1, sizeof(rgb), bmp);

		lCount = dwRawSize;

		for (lCount -= (long)infoHeader.biWidth; lCount >= 0; lCount -= (long)infoHeader.biWidth) {
			fwrite((pData + lCount), 1, (long)dwLine, bmp);
		}
		free(pData);
	}

	fclose(raw);
	fclose(bmp);
	

	return 1;
}