\tableofcontents{HTML:1}

# Image Allignment

## Introduction

Due to various factors, recording a video with a portable handheld device can be
challenging. One of the most significant difficulties is keeping the device
stable while recording. The device's handheld nature makes it susceptible to
movement and shakiness, which can cause a non-static video that significantly
affects the accuracy of the calculated results. This section will discuss
overcoming this problem by utilizing a feature detection algorithm.

## Scale Invariant Feature Transform (SIFT)

Many image processing and computer vision algorithms require feature detection
in input data, such as object tracking and recognition. Researchers have
proposed several algorithms for feature detection, including the Harris corner
detector \cite harris1988, the SIFT algorithm \cite lowe2004, and the SURF
algorithm \cite bay2006. One significant advantage of Lowe's approach is its
ability to detect and describe local features in images insensitive to scale,
rotation, and illumination changes. \cite lowe2004.

<!-- prettier-ignore-start -->
\image html sift1.png "Example of SIFT Algorithm"
\image latex sift1.png "Example of SIFT Algorithm"
<!-- prettier-ignore-end -->

By applying a Difference of Gaussian (DoG) filter to the image at various
scales, the SIFT algorithm achieves keypoint localization and generates a scale
space representation. Keypoints detection involves identifying local extrema in
the scale space, then generating feature descriptors for each key point to
facilitate matching and recognition \cite cordes09.

## Feature Matching

<!-- prettier-ignore-start -->
Feature matching involves comparing the feature descriptors of the keypoints
from the two frames to match the generated keypoints with the keypoints from the
next frame. The Fast Library for Approximate Nearest Neighbors (FLANN) is used
in this case for comparing feature descriptors that work by comparing the
similarity of the generated keypoints and return the best possible match \cite geo23.
<!-- prettier-ignore-end -->

To further improve the accuracy of the FLANN matcher, Lowe proposed a ratio test
to eliminate false matches \cite lowe2004. It works by comparing the distance of
the best match with the distance of the second-best match, and if the ratio of
the distance of the best match to the second-best match is less than a threshold
value, the best match is considered to be a good match and is used for further
processing \cite Bekele13.

## Homography

<!-- prettier-ignore-start -->
Homography is a crucial concept in computer vision and is commonly used in
perspective transformations \cite Ondraovi21 and object detection \cite Hudaya21.
 One can use homography in SIFT detection to transform the detected
features in one image into the coordinate system of another image, thereby
fixing the perspective distortion and aligning the images.

\image html homography1.jpg "Example of Homography result \cite cvHomography"
\image latex homography1.jpg "Example of Homography result \cite cvHomography"
<!-- prettier-ignore-end -->

As proposed by Vincent and Lagani\'ere, to compute the homography matrix, at
least four corresponding points are needed, which can be obtained by the RANSAC
algorithm \cite Vin01. RANSAC algorithm is an iterative approach that randomly
selects a subset of the data and fits a model to the subset \cite Lee20. One can
fix the perspective distortion of the image and align the images using the
computed homography matrix.

## Image Alignment Algorithm

<!-- prettier-ignore-start -->
\image html ImageAllignmentAlgoDiagram.jpg "Image Alignment Algorithm"
\image latex ImageAllignmentAlgoDiagram.jpg "Image Alignment Algorithm"
<!-- prettier-ignore-end -->

The algorithm starts by reading the selecting two frames from the video and
detecting the keypoints using SIFT algorithm. The keypoints are then matched
with the keypoints from the next frame using the FLANN matcher. The matched
keypoints are utilized to compute the homography matrix using the RANSAC
algorithm. The resulting homography matrix is then applied to transform the
keypoints from the next frame into the coordinate system of the first frame.
This process is repeated for all frames in the video.

## Useful links

FeatureDetector::allign()

[OpenCV Example](https://docs.opencv.org/3.4/d1/de0/tutorial_py_feature_homography.html)


# Object Detection

## Introduction

Identifying and locating objects within an image or video is a crucial task in
computer vision known as object detection. This task has a wide range of
applications, such as in autonomous driving, surveillance, and robotics. Over
the years, several methods have been developed to address this problem, ranging
from classical computer vision approaches to deep learning-based techniques.

<!-- prettier-ignore-start -->
Classical methods include feature-based approaches such as Haar cascades \cite viola01 and Histogram of Oriented Gradients (HOG) \cite dalal05, while deep
learning-based approaches include popular frameworks such as Region-based
Convolutional Neural Networks (R-CNN) \cite ross13 and Single Shot MultiBox
Detector (SSD) \cite wei15. With the recent advancements in computer hardware
and deep learning techniques, object detection has seen significant progress,
and state-of-the-art models such as YOLO (You Only Look Once) \cite joseph15
have achieved remarkable accuracy and speed.
<!-- prettier-ignore-end -->

Due to the hardware limitations for this project, implementing object detection
has been a challenging task to solve. A method which neither requires a powerful
computatioanal power nor time consuming is needed. This section will propose a
method to detect moving objects in a video with Optical Flow algorithm

## Optical Flow

Optical flow is a motion estimation technique used to determine the motion of
pixels in a video, resulting in a vector field where each vector represents the
motion of the corresponding pixel \cite Duncan92. One significant advantage of
optical flow is its ability to detect independent moving objects in a scene even
when limited information is available \cite Jiang13.

The technique proposed by Lucas and Kanade estimates pixel displacement by
comparing the intensity of pixels in consecutive frames. In order to reduce the
complexity of calculating optical flow, two assumptions are made by Lucas and
Kanade. These assumptions are that the motion between frames is small and that
the intensity of the image is smooth \cite Sharmin12.

<!-- prettier-ignore-start -->
\image html opticalflow_lk.jpg "Result of Optical Flow"
\image latex opticalflow_lk.jpg "Result of Optical Flow"
<!-- prettier-ignore-end -->

Optical flow works by first detecting the keypoints in the first frame of the
video as explained in FeatureDetector. One study found that feature detection
techniques like Canny and Harris can produce more accurate keypoints for optical
flow compared to SIFT \cite Nourani12. The keypoints are then tracked in the
next frame using the Lucas-Kanade algorithm and repeated until all frames are
processed.

The result of optical flow, as shown in Figure ... , clearly shows that moving
points can be distinctly identified and tracked. Therefore, if a threshold value
is set for the magnitude of the vector, fixed points on the background object,
e.g., trees, and roads, will be filtered out, and only moving points will be
detected.

## Object Detection and Tracking Algorithm

<!-- prettier-ignore-start -->
\image html ObjectDetection.png "Object Detection and Tracking Algorithm"
\image latex ObjectDetection.png "Object Detection and Tracking Algorithm"
<!-- prettier-ignore-end -->

The algorithm starts by reading the video and generating initial keypoints using
the Shi-Tomasi algorithm. The keypoints are then tracked using the Lucas-Kanade
algorithm, and the process is repeated until all frames are processed. The
magnitude of the vector is then analyzed. The corresponding point is considered
a moving point for any vector whose magnitude is more significant than a
threshold value.

## Useful Links

ObjectDetection

ObjectDetection::updateFlow

[OpenCV Optical Flow](https://docs.opencv.org/3.4/d4/dee/tutorial_optical_flow.html)

# Speed Calculation

## Pinhole Camera Model

The utilization of the pinhole camera model in computer vision and image
processing has been widespread. Its origin dates back to the fifth century BC,
when Mo Jing, a Chinese Mohist philosopher, described a similar design utilizing
a closed room and a hole in the wall \cite Ye2014. Later in the tenth century
AD, the Arabian physicist and mathematician Ibn al-Haytham, also known as
Alhazen, conducted experiments on image formation. He placed three candles in a
row, a screen with a small hole between them and the wall, and noticed that
images were only formed by the small holes, and the candle to the right created
an image on the wall to the left \cite Bekele13.

<!-- prettier-ignore-start -->
\image html pinholemodel.jpg "Example of Pinhole Camera Model \cite Ye2014"
\image latex pinholemodel.jpg "Example of Pinhole Camera Model \cite Ye2014"
<!-- prettier-ignore-end -->

The pinhole camera model is fundamental in computer vision, and the concept is
often used as a reference for developing more complex camera models. It is a
single-point perspective camera model that assumes that each point in the object
space projects through a single point in the image plane (Figure
\ref{pinholemodel}) \cite Huang14. The model contains three main components: the
image plane, focal length, and optical center \cite Nogueira19. The image plane
is where the light rays from the object space are projected and where an
inverted image is formed \cite Tomasi15. The optical center, on the other hand,
is where the light rays from the object space intersect, and it is located at a
focal length distance from the image plane \cite Tomasi15.

## Object Distance from Camera

<!-- prettier-ignore-start -->
\image html pinhole2.jpg "Figure of Pinhole Camera Model"
\image latex pinhole2.jpg "Figure of Pinhole Camera Model"
<!-- prettier-ignore-end -->

The diagram in Figure above shows the formation of an image of an object in the
image plane. The object, \f$O\f$, is located at a distance of \f$O_d\f$ from the
optical center, \f$C\f$ where the light rays from the object space intersect. It
will then form an inverted image of the object at the image plane, \f$I\f$,
which located at a distance of \f$f\f$ from the optical center. \f$O_h\f$
represents the height of the object in real world and \f$I_h\f$ represents the
height of the object in image plane.\f$S_h\f$ is the height of the image plane
or the sensor size of the camera.

The mathematical equations for the pinhole camera model are derived based on the
assumptions that the projection of the object is a point \cite Huang14 and that
light propagates in a straight line \cite bhathal09. From these assumptions, we
can derive the following equations:

<!-- prettier-ignore-start -->

\begin{equation}
    \label{eq:1}
    \frac{O_h}{O_d} = \frac{I_h}{f}
\end{equation}

\begin{equation}
    \label{eq:2}
    \frac{S_h}{I_h} = \frac{S_{hpix}}{I\_{hpix}}
\end{equation}
<!-- prettier-ignore-end -->

Assuming that the camera utilizes 100\% of the sensor size \cite picamDoc, the
following equation can be derived to relate the sensor size and image
resolution, as stated in Equation \ref{eq:2} . This equation assumes that the
ratio of sensor size, \f$S_h\f$, to focal length, \f(f \f), remains constant in
comparison to the ratio of image resolution, \f$S_{hpix}\f$, and object size in
pixels at the image plane, \f$I_{hpix}\f$ . By using this relationship, the
value of \f$I_h\f$ in Equation \ref{eq:1} can be substituted to calculate the
distance of the object from the camera using the following equation:

<!-- prettier-ignore-start -->
\begin{equation}
    \label{eq:3}
    O_d = {f} \cdot \frac{S_{hpix}}{S_h} \cdot \frac{O_h}{I_{hpix}} 
\end{equation}
<!-- prettier-ignore-end -->

One can obtain the parameters \f$S_{hpix}\f$ and \f$f\f$ directly from the
camera specifications or manufacturer. For instance, the Raspberry Pi Camera
Module v2 used in this project has a sensor size of 3.68 mm x 2.76 mm, and a
focal length of 3.04 mm \cite pi. It is worth noting that the sensor size varies
in width and height, and the choice of which value to use in the calculation
depends on the camera's orientation concerning the object's position.

While \f$S_{hpix}\f$ depends on the camera resolution, \f$I_{hpix}\f$ value can
be measured directly from the image. However, we are left with an unknown
variable, \f$O_h\f$, representing the object's height in the real world. Hence,
to compute the object's distance from the camera, one must know the object's
height in the real world.

## Speed Calculation

To determine the speed of a moving object, one can calculate the distance it
travels within a given time interval. This can be done by subtracting the
distance of the object in the previous frame from the distance of the object in
the current frame. Similarly, the time interval can be calculated by subtracting
the time of the previous frame from the current frame's time. Therefore, the
formula for determining the speed of the object is derived.

<!-- prettier-ignore-start -->
\begin{equation}
    \label{eq:4}
    Speed = \frac{|d_{current} - d_{previous}|}{t_{current} - t_{previous}}
\end{equation}

However, as previously mentioned in \ref {objectdistance}, the object's dimension
in the real world must be known to obtain an accurate result in the calculation.
A constant object size in the real world must be utilized to ensure consistency
in the calculation. In this project, the width of the road, which has an average
value of 3.5 meters in Germany, will be utilized as the object size \cite Autobahn.
<!-- prettier-ignore-end -->

## Proposed Algorithm

<!-- prettier-ignore-start -->
\image html algo.jpg "Proposed Algorithm"
\image latex algo.jpg "Proposed Algorithm"
<!-- prettier-ignore-end -->

Figure \ref {algorithm} illustrates the proposed algorithm, which commences by
acquiring images from the camera. Next, the image alignment algorithm processes
the images to eliminate any perspective distortion and ensure proper alignment.
The object detection algorithm then employs optical flow to detect moving
objects in the image.

User input is required to select the line that represents the width of the road,
as the calculation requires the real-world size of the object, as explained in
\ref {objectdistance}. Once the line selection is made, the speed of the
detected object can be calculated. The calculation results are displayed on the
screen, and the process is terminated.
