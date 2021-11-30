# Median Filter
1. 과제 내용
    - 주어진 Test 영상을 입력으로 하여 Median Filtering(3x3 , 5x5)을 수행 한다.
    - 같은 Mask 크기의 Gaussian Filtering 영상과 비교한다.

2. 과제 수행 방법
    - Mask 크기를 정하고 선택한 픽셀과 주변 픽셀을 한 배열에 저장한다.
    - 배열 내에서 오름차순으로 정렬하고 기하학적 중간값을 찾는다.
---
- 제작자: 강릉원주대학교 전자공학과 20171041 이민섭
- compiler: clang
### Usage
```shell
$ gcc main.c bmp.c filter.c -o main
$ ./main
```