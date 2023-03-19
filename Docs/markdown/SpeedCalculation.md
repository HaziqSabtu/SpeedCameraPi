# Speed Calculation

## Pinhole Camera Model

The pinhole camera model is a simple and widely used model in computer vision
and computer graphics. It is based on the concept of a camera that captures an
image of a scene by projecting light rays from the scene onto a two-dimensional
image plane. In the pinhole camera model, the camera is represented as a
rectangular box with a small aperture, or pinhole, on one end. Light rays from
the scene pass through the pinhole and form an inverted image on the opposite
side of the box, which is the image plane. The location and size of the image on
the image plane depend on the distance between the pinhole and the image plane,
as well as the angle of the light rays from the scene. This relationship can be
described mathematically using the perspective projection equation, which
relates the 3D coordinates of points in the scene to their corresponding 2D
coordinates on the image plane. The pinhole camera model is used in many
applications, including camera calibration, 3D reconstruction, and virtual
reality.

## Measuring Distance with the Pinhole Camera Model

The pinhole camera model can be used to measure the distance between an object
and the camera. This process involves using the relationship between the size of
the object in the image and its actual size in the scene, as well as the
distance between the object and the camera.

In the pinhole camera model, the distance between the camera and the object can
be represented by the distance between the pinhole and the object in the scene.
If we know the size of the object in the scene, we can use the perspective
projection equation to compute the size of the object on the image plane.

Assuming that the camera is calibrated and we know its intrinsic parameters
(such as focal length and principal point), we can measure the size of the
object in the image. The ratio between the size of the object in the image and
its actual size in the scene is known as the object's scale factor.

Once we know the object's scale factor and its size in the scene, we can use
trigonometry to compute the distance between the camera and the object.
Specifically, we can use the following formula:

distance to object = actual size of object / (size of object in image \* scale
factor)

This formula works under the assumption that the object is located at the same
distance from the camera as the pinhole. If the object is located at a different
distance, we need to take into account the effects of perspective distortion.

### Usefull links
