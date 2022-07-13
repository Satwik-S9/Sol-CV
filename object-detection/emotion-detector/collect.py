import os
import time
import uuid
import cv2 as cv

IMG_PATH = os.path.join("data", "images")
labels = ["awake", "sleepy", "happy", "sad"]
num_imgs = 32
cv.namedWindow("Image Collection Window", cv.WINDOW_AUTOSIZE)

cam = cv.VideoCapture(0)
for label in labels:
    print(f"Collecting images for {label} ...")

    for img_num in range(num_imgs):
        print(f"Collecting images for {label}, Image Number: {img_num}")
        # reading webcam feed
        ret, frame = cam.read()
        
        # setting up image name
        img_name = os.path.join(IMG_PATH, label+'-'+str(uuid.uuid1())+'.jpg')
        
        # saving the images
        cv.imwrite(img_name, frame)
        cv.imshow("Image Collection Window", frame)
        time.sleep(2)

        if cv.waitKey(10) & 0xFF == ord('q'):
            break

cam.release()
cv.destroyAllWindows()