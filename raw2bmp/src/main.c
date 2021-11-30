#include "../include/raw2bmp.h"

#define PATH_LEN 20
/* 목표: 256 x 256 8bits/pixel Lena.raw를 Lena.bmp로 */

int main(int argc, char** argv) {
    char rawFilePath[PATH_LEN] = "../img/Lena.raw";
    char bmpFilePath[PATH_LEN] = "../img/Lena.bmp";

    DWORD width = 256, height = 256;

    Raw2Bmp(rawFilePath, width, height, bmpFilePath);

    return 0;
}