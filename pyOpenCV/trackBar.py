import numpy as np
import cv2

# 트랙바 핸들러
def onChange(pos):
	h1 = cv2.getTrackbarPos('H1','img')
	h2 = cv2.getTrackbarPos('H2','img')
	s1 = cv2.getTrackbarPos('S1','img')
	s2 = cv2.getTrackbarPos('S2','img')
	v1 = cv2.getTrackbarPos('V1','img')
	v2 = cv2.getTrackbarPos('V2','img')

	mask_h = cv2.inRange(hsv,(h1,s1,v1),(h2,s2,v2))
	res1 = cv2.bitwise_and(hsv,hsv,mask=mask_h)
	res1 = cv2.cvtColor(res1, cv2.COLOR_HSV2BGR)

	cv2.imshow('img',res1)

def onChangeH(pos):
	h = cv2.getTrackbarPos('H','img')
	h1 = h - 10
	h2 = h + 10
	mask_h = cv2.inRange(hsv, (h1,0,0), (h2,255,255))
	res1 = cv2.bitwise_and(hsv, hsv, mask=mask_h)
	res1 = cv2.cvtColor(res1, cv2.COLOR_HSV2BGR)

	cv2.imshow('img',res1)
	print("Change!!!!!!!!!!!")
def onChangeS(pos):
	s = cv2.getTrackbarPos('S', 'img')
	s1 = s - 10
	s2 = s + 10
	mask_s = cv2.inRange(hsv, (0,s1,0), (180,s2,255))
	res2 = cv2.bitwise_and(hsv, hsv, mask=mask_s)
	res2 = cv2.cvtColor(res2, cv2.COLOR_HSV2BGR)
	
	cv2.imshow('img',res2)
	print("나도 됬당.")

def onChangeV(pos):
        v = cv2.getTrackbarPos('V', 'img')
        v1 = v - 10
        v2 = v + 10
        mask_v = cv2.inRange(hsv, (0,0,v1), (180,255,v2))
        res3 = cv2.bitwise_and(hsv, hsv, mask=mask_v)
        res3 = cv2.cvtColor(res3, cv2.COLOR_HSV2BGR)

        cv2.imshow('img',res3)
        print("나도 됬당.")
# init	
cv2.namedWindow('img')
img = cv2.imread('/home/seulgi/data/color.jpg', cv2.IMREAD_COLOR)
hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
cv2.imshow('img',img)

# 트랙바 생성
cv2.createTrackbar('H1','img',0,180,onChange)
cv2.createTrackbar('H2','img',0,180,onChange)
cv2.createTrackbar('S1','img',0,255,onChange)
cv2.createTrackbar('S2','img',0,255,onChange)
cv2.createTrackbar('V1','img',0,255,onChange)
cv2.createTrackbar('V2','img',0,255,onChange)

# 트랙바 위치 초기화
cv2.setTrackbarPos('H2','img',180)
cv2.setTrackbarPos('S2','img',255)
cv2.setTrackbarPos('V2','img',255)

cv2.waitKey()
cv2.destroyAllWindows()
