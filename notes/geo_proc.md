# Geometric Processing
- input -> Scaling -> output
    - 이 때의 factor는 alpha고, alpha = 1이면, 화면이 1배율 a < 1: 축소, alpha > 1: 확대
- Rotation(90도 clockwise): 픽셀의 위치가 바뀔 뿐, 영상의 사이즈는 유지. 하지만 세로 픽셀의 사이즈와 가로 사이즈의 픽셀은 바뀜.
    - 우리가 보통, 영상 데이터라고 하는 것은 딱 두 가지.
    - 어떤 위치값(Address), 어떤 값(픽셀의 밝기)
    - Rotation 시 당연히 위치의 변화가 생기고 그에 따라 당연히 또 값도 변하게 됨.
- Translation: 영상을 x축으로 얼마, y축으로 얼마. 이동 시킨다는 것.
    - 예를 들어 object를 이동 시키고싶다면, E.D.를 활용해 그 값들을 옮기는데 활용됨. E.D.는 그 자체가 목적이 아니라 수단이라는 것을 또 알 수 있음.
- Rotation, Translation은 픽셀 값을 변화시키는 게 아니라 이동 시키는 것임.
- Scaling은 픽셀 값을 변화시킴.

