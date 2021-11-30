# 512 x 512 bmp file Histogram Equalization
- 제작자: 강릉원주대학교 전자공학과 20171041 이민섭

# 설계
- 1. image의 histogram 구하기
- 2. histogram 값의 cumulative frequency 구하기
- 3. 계산된 frequency를 이용하여 정규화합 histogram으로 변형
- 4. 정규화합 histogram을 이용하여 원본 image에 다시 mapping.

# Usage
```shell
$ gcc -std=c99 -Wall main.c bmp.c -o main
$ ./main ../img/map.bmp
```