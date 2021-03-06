# ADR-Taskphase

## Computer Vision using OpenCV 
* [OpenCV with Python Intro and loading Images](#Intro_and_loading_Images)
* [Loading Video Source OpenCV](#Loading_Video_Source)
* [Drawing and Writing on Image](#Drawing_and_writing)
* [Image Operations](#Image_Operations)
* [Image arithmetics and Logic ](#Image_arithmetics_and_Logic )
* [Thresholding OpenCV](#Thresholding)
* [Colour Filtering](#Colour_filtering)
* [Blurring and Smoothing](#Blurring_and_Smoothing)
* [Morphological Transformations](#Morphological_Transformations)
* [Canny Edge Detection and Gradients](#Canny_Edge_Detection_and_Gradients)
* [Template Matching](#Template_Matching)
* [GrabCut Foreground Extraction](#GrabCut_Foreground_Extraction)
* [Corner Detection](#Corner_Detection)
* [Feature Matching (Homography) Brute Force ](#Feature_Matching)
* [MOG Background Reduction](#MOG_Background_Reduction)
* [Haar Cascade Object Detection Face & Eye](#Haar_Cascade_Object_Detection_Face_&_Eye)
* [Making your own Haar Cascade](#Making_your_own_Haar_Cascade)
* [Haar Cascade For Image and Video Object Classification](#Haar_Cascade_For_Image_and_Video_Object_Classification)


The goal is to follow along the sentdex's "Image analysis using opencv" tutorials and document the corresponding codes.
The code is documented [here](https://github.com/ParnaChowdhury/ADR-Taskphase/tree/master/opencv/codes) and the playlist can be found [here](https://www.youtube.com/playlist?list=PLQVvvaa0QuDdttJXlLtAJxJetJcqmqlQq).

OpenCV could be used for all sorts of image and video analysis like facial recognition and and detection, license plate reading, photo editing, advanced robotic vision, optical character recognition, and a lot more. Here, the task is performed using the python language.

### <a name="Intro_and_loading_Images"></a>OpenCV with Python Intro and loading Images
* IMREAD_COLOR loads the image in the BGR 8-bit format.
* IMREAD_UNCHANGED loads the image as is (including the alpha channel if present)
* IMREAD_GRAYSCALE loads the image as an intensity one
* cv2.imshow is used to show the image.
* cv2.waitkey() is used to determine how long should it wait for a user input. It accepts a single parameter in milliseconds. Zero means to wait forever.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/opencv%20with%20python%20intro%20and%20loading%20images%20tutorial.py)

### <a name="Loading_Video_Source"></a>Loading Video Source OpenCV 
* cv2.VideoCapture() is used to return video from a webcam
* ret and frame being defined as the cap.read(). Basically, ret is a boolean regarding whether or not there was a return at all, at the frame is each frame that is returned.
* cv2.cvtColor() is used to convert to gray using BGR2GRAY.
* cap.release() releases the video
* cv2.destroyAllWindows() closes all the imshow windows.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/loading%20video%20source%20opencv%20python%20tutorial.py)

### <a name="Drawing_and_writing"></a>Drawing and Writing on Image
* cv2.line() takes the image, start coordinates, end coordinates, color (bgr), line thickness as parameters.
* cv2.rectangle() takes the image, the top left coordinate, bottom right coordinate, color, and line thickness as parameters.
* cv2.circle() takes the image, the center of the circle, the radius, color, and the thickness as parameters. -1 thickness outputs a filled in object.
* cv2.putText() takes image, text string, coordinates of bottom-left corner of the string, font, font-scale, colour, thickness and line-type as the parameters.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/drawing%20and%20writing%20on%20%20image%20opencv%20pytghon%20tutorial.py)

### <a name="Image_Operations"></a>Image Operations
* Here, the code is used to sccess and modify the pixel values and the region of image.
* Image properties can also be accessed using img.shape, img.size, img.dtype etc.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/image%20operations%20opencv%20python%20tutorial.py)

### <a name="Image_arithmetics_and_Logic"></a>Image Arithmetics and Logic 
* Here, we superimpose two equal sized images by simple addition and then by using cv2.addWeighted() which takes the first image, its weight, second image, its weight and measurement of light as parameters. And then we compare the results.
* Then we take a smaller image and add it to a larger one by ROI replacement.
* We used cv2.threshold() to convert all pixels to either black or white depending on threshold value.
* We access the required part of the image using bitwise operations. They are of the form cv2.bitwise_and/or/not/xor() and can accept image-source 1, image-source 2, destination and mask as parameters.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/image%20arithmetics%20and%20logic%20opencv%20python%20tutorial.py)


### <a name="Thresholding"></a>Thresholding OpenCV
* Thresholding converts everything into black and white depending upon the threshold variable in a greyscale image. If image is not greyscale, thresholding can still be done but there will be colour. It is done using cv2.threshold() and accepts parameters image, threshold value, maximum value, type of threshold.
* Then we try Adaptive Thresholding where the threshold value of a pixel is depended on the region around it. so in a picture, we get multiple threshold values for multiple regions which gives better results.
* Further, there is Otsu's method which determines the optimal threshold value automatically from the image histogram.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/thresholding%20opencv%20python%20tutorial.py)

### <a name="Colour_filtering"></a>Colour Filtering
* Here colours are filtered out by converting colours to Hue Saturation Values. These filters can also be produced using BGR values but HSV points out to a more specific colour so colour separation is easier.
* By hit and trial, we find the lower bound and upper bound range of colours in one of the colour spaces and then, we create a mask accordingly.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/colour%20filtering%20opencv%20python%20tutorial.py)

### <a name="Blurring_and_Smoothing"></a>Blurring and Smoothing
* Blurring and Smoothing is done to eleminate noise from the filters.
* Simple smoothing is done by taking the average of all pixels in the kernel area and then replacing the central element with this.
* Gaussian Blurring is done with the function, cv2.GaussianBlur(). It uses a gaussian kernel instead of a normal one.
* Median Blurring is done using the function cv2.medianBlur() which computes the median of all the pixels under the kernel window and the central pixel is replaced with this median value.
* In the Gaussian and simple filters, the filtered value for the central element can be a value which may not exist in the original image. However this is not the case in median filtering, since the central element is always replaced by some pixel value in the image. therefore, median blurring is more effective in reducing noise.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/blurring%20and%20smoothing%20opencv%20python%20tutorial.py)

### <a name="Morphological_Transformations"></a>Morphological Transformations
* cv2.erode() is used for erosion. It erodes away the boundaries of foreground object. basically, A kernel is convolved with the image. A pixel in the original image (either 1 or 0) will be considered 1 only if all the pixels under the kernel is 1, otherwise it is made zero (eroded). Thus all the pixels near boundary will be discarded depending upon the size of kernel. So the thickness or size of the foreground object decreases or simply white region decreases in the image.
* cv2.dilate()  is used for dilation. It is the oppsite of erosion. Here, a pixel element in the original image is ‘1’ if atleast one pixel under the kernel is ‘1’.
It increases the white region in the image or size of foreground object increases.
* Opening is done by cv2.MORPH_OPEN. It is erosion followed by dilation. Opening eliminates thin protrusions and salt noise
* Closing is done by cv2.MORPH_CLOSE. it is reverse of opening i.e. dilation follwed by erosion. Closing closes the holes/gaps present in the object while keeping the initial object size the same

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/morphological%20transformations%20opencv%20python%20tutorial.py)

### <a name="Canny_Edge_Detection_and_Gradients"></a>Canny Edge Detection and Gradients
* In Canny Edge Detection, first, it performs noise reduction on the image. Then, it uses the first derivative at each pixel to find edges. The logic behind this is that the point where an edge exists, there is an abrupt intensity change, which causes a spike in the first derivative's value, hence making that pixel an 'edge pixel'. Finally, it performs hysteresis thresholding making use of two threshold values instead of one. The reason behind that is, if the threshold value is too high, we might miss some actual edges (true negatives) and if the value is too low, we would get a lot of points classified as edges that actually are not edges (false positives). One threshold value is set high, and one is set low. All points which are above the 'high threshold value' are identified as edges, then all points which are above the low threshold value but below the high threshold value are evaluated; the points which are close to, or are neighbors of, points which have been identified as edges, are also identified as edges and the rest are discarded.
* It is done using cv2.Canny().

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/canny%20edge%20detection%20and%20gradients%20opencv%20python%20tutorials.py)

### <a name="Template_Matching"></a>Template Matching
* We use Template Matching to find identical regions of an image that match a template we provide, given a certain threshold. It is done using cv2.matchTemplate().
* It compares the template image against the source image by sliding it, one pixel at a time and then comparing it at each location. Multiple images of the same template could be used to reduce no. of false positives.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/template%20matching%20opencv%20python%20tutorial.py)

### <a name="GrabCut_Foreground_Extraction"></a>GrabCut Foreground Extraction
* Here, we load in the image, create a mask, specify the background and foreground model and then define rect, the rectangle which encases the main object.
* Then we use cv2.grabCut, which takes the input image, then the mask, then the rectangle for our main object, the background model, foreground model, the amount of iterations to run, and the mode as parameters.
* Then, the mask is changed so that all 0 and 2 pixels are converted to the background, where the 1 and 3 pixels are now the foreground. Then, we multiply with the input image, and we get our final result.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/grab%20cut%20foreground%20extraction%20opencv%20python%20tutorials.py)

### <a name="Corner_Detection"></a>Corner Detection
* First we load the image, convert to gray, then to float32. Next, we detect corners with the cv2.goodFeaturesToTrack() function. The parameters here are the image, max corners to detect, quality, and minimum distance between corners. Then, we iterate through each corner, making a circle at each.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/corner%20detection%20opencv%20python%20tutorial.py)

### <a name="Feature_Matching"></a>Feature Matching (Homography) Brute Force
* It is done by the function bf.match().
* First, we defined our two images and the detector. Then, we find the key points and their descriptors with the orb detector. Then we create the bf match object. And then we create matches of the descriptors and sort them based on their distances.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/feauture%20matching%20brute%20force%20opencv%20python%20tutorial.py)

### <a name="MOG_Background_Reduction"></a>MOG Background Reduction
* Here, we extract the moving foreground from the static background.
* cv2.createBackgroundSubtractorMOG2() is used to create the foreground mask.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/MOG%20background%20reduction.py)

### <a name="Haar_Cascade_Object_Detection_Face_&_Eye"></a>Haar Cascade Object Detection Face & Eye
* Haar Cascade Classification is basically a machine learning based approach where a cascade function is trained from a lot of images both positive and negative. Based on the training it is then used to detect the objects in the other images. Usually, they use huge individual .xml files with a lot of feature sets and each xml corresponds to a very specific type of use case.
* First, we are finding faces, their sizes, drawing rectangles, and noting the ROI using a loop and then we sketch out more rectangles for the eyes.
The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/haar%20cascade%20object%20detection%20face%20and%20eye%20opencv%20python%20tutorial.py)


### <a name="Making_your_own_Haar_Cascade"></a>Making your own Haar Cascade
* First, we define a function to read .xml files and store resized grayscale images of both positive and negetive pictures in a seperate folder. Then we remove the unwanted pictures by defining another function. Finally we create a descripter file for the negetive images and then proceed with the training part.
* For training, we move the neg folder and the descriptor file to the server and then create positive and negetive samples based on an image we provide. Using this we output an info list and all the newly generated images on seperate directories. More no. of stages run, higher is the accuracy.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/making%20your%20own%20haar%20cascade%20opencv%20python%20tutorial.py)


### <a name="Haar_Cascade_For_Image_and_Video_Object_Classification"></a>Haar Cascade For Image and Video Object Classification
* Finally, we write a code using the eye, face and watch cascades. it captures the recording from webcam and detects the eyes, faces and watches.

The code can be found [here](https://github.com/ParnaChowdhury/ADR-Taskphase/blob/master/opencv/codes/haar%20cascade%20for%20image%20and%20video%20classification%20opencv%20python%20tutorial.py)




