# Convolution & Filtering.
1. 과제 내용
    - 주어진 Test 영상을 입력으로 하여 Convolution Filtering 수행 후 결과 영상 출력
    - Blurring, Sharpening 등의 Filtering 실행
2. 과제 수행 방법
    - Test 영상과 filter 계수의 컨볼루션을 수행하는 함수 작성
---
- 제작자: 강릉원주대학교 전자공학과 20171041 이민섭
- compiler: Clang
### Usage
```shell
$ gcc main.c bmp.c conv.c -o main
$ ./main
```