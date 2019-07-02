import cv2
import numpy as np

img = np.zeros(shape=(512,512,3), dtype=np.uint8) + 255

pt1 = 100,100
pt2 = 400,400

cv2.rectangle(img,pt1,pt2,(0,0,255),-1)

pt3 = (
