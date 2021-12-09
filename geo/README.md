# Geometric Processing
- Nearest Neighbor Interpolation
```C
BYTE* NearestInterpolation(BYTE* input, BYTE* output, int newWidth, int newHeight, int width, int height);
```
- Bi-linear Interpolation
```C
BYTE* BilinearInterpolation(BYTE* input, BYTE* output, int newWidth, int newHeight, int width, int height);
```
---
```C
#include "geo.h"
```
---
제작자: 강릉원주대학교 전자공학과 20171041 이민섭