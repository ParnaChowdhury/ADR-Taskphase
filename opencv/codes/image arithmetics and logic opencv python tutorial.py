import numpy as np
import cv2

img1 = cv2.imread('im1.png')
img2 = cv2.imread('im2.png')

#add = img1+img2
#cv2.imshow('add',add)

#weighted = cv2.addWeighted(img1, 0.6, img2, 0.4, 0)
#cv2.imshow('weighted',weighted)

img3 = cv2.imread('pylogo.png')

rows,cols,channels = img3.shape
roi = img1[0:rows,0:cols]

img3gray = cv2.cvtColor(img3, cv2.COLOR_BGR2GRAY)
ret, mask = cv2.threshold(img3gray, 220, 255, cv2.THRESH_BINARY_INV)

#cv2.imshow('mask',mask)

mask_inv = cv2.bitwise_not(mask)

img1_bg = cv2.bitwise_and(roi, roi, mask=mask_inv)
img3_fg = cv2.bitwise_and(img3,img3,mask=mask)

dst= cv2.add(img1_bg,img3_fg)

img1[0:rows,0:cols] = dst

cv2.imshow('res',img1)
cv2.imshow('mask_inv',mask_inv)
cv2.imshow('img1_bg',img1_bg)
cv2.imshow('img3_fg',img3_fg)
cv2.imshow('dst',dst)

cv2.imwrite('res.png',img1)
cv2.imwrite('mask_inv.png',mask_inv)
cv2.imwrite('img1_bg.png',img1_bg)
cv2.imwrite('im3_bg.png',img3_fg)
cv2.imwrite('dst.png',dst)

cv2.waitKey(0)
cv2.destroyAllWindows()


