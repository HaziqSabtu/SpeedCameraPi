# Installing Required Dependencies

This project requires the following dependencies to be installed:

- OpenCV v4.5.5

  - Powerful computer vision library that provides a vast range of image and
    video processing capabilities.

- wxWidgets v3.2.2

  - GUI toolkit that allows you to create cross-platform desktop applications
    with ease.

- libcamera v0.0.4

  - C++ library for interfacing with the Raspberry Pi camera module.

If these dependencies are not installed properly, the compilation process of
your project may fail or produce unexpected errors during runtime.

The following sections will guide you through the installation process of these
dependencies on Raspberry Pi 4 running Debian. The installation process may
involve downloading and compiling the source code yourself or using a package
manager to install pre-built binary packages. You may skip this section if the
required dependencies are already installed.

To further simplify the installation process, we have provided a set of scripts
that will automatically install the required dependencies for you. You may
choose to run the scripts or follow the steps manually. It is also recommended to perform installation on fresh installation of Raspberry Pi OS to prevent any conflicts with existing packages.

## Preparing the system

Before installing the required dependencies, following steps are required to be
done:

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:
        
        sudo chmod +x DI_Scripts1.sh

- Run script:
        
        sudo ./DI_Scripts1.sh

### Explanation of script

- Update the package list and upgrade all packages to their latest versions:

        sudo apt-get update && sudo apt-get upgrade

- Increase swap size to 4096MByte to prevent the system from running out of
  memory during the compilation process:

        NEW_SWAPSIZE=4096
        sudo sed -i "s/CONF_SWAPSIZE=.*/CONF_SWAPSIZE=$NEW_SWAPSIZE/" /etc/dphys-swapfile
        sudo sed -i "s/CONF_MAXSWAP=.*/CONF_MAXSWAP=$NEW_SWAPSIZE/" /sbin/dphys-swapfile
        sudo systemctl restart dphys-swapfile

## Installing OpenCV

OpenCV is a powerful computer vision library that provides a vast range of image
and video processing capabilities. This project uses OpenCV to perform image
processing tasks such as detecting and tracking objects in the video stream.

Steps to install OpenCV on Raspberry Pi 4 running Debian:
[\[source\]](https://qengineering.eu/install-opencv-4.5-on-raspberry-pi-4.html)

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:
        
        sudo chmod +x DI_Scripts2.sh

- Run script:

        sudo ./DI_Scripts2.sh

### Explanation of script

- Update the package list and upgrade all packages to their latest versions:

        sudo apt-get update && sudo apt-get upgrade

- Install the required dependencies for building OpenCV:

        sudo apt-get install -y build-essential cmake git unzip pkg-config
        sudo apt-get install -y libjpeg-dev libtiff-dev libpng-dev
        sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev
        sudo apt-get install -y libgtk2.0-dev libcanberra-gtk* libgtk-3-dev
        sudo apt-get install -y libgstreamer1.0-dev gstreamer1.0-gtk3
        sudo apt-get install -y libgstreamer-plugins-base1.0-dev gstreamer1.0-gl
        sudo apt-get install -y libxvidcore-dev libx264-dev
        sudo apt-get install -y python3-dev python3-numpy python3-pip
        sudo apt-get install -y libtbb2 libtbb-dev libdc1394-22-dev
        sudo apt-get install -y libv4l-dev v4l-utils
        sudo apt-get install -y libopenblas-dev libatlas-base-dev libblas-dev
        sudo apt-get install -y liblapack-dev gfortran libhdf5-dev
        sudo apt-get install -y libprotobuf-dev libgoogle-glog-dev libgflags-dev
        sudo apt-get install -y protobuf-compiler

- Download OpenCV version 4.5.5 from the repository:

        cd ~ 
        sudo rm -rf opencv*
        wget -O opencv.zip https://github.com/opencv/opencv/archive/4.5.5.zip 
        wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.5.5.zip 
        unzip opencv.zip 
        unzip opencv_contrib.zip 
        mv opencv-4.5.5 opencv
        mv opencv_contrib-4.5.5 opencv_contrib
        rm opencv.zip
        rm opencv_contrib.zip

- Create a build directory and navigate to it:
        
        cd ~/opencv
        mkdir build
        cd build

- Configure the build process by running the following command:

        cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
        -D ENABLE_NEON=ON \
        -D WITH_OPENMP=ON \
        -D WITH_OPENCL=OFF \
        -D BUILD_TIFF=ON \
        -D WITH_FFMPEG=ON \
        -D WITH_TBB=ON \
        -D BUILD_TBB=ON \
        -D WITH_GSTREAMER=ON \
        -D BUILD_TESTS=OFF \
        -D WITH_EIGEN=OFF \
        -D WITH_V4L=ON \
        -D WITH_LIBV4L=ON \
        -D WITH_VTK=OFF \
        -D WITH_QT=ON \
        -D OPENCV_ENABLE_NONFREE=ON \
        -D INSTALL_C_EXAMPLES=OFF \
        -D INSTALL_PYTHON_EXAMPLES=OFF \
        -D OPENCV_FORCE_LIBATOMIC_COMPILER_CHECK=1 \
        -D PYTHON3_PACKAGES_PATH=/usr/lib/python3/dist-packages \
        -D OPENCV_GENERATE_PKGCONFIG=ON \
        -D BUILD_EXAMPLES=OFF ..

- Compile and install the library:
        
                make -j1
                sudo make install
                sudo ldconfig

## Installing wxWidget

wxWidgets is a cross-platform GUI library that provides a set of C++ classes for
creating graphical user interfaces. This project uses wxWidgets to create the
graphical user interface for the application.

Steps to install wxWidget on Raspberry Pi 4 running Debian:
[\[source\]](https://forums.raspberrypi.com/viewtopic.php?t=271709)

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:
        
        sudo chmod +x DI_Scripts3.sh

- Run script:
                
        sudo ./DI_Scripts3.sh

### Explanation of script

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

        sudo make install

## Installing libcamera

Libcamera is an open-source software stack designed to support complex camera configurations on Raspberry Pi and other embedded devices. It provides a unified interface for multiple camera modules, allowing developers to efficiently harness their full potential in various applications, from computer vision projects to advanced photography.

As of now, libcamera is still under development and is still in alpha stage. However, it is already being used by the Raspberry Pi Foundation to support the Raspberry Pi High Quality Camera Module. It is recommended to use libcamera in the future as it provides a more flexible and powerful interface for controlling the camera module.

For this project, we will be using v0.0.4. As of now, a more higher version is available, however as still in alpha stage, a lot of changes are still being made. When a more stable release is available, we will update this guide.

Steps to install Libcamera v0.0.4 on Raspberry Pi 4 running Debian:

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:

        sudo chmod +x DI_Scripts4.sh

- Run script:
        
        sudo ./DI_Scripts4.sh

### Explanation of script
- Update the package list and upgrade all packages to their latest versions:

        sudo apt-get update && sudo apt-get upgrade

- Install the required dependencies for building libcamera:

        sudo apt install -y libboost-dev
        sudo apt install -y libgnutls28-dev openssl libtiff5-dev pybind11-dev
        sudo apt install -y qtbase5-dev libqt5core5a libqt5gui5 libqt5widgets5
        sudo apt install -y meson
        sudo apt install -y cmake
        sudo pip3 install pyyaml ply
        sudo pip3 install --upgrade meson
        sudo apt install -y libglib2.0-dev libgstreamer-plugins-base1.0-dev

- Download the repository and checkout to v0.0.4:

        cd ~
        git clone https://github.com/raspberrypi/libcamera.git
        cd libcamera
        git checkout v0.0.4

- Configure and build the library:

        meson build --buildtype=release -Dpipelines=raspberrypi -Dipas=raspberrypi -Dv4l2=true -Dgstreamer=enabled -Dtest=false -Dlc-compliance=disabled -Dcam=disabled -Dqcam=enabled -Ddocumentation=disabled -Dpycamera=enabled
        ninja -C build -j2   # use -j 2 on Raspberry Pi 3 or earlier devices
        sudo ninja -C build install

## Clean up

After installing the required dependencies, you may want to clean up the unnecessary files to free up some disk space. To do so, run the following commands:

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:

        sudo chmod +x DI_Scripts5.sh

- Run script:
                
        sudo ./DI_Scripts5.sh


## Utility Scripts

This collection of scripts is not necessary for the installation of the required dependencies. However, it is recommended to run these scripts to ensure that the system is properly configured for the project.

### Hotspot

This script will configure the Raspberry Pi to enable the hotspot feature whenever it is not connected to local network. This will allow you to connect to the Raspberry Pi directly when you are not at home.

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:
        
        sudo chmod +x Hotspot.sh

- Run script:
                
        sudo ./Hotspot.sh

### Startup

This script will configure the Raspberry Pi to automatically start the SpeedCameraPi application whenever it is booted up. This will allow you to use the Raspberry Pi as a standalone device without the need to manually start the application.

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:

        sudo chmod +x Startup.py

- Run script:

        sudo ./Startup.py

### Touchscreen

This script will fix the touchscreen rotation issue. This will allow you to use the touchscreen in portrait mode.

- Navigate to scripts directory:

        cd ~/SpeedCameraPi/scripts/Installation

- Allow script to be executed:

        sudo chmod +x Touchscreen.sh    

- Run script:

        sudo ./Touchscreen.sh

