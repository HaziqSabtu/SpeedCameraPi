# Line Detection


## Introduction

Line detection is a fundamental technique in computer vision that plays an
essential role in a variety of applications, such as self-driving cars,
robotics, and augmented reality. Additionally, line detection can be used in
conjunction with other computer vision techniques, such as depth estimation, to
compute the distance of an object from a camera. This section describes how to
detect lines in an image using the OpenCV library.

## Line Detection Algorithm

<!-- prettier-ignore-start -->
\image html LineDetection.png "Line Detection Algorithm" 
\image latex LineDetection.png "Line Detection Algorithm"
<!-- prettier-ignore-end -->

To perform line detection using the Hough Transform, several pre-processing
steps are required. The first step is to convert the RGB image to grayscale, as
the Hough Transform is typically performed on grayscale images. The grayscale
image only contains intensity values, with no color information, making it
easier to detect edges and lines. The next step is to detect edges using Canny
edge detection which applies a series of filters and thresholds to the grayscale
image to identify the edges of objects in the image.

Once the edges have been detected, the Hough Transform can be applied to the
edge image to detect lines. The Hough Transform algorithm accumulates edge
points that are part of the same line and identifies the lines that are most
prominent in the image. These lines are then returned as output from the Hough
Transform algorithm. All of this steps are included in
LineDetection::ProcessImage() method.

### Useful links

[OpenCV HoughLinesP](http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=houghlinesp#houghlinesp)


# Subpage 1 Title {#subpage_1}
\section page_intro Introduction

# The List of subpages:

* Page @subpage subpage_1_1
* Page @subpage subpage_1_2
* Page @subpage subpage_1_3

# Subpage 1 Title {#example}
\section page_intro Introduction

# The List of subpages:

* Page @subpage subpage_1_1
* Page @subpage subpage_1_2
* Page @subpage subpage_1_3