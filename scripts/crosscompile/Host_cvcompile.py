#!/usr/bin/env python3

import os
import subprocess
import shutil
import cUtils

if not cUtils.isRunningWithSudo():
    print("Please run this script as root.")
    exit()

# Get the current username
username = os.getlogin()

# Define a function to execute shell commands
def run_command(command):
    process = subprocess.Popen(command, shell=True)
    process.wait()

# Download file
def download_file(url, filename):
    run_command(f"wget -O {filename} {url}")

# Extract zip file
def extract_zip(zipfile, target_dir):
    run_command(f"unzip {zipfile} -d {target_dir}")

# List of commands to execute
commands = [
    "sudo apt-get install -y build-essential cmake git unzip pkg-config",
    "sudo apt-get install -y libjpeg-dev libtiff-dev libpng-dev",
    "sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev",
    "sudo apt-get install -y libgtk2.0-dev libcanberra-gtk* libgtk-3-dev",
    "sudo apt-get install -y libgstreamer1.0-dev gstreamer1.0-gtk3",
    "sudo apt-get install -y libgstreamer-plugins-base1.0-dev gstreamer1.0-gl",
    "sudo apt-get install -y libxvidcore-dev libx264-dev",
    "sudo apt-get install -y python3-dev python3-numpy python3-pip",
    "sudo apt-get install -y libtbb2 libtbb-dev libdc1394-22-dev",
    "sudo apt-get install -y libv4l-dev v4l-utils",
    "sudo apt-get install -y libopenblas-dev libatlas-base-dev libblas-dev",
    "sudo apt-get install -y liblapack-dev gfortran libhdf5-dev",
    "sudo apt-get install -y libprotobuf-dev libgoogle-glog-dev libgflags-dev",
    "sudo apt-get install -y protobuf-compiler"
]

# Execute each command
for command in commands:
    run_command(command)

# Define paths
home_path = f"/home/{username}"
cxcmpl_path = f"{home_path}/cxcmpl"
opencv_path = f"{home_path}/opencv"
build_path = f"{opencv_path}/build"

# Change directories
os.chdir(home_path)

# Download opencv and opencv_contrib
download_file("https://github.com/opencv/opencv/archive/4.5.5.zip", "opencv.zip")
download_file("https://github.com/opencv/opencv_contrib/archive/4.5.5.zip", "opencv_contrib.zip")

# check if opencv folder exists, if so delete it
if os.path.exists(opencv_path):
    shutil.rmtree(opencv_path)

# Extract opencv and opencv_contrib
if (os.path.exists(f"{opencv_path}-4.5.5")):
    shutil.rmtree(f"{opencv_path}-4.5.5")
extract_zip("opencv.zip", home_path)#

if (os.path.exists(f"{opencv_path}_contrib-4.5.5")):
    shutil.rmtree(f"{opencv_path}_contrib-4.5.5")
extract_zip("opencv_contrib.zip", home_path)

# Rename opencv and opencv_contrib directories
if os.path.exists(f"{home_path}/opencv"):
    shutil.rmtree(f"{home_path}/opencv")

os.rename(f"{opencv_path}-4.5.5", "opencv")

if os.path.exists(f"{home_path}/opencv_contrib"):
    shutil.rmtree(f"{home_path}/opencv_contrib")

os.rename(f"{opencv_path}_contrib-4.5.5", "opencv_contrib")

# Remove zip files
os.remove("opencv.zip")
os.remove("opencv_contrib.zip")

# Change directories
os.makedirs(build_path, exist_ok=True)
os.chdir(build_path)

os.environ['HOME'] = home_path

# Temporary fix for allowing GTK to be found
os.system("export PKG_CONFIG_PATH=/usr/lib/arm-linux-gnueabihf/pkgconfig:/usr/share/pkgconfig")
os.system("export PKG_CONFIG_LIBDIR=/usr/lib/arm-linux-gnueabihf/pkgconfig:/usr/share/pkgconfig")

# CMake command
cmake_command = f"cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX={cxcmpl_path}/cv/local \
    -D CMAKE_TOOLCHAIN_FILE={cxcmpl_path}/tools/PI.cmake \
    -D OPENCV_EXTRA_MODULES_PATH={opencv_path}_contrib/modules \
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
    -D WITH_QT=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D INSTALL_C_EXAMPLES=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D PYTHON3_PACKAGES_PATH=/usr/lib/python3/dist-packages \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D BUILD_EXAMPLES=OFF \
    -D WITH_CUDA=OFF \
    -D INCLUDE_DIRECTORIES={cxcmpl_path}/sysroot/usr/lib \
    -D INCLUDE_DIRECTORIES={cxcmpl_path}/sysroot/usr/include \
    -D INCLUDE_DIRECTORIES={cxcmpl_path}/sysroot/opt/lib \
    -D INCLUDE_DIRECTORIES={cxcmpl_path}/sysroot/lib \
    -D WITH_GTK=ON .."

run_command(cmake_command)

# Determine the number of CPU cores
cores = os.cpu_count()
print(f"Number of CPU cores: {cores}")

# Make command
make_command = f"make -j{cores}"

run_command(make_command)

# Install command
install_command = "sudo make install"

run_command(install_command)

print("OpenCV installation complete.")
