# 파이썬에서 openCV를 사용하기 위해
import cv2

# matplotlib 패키지에서 pyplot를 plt 라는 이름으로 임포트 한다.
from matplotlib import pyplot as plt

# BGR포맷으로 읽어서 imgBGR1~4 객체에 저장한다.
path = '/home/seulgi/data/'
imgBGR1 = cv2.imread(path+'orange.jpg')
imgBGR2 = cv2.imread(path+'apple.jpg')
imgBGR3 = cv2.imread(path+'baboon.jpg')
imgBGR4 = cv2.imread(path+'lena.jpg')

# 이미지 사이즈 변경
imgBGR1 = cv2.resize(imgBGR1, dsize=(512,512), interpolation=cv2.INTER_AREA)
imgBGR2 = cv2.resize(imgBGR2, dsize=(512,512), interpolation=cv2.INTER_AREA)
imgBGR3 = cv2.resize(imgBGR3, dsize=(512,512), interpolation=cv2.INTER_AREA)
imgBGR4 = cv2.resize(imgBGR4, dsize=(512,512), interpolation=cv2.INTER_AREA)

# 컬러 순서 변환: BGR -> RGB
imgRGB1 = cv2.cvtColor(imgBGR1, cv2.COLOR_BGR2RGB)
imgRGB2 = cv2.cvtColor(imgBGR2, cv2.COLOR_BGR2RGB)
imgRGB3 = cv2.cvtColor(imgBGR3, cv2.COLOR_BGR2RGB)
imgRGB4 = cv2.cvtColor(imgBGR4, cv2.COLOR_BGR2RGB)

# subplots 2x2 총 4개로 설정하고 Window를 (10,10) 사이즈로 정의하고,
# window의 이름을 ‘Sample Pictures’로 정의 한다.
fig, ax = plt.subplots(2, 2, figsize=(10,10), sharey=True)
fig.canvas.set_window_title('Sample Pictures')

# 왼쪽 위 Window의 좌표 축을 ‘off’하고,
# imgRGB1(orange이미지) 비율을 ‘auto’로 설정한다.
ax[0][0].axis('off')
ax[0][0].imshow(imgRGB1, aspect = 'auto')

# 오른쪽 위 Window의 좌표 축을 ‘off’하고,
# imgRGB2(apple이미지) 비율을 ‘auto’로 설정한다.
ax[0][1].axis('off')
ax[0][1].imshow(imgRGB2, aspect = 'auto')

# 왼쪽 아래 Window의 좌표 축을 ‘off’하고,
# imgRGB3(baboon이미지) 비율을 ‘auto’로 설정한다.
ax[1][0].axis("off")
ax[1][0].imshow(imgRGB3, aspect = "auto")

# 오른쪽 아래 Window의 좌표 축을 ‘off’하고,
# imgRGB3(lena이미지) 비율을 ‘auto’로 설정한다.
ax[1][1].axis("off")
ax[1][1].imshow(imgRGB4, aspect = 'auto')

# 주어진 사이즈의 Window에서 크기를 최대로 하고,
# sub window간의 공간을 가로(wspace)=0.05, 세로(hspace)=0.05로 설정한다.
plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0.05, hspace=0.05)
plt.savefig('/home/seulgi/data/0206.png', bbox_inches='tight')
plt.show()
