import numpy as np
import cv2

# 트랙바 핸들러
def onChange(pos):
	h = cv2.getTrackbarPos('H','img')
	s = cv2.getTrackbarPos('S','img')
	v = cv2.getTrackbarPos('V','img')
	hsv = cv2.merge((h,s,v))
	print(hsv)
	#img = cv2.cvtColor(hsv,cv2.COLOR_HSV2BGR)
	cv2.imshow('img',img)

# init	
img = cv2.imread('/home/seulgi/data/color.jpg', cv2.IMREAD_COLOR)
cv2.namedWindow('img')
cv2.imshow('img',img)

# 트랙바 생성
cv2.createTrackbar('H','img',0,180,onChange)
cv2.createTrackbar('S','img',0,255,onChange)
cv2.createTrackbar('V','img',0,255,onChange)

# 트랙바 위치 초기화
#cv2.setTrackbarPos('V','img',255)

# BGR -> HSV
hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
h,s,v = cv2.split(hsv)
print(h)

cv2.waitKey()
cv2.destroyAllWindows()
