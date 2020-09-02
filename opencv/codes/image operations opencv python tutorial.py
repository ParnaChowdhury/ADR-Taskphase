import numpy as np
import cv2

img = cv2.imread('testimg.jpg', cv2.IMREAD_COLOR)



img[55,55] = [255,255,255]
px = img[55,55]

roi = img[100:150, 100:150] = [0,0,0]

im_face = img[37:111, 107:197]

img[0:74, 0:90] =im_face



cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows




