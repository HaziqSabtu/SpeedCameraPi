# Object Detection

## Introduction

Optical flow refers to the pattern of motion in an image sequence caused by the
movement of objects or camera. Specifically, it is a computer vision technique
that estimates the apparent motion of pixels between consecutive frames in a
video sequence. It is a powerful tool that allows us to track the motion of
objects in a scene and understand how they are moving over time. Optical flow
algorithms work by analyzing the brightness patterns of pixels across frames and
computing the displacement vectors that describe their motion. This information
can be used for a wide range of applications, from tracking the movement of
people and vehicles in surveillance footage, to stabilizing shaky camera
footage, to creating special effects in movies and video games.

This section will describe how optical flow can be used to used as object
detection algorithm.

## Object Detection Algorithm

\image html ObjectDetection.png "Line Detection Algorithm" \image latex
ObjectDetection.png "Line Detection Algorithm"

The first step in object detection with optical flow is to compute the initial
feature detection with the Lucas-Kanade algorithm. Once these keypoints are
detected, their locations are tracked in subsequent frames using optical flow.
Optical flow algorithms estimate the motion of objects in the scene by analyzing
the displacement of pixels between consecutive frames. By tracking the motion of
keypoints over time, we can obtain a more accurate estimate of the motion of
objects in the video sequence.

After computing the optical flow, the motion of each point is analyzed, and a
threshold is applied to identify points with significant movement. These points
are then considered as part of a moving object. One common method to analyze the
motion of the keypoints is to compute the magnitude of the displacement vector
and compare it to a threshold value. If the magnitude of the displacement vector
is above the threshold, the point is considered part of a moving object.

### Usefull links
