# import
import cv2

# 동영상 파일 불러오기
cap = cv2.VideoCapture('/home/seulgi/data/vtest.avi')

frame_size = (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
print('frame_size =', frame_size)

while True:
	retval, frame = cap.read( ) # 프레임 캡처
	if not retval:
		break

	cv2.imshow('frame',frame)

	key = cv2.waitKey(25) # 25/1000 sec 대기
	if key == 27: # Esc
		break
if cap.isOpened():
	cap.release()
cv2.destroyAllWindows()

