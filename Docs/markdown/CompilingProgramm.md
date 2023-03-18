# Compiling the Application

This section describes the steps to compile the application.

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
