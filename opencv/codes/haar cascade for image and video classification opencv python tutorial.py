import numpy as np
import cv2

#ready made watch-cascade has been used.

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')
watch_cascade = cv2.CascadeClassifier('watch-cascade.xml')

cap = cv2.VideoCapture(0)

while 1:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    
    
    watches = watch_cascade.detectMultiScale(gray, 50, 50)
    
    
    for (x,y,w,h) in watches:
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,255,0),2)
        #cv2.putText(image, 'Watch', (x, y), font, 0.5, (255, 255, 0), 2, cv2.LINE_AA)


    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        eyes = eye_cascade.detectMultiScale(roi_gray)
        for (ex,ey,ew,eh) in eyes:
            cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
            #cv2.putText(roi_color, 'Eyes', (ex, ey), font, 0.5, (0, 255, 0), 2, cv2.LINE_AA)

    cv2.imshow('img',img)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()
