# Installing Required Dependencies

This project requires the following dependencies to be installed:

- OpenCV v4

  - Powerful computer vision library that provides a vast range of image and
    video processing capabilities.

- wxWidgets v3

  - GUI toolkit that allows you to create cross-platform desktop applications
    with ease.

- RaspiCam

  - C++ library for interfacing with the Raspberry Pi camera module.

If these dependencies are not installed properly, the compilation process of
your project may fail or produce unexpected errors during runtime.

The following sections will guide you through the installation process of these
dependencies on Raspberry Pi 4 running Debian. The installation process may
involve downloading and compiling the source code yourself or using a package
manager to install pre-built binary packages. You may skip this section if the
required dependencies are already installed.

## Installing OpenCV

OpenCV is a powerful computer vision library that provides a vast range of image
and video processing capabilities. This project uses OpenCV to perform image
processing tasks such as detecting and tracking objects in the video stream.

Steps to install OpenCV on Raspberry Pi 4 running Debian:
[\[source\]](https://qengineering.eu/install-opencv-4.5-on-raspberry-pi-4.html)

- Update the package list and upgrade all packages to their latest versions:

        sudo apt-get update && sudo apt-get upgrade

- Increase the swap size to 4096MByte to prevent the system from running out of
  memory during the compilation process:

        sudo nano /etc/dphys-swapfile

- Once the file is opened in the Nano editor, locate the "CONF_SWAPSIZE" line,
  which specifies the maximum size of the swap file.

  - By default, the value of this variable is set to 100, which means that the
    swap file will be limited to 100MByte. Change this value to 4096MByte by
    replacing 100 with 4096.
  - Save the changes and exit the editor by pressing Ctrl+X, then Y, then Enter.

            CONF_SWAPSIZE=4096

  - Next, run the following command:

            sudo nano /sbin/dphys-swapfile

  - Increase CONF_MAXSWAP to 4096MByte

            CONF_MAXSWAP=4096

  - Reboot the system to apply the changes to the swap file:

            sudo reboot

- Now that the swap file has been increased, you can proceed with the
  installation of OpenCV.
- Download the installation script:

        wget https://github.com/Qengineering/Install-OpenCV-Raspberry-Pi-32-bits/raw/main/OpenCV-4-5-5.sh

        sudo chmod 755 ./OpenCV-4-5-5.sh

- Useful tips before compiling the library (optional):

  - During compilation process, you may encounter an error message that says
    "Out of memory". This means that the system ran out of memory and the
    compilation process was terminated. To fix this issue, you can reduce the
    number of threads used by the compiler by changing the value of the "-j"
    flag in the script.
  - By doing so may increase the compilation time.
  - To change the number of threads, open the installation script in the Nano
    editor:

            sudo nano ./OpenCV-4-5-5.sh

  - locate the following line and change the value of the "-j" flag to 1:

            make -j1

- Compile the library

        ./OpenCV-4-5-5.sh

- The installation script will take about 2 hours to complete. Once it is
  finished, reboot the system to apply the changes:

        sudo reboot

- Make sure to set swap size to original value after finish installation

## Installing wxWidget

wxWidgets is a cross-platform GUI library that provides a set of C++ classes for
creating graphical user interfaces. This project uses wxWidgets to create the
graphical user interface for the application.

Steps to install wxWidget on Raspberry Pi 4 running Debian:
[\[source\]](https://forums.raspberrypi.com/viewtopic.php?t=271709)

- Update the package list and upgrade all packages to their latest versions:

        sudo apt-get update && sudo apt-get upgrade

- Install the required dependencies for building wxWidgets:

        sudo apt-get install libgtk-3-dev build-essential checkinstall

- Download the latest stable version of wxWidgets from the official website:

        wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.2.1/wxWidgets-3.2.2.1.tar.bz2

- Extract the downloaded archive and navigate to the extracted directory:

        tar -xvf wxWidgets-3.2.2.1.tar.bz2

- Change directory to the extracted directory:

        cd wxWidgets-3.2.2.1

- Create a build directory and navigate to it:

        mkdir gtk-build

        cd gtk-build

- Configure the build process by running the following command:

        ../configure --disable-shared --enable-unicode --disable-debug

- Compile and install the library:

        make

        make install

## Installing RaspiCam

This library provides a set of C++ classes for interfacing with the Raspberry Pi
camera module. This project uses RaspiCam to capture images and video streams
from the camera module.

- Note: For Future Development this library is currently deprecated. It is
  recommended to use libcamera in the future.
  [\[source\]](https://github.com/raspberrypi/documentation/blob/develop/documentation/asciidoc/computers/camera/raspicam.adoc)

Steps to install RaspiCam on Raspberry Pi 4 running Debian:
[\[source\]](https://github.com/cedricve/raspicam/tree/master)

- Update the package list and upgrade all packages to their latest versions:

        sudo apt-get update && sudo apt-get upgrade

- Clone the repository:

        git clone https://github.com/cedricve/raspicam.git

- Change directory to the cloned repository and build the library:

          cd raspicam

          mkdir build

          cd build

          cmake ..

- Compile and install the library:

           make

           sudo make install

           sudo ldconfig

## Installing CMake

CMake is an open-source, cross-platform family of tools designed to build, test
and package software. This project uses CMake to build the application.

Steps to install CMake on Raspberry Pi 4 running Debian:
[\[source\]](https://gitlab.kitware.com/cmake/cmake)

- Update the package list and upgrade all packages to their latest versions:

        sudo apt-get update && sudo apt-get upgrade

- Install the required dependencies for building CMake:

        sudo apt install build-essential checkinstall zlib1g-dev libssl-dev

- Download the latest stable version of CMake from the official website:

        wget https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2.tar.gz

- Extract the downloaded archive and navigate to the extracted directory:

        tar -xvf cmake-3.22.2.tar.gz

        cd cmake-3.22.2

- Configure the build process by running the following command:

        ./bootstrap && make && sudo make install

- Verify the installation by running the following command:

        cmake --version
