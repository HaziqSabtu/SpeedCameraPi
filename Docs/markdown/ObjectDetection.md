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

Detection::ObjectDetection

Detection::ObjectDetection::updateFlow

[OpenCV Optical Flow](https://docs.opencv.org/3.4/d4/dee/tutorial_optical_flow.html)
