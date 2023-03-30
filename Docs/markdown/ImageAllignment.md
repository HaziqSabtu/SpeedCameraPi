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
