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
