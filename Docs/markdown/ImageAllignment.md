# Image Allignment

## Introduction

Recording a video using a portable handheld device can be a challenge due to various factors. One of the major challenges is the stability of the device while recording. Since the device is held by hand, it is prone to movement and shakiness, which can result in a video that is not static. It is important to be aware of the challenge and take steps to have higher accuracy in speed estimation later on.

This section describes how an image alignment algorithm can be used to solve the shakiness problem from a recorded video. Image alignment algorithms work by analyzing frames of a video and identifying common features in each frame. By comparing these features across frames, the algorithm is able to compute features that are common across all frames. The algorithm then uses these common features to align the frames, which results in a video that is more static and stable.

## Image Alignment Algorithm

\image html ImageAllignmentAlgoDiagram.jpg "Image Alignment Algorithm"
\image latex ImageAllignmentAlgoDiagram.jpg "Image Alignment Algorithm"

Image processing algorithms can be explained using the diagram above. The first step in the algorithm is to use a feature detection algorithm such as SIFT or ORB to identify key points in each image. These key points are points in the image that have distinct and stable visual features such as corners, edges, or blobs. Once the key points have been identified, a descriptor is generated for each key point. The descriptor is a vector that encodes the visual properties of the key point such as its gradient orientation and magnitude.

After the descriptors have been generated, the next step is to match the descriptors between the two images. This is typically done using a nearest neighbor algorithm where each descriptor in one image is compared to all the descriptors in the other image, and the closest match is found. However, this can result in many false matches due to noise and occlusion in the images.

To filter out the false matches, the Lowe's algorithm is often used. This algorithm computes a ratio of the distance between the closest match and the second closest match. If this ratio is below a certain threshold, the match is considered to be a good match and is retained.

Once the good matches have been identified, the next step is to compute a homography matrix that maps the points in one image to the corresponding points in the other image. This is done using a least-squares algorithm that minimizes the distance between the mapped points and the actual points in the other image. The homography matrix can be used to warp one image so that it aligns with the other image.

Finally, the images are transformed using the homography matrix to produce a single aligned image. This process can be repeated for multiple images to produce a panorama or to track an object in a video stream. Overall, image aligning algorithms are an essential tool in computer vision and have numerous applications in a variety of fields.
