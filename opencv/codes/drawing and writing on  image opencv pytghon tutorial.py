import numpy as np
import cv2

im = cv2.imread('testimg.jpg',cv2.IMREAD_COLOR)


cv2.line(im,(0,0), (150,150), (255,255,255), 15)
cv2.rectangle(im, (15,25), (200,150), (0,255,0), 5)
cv2.circle(im, (100,63), 55, (0,0,255), -1)

pts= np.array([[10,5],[20,30],[70,20],[50,10]], np.int32)
pts= pts.reshape((-1,1,2))
cv2.polylines(im, [pts], True, (0,255,255), 3 )

font = cv2.FONT_HERSHEY_SIMPLEX
cv2.putText(im, 'OpenCV Tuts!', (0,500), font, 1, (200,255,255), 3, cv2.LINE_AA  )

cv2.imshow('output',im)
cv2.waitKey(0)
cv2.destroyAllWindows()
