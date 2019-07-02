import cv2
import numpy as np

# 배경 shape(행,열) 행-> 세로
img = np.zeros(shape=(512,512,3), dtype=np.uint8) + 255

# 사각형
cv2.rectangle(img,(100,100),(400,400),(0,0,255),2)

# 선
# pt1 = 120,50
# pt2 = 250,450
cv2.line(img,(110,50),(250,450),(255,0,0),2)

# 선과 사각형 만나는 점
imgRect = (100,100,300,300) # (x1,y1,x2-x1,y2-y1)
retval,rpt1,rpt2 = cv2.clipLine(imgRect,(110,50),(250,450))
if retval:
	cv2.circle(img,rpt1,radius=3,color=(0,255,0),thickness=-1)
	cv2.circle(img,rpt2,radius=3,color=(0,255,0),thickness=-1)

cv2.imshow('img',img)
cv2.waitKey()
cv2.destroyAllWindows()
