# SpeedCameraPi(SCP)

<p align="center">
  <img src="Docs/assets/logo.png" />
</p>

This project aims to develop a speed camera algorithm using Raspberry Pi and
computer vision techniques. The algorithm consists of three main components:

- Image alignment with feature detection
- Object detection with optical flow
- Speed calculation with pinhole camera

The proposed algorithm offers a low-cost, accurate, and real-time speed
detection solution that can contribute to improving road safety and reducing the
incidence of speeding.

## Getting Started

### Prerequisites

- Raspberry Pi 3 or later
- OpenCV 3.0 or later with Opencv_contrib
- wxWidgets
- RaspiCam

### Installation

- Download the source code of the application from the repository:

        git clone https://github.com/HaziqSabtu/SpeedCameraPi.git

- Create a build directory and navigate to it:

        cd SpeedCameraPi

        mkdir build

        cd build

- Configure the build process by running the following command:

        cmake -B. -H..

- Compile the application:

        make -j3

- After finished compiling, the executable file is located in the build
  directory.

        ./build

## Results

The proposed speed camera algorithm was evaluated on a dataset of moving
vehicles, balls, and cats. The results showed high accuracy and effectiveness in
detecting and measuring the speed of the objects. The error rate in speed
calculation was around 6%, which is comparable to traditional speed cameras.

## Future Work

Explore alternative feature detection and tracking techniques to improve the
efficiency of the image alignment and object detection algorithms.

Investigate dynamic thresholding techniques to increase the flexibility of the
object detection algorithm in different scenarios.

Develop more robust speed calculation methods that are not limited by the camera
angle or position.

## Contributing

Contributions are welcome. Please fork this repository and submit a pull
request.

## Useful links

- Docs: [GitHub Pages](https://haziqsabtu.github.io/SpeedCameraPi/)
- OpenCV: [https://opencv.org/](https://opencv.org/)
- wxWidgets: [https://www.wxwidgets.org/](https://www.wxwidgets.org/)
