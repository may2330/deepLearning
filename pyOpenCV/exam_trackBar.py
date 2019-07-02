import cv2

def nothing(x):
	low = cv2.getTrackbarPos('low threshold', 'Canny')
	high = cv2.getTrackbarPos('high threshold', 'Canny')
	img_canny = cv2.Canny(img_gray, low, high)
	cv2.imshow('Canny', img_canny)

cv2.namedWindow('Canny')

img_gray = cv2.imread('/home/seulgi/data/color.jpg', cv2.IMREAD_GRAYSCALE)

cv2.createTrackbar('low threshold', 'Canny', 0, 1000, nothing)
cv2.createTrackbar('high threshold', 'Canny', 0, 1000, nothing)

cv2.setTrackbarPos('low threshold', 'Canny', 50)
cv2.setTrackbarPos('high threshold', 'Canny', 150)

cv2.waitKey()
cv2.destroyAllWindows()
