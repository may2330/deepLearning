import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('/home/seulgi/data/color.jpg',cv2.IMREAD_COLOR)

# BGR -> HSV 모드로 전환
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

# HSV에서 BGR로 가정할 범위를 정의함
lower_blue = np.array([110,100,100])
upper_blue = np.array([130,255,255])

lower_green = np.array([50,100,100])
upper_green = np.array([70,255,255])

lower_red = np.array([-10,100,100])
upper_red = np.array([10,255,255])

# HSV 이미지에서 청색만, 또는 초록색만, 또는 빨간색만 추출하기 위한 임계값
mask_blue = cv2.inRange(hsv, lower_blue, upper_blue)
mask_green = cv2.inRange(hsv, lower_green, upper_green)
mask_red = cv2.inRange(hsv, lower_red, upper_red)

# mask와 원본 이미지를 비트 연산함
res1 = cv2.bitwise_and(img, img, mask=mask_blue)
res2 = cv2.bitwise_and(img, img, mask=mask_green)
res3 = cv2.bitwise_and(img, img, mask=mask_red)

#cv2.imshow('original', img)
#cv2.imshow('blue', res1)
#cv2.imshow('green', res2)
#cv2.imshow('red', res3)

# subplots 2x2
fig, ax = plt.subplots(2, 2, figsize=(10,10), sharey=True)
fig.canvas.set_window_title('Sample Pictures')

ax[0][0].axis('off')
ax[0][0].imshow(img, aspect = 'auto')

ax[0][1].axis('off')
ax[0][1].imshow(res1, aspect = 'auto')

ax[1][0].axis("off")
ax[1][0].imshow(res2, aspect = "auto")

ax[1][1].axis("off")
ax[1][1].imshow(res3, aspect = 'auto')

plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0.05, hspace=0.05)
#plt.savefig("/home/seulgi/data/colorExtr.png", bbox_inches='tight')
plt.show()


