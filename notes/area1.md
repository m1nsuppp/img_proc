# Area Processing
- 신호처리를 한다는 것?
    - 1. Spectral Analysis
    - 2. Filtering
- 특정한 픽셀 하나를 처리하는데, 주변의 픽셀까지 연계해서 처리하겠다는 것.
- filter라는 말을 들었을 때, 주파수를 떠올려야한다.
  - 공간 영역에 있는 데이터(물리 데이터)를 주파수 영역으로 바꾸는 Fast Fourier Transform을 통해, 주파수 영역으로 바꾸는게 일반적인 기법.
  - 영상 데이터를 FFT를 통해  주파수 영역으로 바꾼 후, 원하는 필터를 설계하고 필터링을 해준 뒤, IFFT를 통해 다시 공간 영역으로 표현을 해서 영상이라는 것을 우리의 눈으로 보게 된다.
  - 영상은 2D 데이터기 때문에 데이터량이 많고, 주파수가 높다.
  - 영상 데이터를 FFT를 통해 바꿔주면 2배 이상의 Memory가 필요하게 된다(Re, Im, Phase를 담아야하기 때문에).
  - FFT 쓸 때: 100 X 100 영상을 FFT 한다고 하면, 100이상의 bit는 2^7. 즉 7 bit이기 때문에 데이터의 크기를 128 x 128로 변환 후, 남은 공간에 Zero Padding을 해준다. 그리고 데이터가 커지기 때문에 당연히 계산량이 많아진다. 
# **Convolution**
- 이 역시 공간 영역에서 주파수 영역으로 바꿀 수 있다.
- h(m, n) --> convolution mask 또는 filter 계수라 함.
- 컨볼루션은 데이터가 선형이라는 기본 전제 하에 수행.
- Causality여야함. 입력에 의해 나온 출력값은 미래의 데이터에 영향을 받지 않아야한다.
- Blurring: LPF
  - 고주파 부분을 뭉개버림(영상이 번져보임).
- Sharpening: HPF
  - 고주파 부분만 통과시킴(원본 영상의 성분을 두드러지게함).
- Edge Detection: HPF
  - 영상의 윤곽만 잡아내는 것.
- Noise: 고주파신호
- Median Filtering: 위와 달리 비선형 필터(기하학적 필터).
  - Salt & Pepper Noise를 없애는 비선형 필터.
  - Random Noise가 껴있을 때, 이를 제거하기 좋은 필터.
- Convolution이라는 것을 취해서 선형 필터(LPF, BPF, HPF)를 만든다.
  - LPF, BPF, HPF는 Convolution을 수행하는 것(Program)은 똑같고 filter 계수만 다르다.
  - Convolution filter라는 것을 하나 프로그래밍 해놓고, LPF, BPF, HPF를 취할지는 filter 계수만 바꾸면 된다. 
- 컨볼루션 과정에는 화소값과 그 주변 화소값을 마스킹을 씌워서 준비되어있는 컨볼루션 필터의 계수값과 곱해서 덧셈 해주는 것이 필요함.
- 영상에서는 한 장의 이미지 전체를 Causality라고 본다(모두 동일한 시점으로 간주).
- 아키텍처
    - 1. filter mask(== filter 계수 == convolution mask)를 정의해야함(3 X 3, 5 X 5 등 보통 홀수를 씀).
    - 100 x 100 영상에서 filter mask를 3 X 3으로 했으면, 계산량은 100 * 100 * 3 * 3이다.
    - filter mask가 큰 게 좋을 때는 영상 변화가 적을 때이다.
- Digital filter.
    - 크게 두 가지.
    - 1. FIR filter(Finite Impulse Response)
        - Tap 수가 많다: 디지털 필터의 계수를 많이 써야 비교적 원만한 필터의 성능을 낼 수 있다.
        - 구현이 쉽기 때문에 많이 사용됨.
        - Linear Phase Response: 주파수에 상관없이, 항상 filtering을 해주면 동일한 delay를 가지고 출력이 될 수 있다.
    - 2. IIR filter(Infinite Impulse Response)
        - Linear Phase Response를 보장하지 못하기 때문에 주파수마다 delay가 달라질 수 있음.
        - 컨벌루션으로 필터링을 해준다고 하더라도 FFT 필터링 못지않게 정교함을 보여준다.
        - 구현이 어려움.
        - 동영상을 처리해 줄 때에, 장면과 장면의 변환이 필요한 경우가 있는데 이 때 스무스하게 해주고싶다면 IIR 필터를 써주면 사람의 눈으로는 잘 눈치채지 못한다.
    - 디지털 필터를 구현하는 3대 요소
        - 1. Multiplier
        - 2. Adder
        - 3. Delay(Flip Flop)
- 필터 계수(convolution mask or kernel)들에 의해서 가중치가 결정된다.
- 보통 영상처리에 있어서 cutoff frequency와 convolution mask를 결정하는 것이 가장 어렵다고 할 수 있다.
- Raster Scanning: 위 -> 아래 & 좌 -> 우 스캔 방식.
# Digital Filtering
1. 주파수 영역(FFT), 좀 더 정교하게 필터링 가능함. 하지만 FFT라는 연산이 필요하기 때문에, 메모리가 많이 필요하고 연산량이 많이 필요함.
2. 공간 영역(Convolution) 정교함은 떨어지지만, 계산량도 적고 메모리 점유량도 적다.
# Image Boundary에서의 Convolution 개념
- Zero Padding: 기존에 없던 값을 0으로 처리하는 것.
- No Processing: 기존에 없던 값에 대해서는 컨볼루션을 수행하지 않는 것.
- Duplication of boundary Pixel Value: 옆에 있는 값을 그대로 복사해서 쓰는 것.
- 영상의 가장자리는 눈에 잘 안들어오기 때문에 잘못 처리한다고 해서 크게 문제 될 일은 없지만, 엔지니어로서 디지털 필터링을 해주어야하기 때문에 위 3가지 기법 중 하나를 사용해야함. zero padding이 가장 손 쉬운 방법이라 권장함.
# Digital Filter Design Steps
- 스무스하게: LPF, 선명하게: HPF 이에 따라 필터 계수를 결정해야함.
- 1. 필터의 요구사항
- 2. 적절한 필터 계수 결정
- 3. FIR or IIR 선택 
- 4. 구현

# Blurring
- LPF의 대표적인 예. 엣지들이 뭉개짐(번짐). 정교한 엣지: 고주파 영역. 같은 색깔로 연속적 연결: 저주파 영역.
- (Moving)Average filter
- 어떤 한 화소값에서 멀어질 수록 correlation이 떨어짐.
- 근데 Average filter는 똑같은 correlation으로 함, **가중치가 동일**. --> filter mask를 키울 수록 블러링 효과가 커짐.
- blurring의 필터 계수를 만드는 법은 각각의 필터 개수를 다 더하면 1이 된다.
    - N x N: 한 cell이 1/(N x N)
- Gaussian Smooth Filter
    - 가우시안 분포를 이용해 필터 계수를 만드는 것.
    - 정한 픽셀이 가장 값이 높고 멀어질 수록 가중치가 낮아지는 필터.
    - 마찬가지로 cell을 모두 더 하면 1임.

# Sharpening
- 대표적인 HPF.
- 마찬가지로 모두 더하면 1이지만, (+), (-)가 공존함. --> HPF
- 선명함이 증가함. 디테일이 두드러진다? 같음. 내 생각엔.
- 더한게 0이 나오고 부호가 바뀌고 필터링한 값이 (-) 값이 나온다? 클리핑을 해줘야할까? 그럼 전부 0이 되어 필터링한 결과가 그저 검은 영상이 나올 수가 있음. 따라서 필터링한 값에 대해서 절대값을 씌워 디피해준다.
    - 엣지를 찾는다던지, 특정한 영상점을 찾는다던지 하는 어떤 포인트를 찾기 위해 많이 쓰임.
- HPF를 쓸 때, 필터 계수를 보고 더해서 0이 나오면 아 이건 어떤 작업을 위한 참조 영상을 만들어내기 위해 쓰는거구나 알면 됨.
- 더하면 1인 필터는 입력이 들어가서 필터를 거쳐서 출력이 나왔을 때, 영상으로 활용하면 되는 것이고, 더하면 0이 나오는 필터는 출력값을 영상으로 활용하는 것이 아닌 **고주파 성분이 어디에 있는지 찾아낼 때 쓰이는 것**
# 과제
- conv. filter 프로그램을 하나 만들고 필터 계수만 바꾸면 됨.