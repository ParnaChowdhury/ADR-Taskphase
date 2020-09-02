import cv2
import numpy as np
import matplotlib.pyplot as plt


img = cv2.imread('testimg.jpg',0)
#IMREAD_COLOR = 1
#IMREAD_UNCHANGED = -1

#cv2.imshow('image', img)
#cv2.waitKey(0)
#cv2.destroyAllWindows()

plt.imshow(img,cmap='gray', interpolation='bicubic')
plt.xticks([]),plt.yticks([])
plt.plot([100,200,300],[200,300,400],'c',linewidth=5)
plt.show()

cv2.imwrite('imgray.png',img)
