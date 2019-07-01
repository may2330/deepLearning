# 파이썬에서 openCV를 사용하기 위해
import cv2

# 파일이 저장된 경로를 문자열 객체 지정
imageFile = '/home/seulgi/data/lena.jpg'

# BGR포맷으로 읽어서 img 객체에 저장한다.
img = cv2.imread(imageFile) # cv2.IMREAD_COLOR

# Lena.bmp 이름으로 파일을 저장한다.
cv2.imwrite('/home/seulgi/data/Lena.bmp', img)

# Lena.png 이름으로 파일을 저장한다.
cv2.imwrite('/home/seulgi/data/Lena.png', img)

# Lena2.png 이름으로 파일을 저장한다. 0~9사이의 숫자로 압축률을 정한다. 기폴트는 3
cv2.imwrite('/home/seulgi/data/Lena2.png',img, [cv2.IMWRITE_PNG_COMPRESSION, 9])

# Lena.jpg 이름으로 파일을 저장한다. jpg의 품질을 90%로 설정한다. 디폴트는 95%
cv2.imwrite('/home/seulgi/data/Lena2.jpg', img, [cv2.IMWRITE_JPEG_QUALITY, 90])
