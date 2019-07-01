import cv2


imageFile = '/home/seulgi/data/lena.jpg'

img = cv2.imread(imageFile)
img2 = cv2.imread(imageFile,0)

cv2.imshow('Lena color',img)
cv2.imshow('lena grayscale',img2)

cv2.waitKey()
cv2.destroyAllWindows()


