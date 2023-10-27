\tableofcontents{HTML:2}

For future developers, this section will help you properly setup your
development environment. In general the development is done with Visual Studio
Code with cross compilation to Raspberry Pi 4. Guide to setup the development
environment is provided below. Alternatively, a native development setup will
also be provided.

# Introduction

C++ is a programming language that is designed to be compiled, meaning that it is generally translated into machine language that can be understood directly by the system, making the generated program highly efficient. To compile C++ code, you need a set of tools known as the development toolchain, whose core are a compiler and its linker. A compiler is a program that converts your C++ code into machine code, while a linker is a program that combines the machine code with other libraries and resources to create an executable file. There are different compilers and linkers available for C++, such as Visual Studio, Clang, mingw, etc. Some of them are integrated with IDEs (Integrated Development Environments) that provide features such as syntax highlighting, debugging, code completion, etc.

To cross compile C++ code, you need to use a cross compiler that can generate executable code for a different platform than the one you are running on. For example, if you want to compile C++ code for ARM architecture on a Windows PC, you need to use a cross compiler like arm-none-linux-gnueabi-gcc. Depending on the tool you are using, you may need to configure some settings to enable cross compilation. For example, if you are using Visual Studio Code, you can edit the Compiler path and Compiler arguments settings in the C/C++ extension to specify the cross compiler and the target triplet. You can also use other tools like CMake or Makefile to automate the cross compilation process.

# Cross-compilation

Cross-compilation is the process of compiling code on one platform (host) to run
on another platform (target). In this case, we will be compiling the code on a
Windows 11 machine running Windows Subsystem for Linux (WSL) to run on Raspberry
Pi 4 running Raspberry Pi OS (Bullseye 32-bit).

This method of development is preferred as it allows for faster compilation time
and easier debugging, which allows for better development experience.

Upon further reading, there are two important terms to take note of:

- **Host** - The machine that you are developing on. In this case, it is the
  Windows 11 machine.
- **Target** - The machine that you are developing for. In this case, it is the
  Raspberry Pi 4.

This method has been tested numerous times and is proven to work. However, it is
not guaranteed to work on all machines. To reproduce the development
environment, following Build number of Windows 11 and WSL is required:

- Windows 11 Pro Version 22H2 OS Build 22621.2428
- WSL 2 with Ubuntu 22.04 LTS

## Steps to setup Cross-Compilation

For this section, it is assumed that you have already installed WSL 2 with
Ubuntu 22.04 LTS. If not, please refer to the
[official documentation](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
to install WSL 2 with Ubuntu 22.04 LTS. Most of the process are taken from
[this guide](https://github.com/abhiTronix/raspberry-pi-cross-compilers/wiki/Cross-Compiler-CMake-Usage-Guide-with-rsynced-Raspberry-Pi-32-bit-OS#cross-compiler-cmake-usage-guide-with-rsynced-raspberry-pi-32-bit-os).

- To begin with, it is important that required dependencies are installed on
  **Target**. Refer to
  [this section](md_Docs_markdown_InstallingRequiredDependency.html) for more
  information.

- Next, we need to prepare the **Target** to allow ssh connection from the host. To
  do so, run the following command on **Host**:

  - Navigate to script folder:

        cd ~/SpeedCameraPi/scripts/crosscompile

  - Allow scripts execution:

        sudo chmod +x setup_ssh.py

  - Run the script. Following parameters are required:

    - **hostname** - Hostname of the target. This can be the IP address of the
      **Target**. Usually it is defaulted to raspberrypi
    - **username** - Username of the target.

          ./setup_ssh.py hostname username

  - Type yes when prompted. When successful, you should now be able to ssh into
    the target from the host with the following command:

        ssh RPi0

- Next, we need to prepare the **target** for cross-compilation. To do so, run
  the following command on **Host**:

  - Navigate to script folder:

        cd ~/SpeedCameraPi/scripts/crosscompile

  - Allow scripts execution:

        sudo chmod +x Target_setup.py

  - Run the script. Following parameters are required:

    - **credential** - If previous steps are done, use RPi0. Otherwise, use
      username@hostname.
    - **password** - Password of the target.

          ./Target_setup.py credential password

  - Following tasks are done within this scripts:
    - Install required dependencies on **Target**
    - Enable development sources
    - Enable rsync (this allows syncing of files between **Host** and
      **Target**)
    - Install development packages
    - Symlinks (fix symbolic links)

- Next, we need to prepare the **host** for cross-compilation. To do so, run the
  following command on **Host**:

  - Navigate to script folder:

        cd ~/SpeedCameraPi/scripts/crosscompile

  - Allow scripts execution:

        sudo chmod +x Host_setup.py

  - Run the script with root privileges:

        sudo ./Host_setup.py

  - Following tasks are done within this scripts:
    - Install required dependencies on **Host**
    - Prepare staging directory (sysroot folder)
      - Staging folder refers to the directories of the **target** that we are
        trying to mimics. This is done to allow the cross-compiler to find the
        required dependencies.
    - Download Toolchain
      - Toolchain is a set of tools that allows us to compile code for the
        **target**.
    - Copy utility files

- Lastly, now we need to sync the files structure of **Target** with **Host** on the staging directory (sysroot). To do so run following command:

  - Navigate to script folder:

        cd ~/SpeedCameraPi/scripts/crosscompile

  - Allow scripts execution:

        sudo chmod +x Host_postSetup.py

  - Run the script:
  
        ./Host_postSetup.py

  - Following tasks are done within this scripts:
    - Sync files from **Target** to **Host** via rsync
    - Symbolic links (fix symbolic links)

- Now, you should be able to perform cross compilation. However, as of now, there is a linker problem with OpenCV libraries. To fix this, please refer to the next section.

## Fixing OpenCV linker problem

- Now, we will once again compile OpenCV. There seems to be a problem using the
  already compiled library of OpenCV as done previously on the **Target**. Some
  _opencv_contrib_ libraries cannot be found during runtime. Possible linker
  error? Still investigating. However, the current fix is to cross compile the
  library on the **Host** and transfer the compiled libs to the **Target**. To
  do so, follow these steps:

  - Navigate to script folder:

        cd ~/SpeedCameraPi/scripts/crosscompile

  - Allow scripts execution:

        sudo chmod +x Target_cvinstall.py

  - Run the script with following parameters:

    - **credential** - If ssh setup are done, use RPi0. Otherwise, use
      username@hostname.

          ./Target_cvinstall.py credential

  - Following tasks are done within this scripts:
    - Download required dependencies
    - Symbolic links (fix symbolic links)
    - Sync files from **Target** to **Host** via rsync

- Now, we will compile OpenCV on **host** machine:

  - Navigate to script folder:

        cd ~/SpeedCameraPi/scripts/crosscompile

  - Allow scripts execution:

        sudo chmod +x Host_cvcompile.py

  - Run the script with root privileges:

        sudo ./Host_cvcompile.py

  - Following tasks are done within this scripts:
    - Download required dependencies
    - Download OpenCV source code
    - Compile OpenCV

  - In some cases, during complation of OpenCV, it will produce error jconfig.h not found
    - To fix this, run the following command:

          cd ~/SpeedCameraPi/scripts/crosscompile
          sudo chmod +x fix_jconfig.py
          ./fix_jconfig.py


- Now, when the library is compiled, we can transfer the compiled library to the
  **target** machine. To do so, run the following command on **Host**:

  - Navigate to script folder:

        cd ~/SpeedCameraPi/scripts/crosscompile

  - Allow scripts execution:

        sudo chmod +x Host_cvinstall.py

  - Run the script:

        ./Host_cvinstall.py

  - Following tasks are done within this scripts:
    - Packed compiled library into tar file
    - Sync files from **Host** to **Target** via scp
    - Unpack compiled library on **Target** and placed them on /usr/local
    - Symbolic links (fix symbolic links)
    - Sync files from **Target** to **Host** via rsync

- Now, the machine is ready for cross-compilation. Now we will explore steps to install Visual Studio Code.

## Installing Visual Studio Code

Visual Studio Code is a free source-code editor made by Microsoft for Windows, Linux and macOS. It is a very popular code editor among developers. This section will guide you through the process of installing Visual Studio Code for  Cross-compilation.

If you are running Linux on WSL, it is recommended to install Visual Studio Code directly on Windows. Download the installer from [here](https://code.visualstudio.com/Download) and install it on Windows.

## Accesing WSL from Visual Studio Code

First we need to install WSL Extension for Visual Studio Code. To do so, open the Extensions pane (Ctrl+Shift+X) and search for WSL. Click on the Install button to install the extension.

- WSL
<!-- prettier-ignore-start -->
\image html wslext.png ""
\image latex wslext.png ""
<!-- prettier-ignore-end -->

To access WSL from Visual Studio Code, open the Command Palette (Ctrl+Shift+P) and type *WSL: Connect to WSL*. This will open a new Visual Studio Code window with WSL as the default shell. You can also open a folder in WSL by right-clicking on the folder in the File Explorer and selecting Open in WSL.

<!-- prettier-ignore-start -->
\image html wslconnect.png ""
\image latex wslconnect.png ""
<!-- prettier-ignore-end -->

You should see that you are currently in the WSL shell. You can also check the bottom left corner of the window to see if you are in WSL shell.

<!-- prettier-ignore-start -->
\image html wslconnect2.png ""
\image latex wslconnect2.png ""
<!-- prettier-ignore-end -->

## Installing required Extensions

To install extensions, open Visual Studio Code and press Ctrl+Shift+X to open the Extensions pane. Search for the following extensions and install them:

- C/C++ Extension Pack
<!-- prettier-ignore-start -->
\image html c++ext.png ""
\image latex c++ext.png ""
<!-- prettier-ignore-end -->

## Opening SpeedCameraPi project

To open the SpeedCameraPi project, open the Explorer pane (Ctrl+Shift+E) and click on the Open Folder button. Navigate to the SpeedCameraPi folder and click on the OK button. You should now see the SpeedCameraPi project in the Explorer pane.

<!-- prettier-ignore-start -->
\image html wslfolder.png ""
\image latex wslfolder.png ""
<!-- prettier-ignore-end -->

<br/>

<!-- prettier-ignore-start -->
\image html wslfolder2.png ""
\image latex wslfolder2.png ""
<!-- prettier-ignore-end -->

## Configuring C/C++ extension

To configure the C/C++ extension, open the Command Palette (Ctrl+Shift+P) and type *CMake:Configure* and select the *Pi Toolchain* option. This will create a *build* folder in the project directory and generate the CMake cache. 

If the *Pi Toolchain* option is not available, you may need to check if the cross compilation setup is done correctly. Additionally, in some cases the path may be different. If so, you may need to edit the *.vscode/cmake-kits.json* file to change the path to the cross compiler.

<!-- prettier-ignore-start -->
\image html cppconf.png ""
\image latex cppconf.png ""
<!-- prettier-ignore-end -->

<br/>

<!-- prettier-ignore-start -->
\image html cppconf2.png ""
\image latex cppconf2.png ""
<!-- prettier-ignore-end -->

If the configuration process is successful, you should see the following message in the terminal:

<!-- prettier-ignore-start -->
\image html cppconf3.png ""
\image latex cppconf3.png ""
<!-- prettier-ignore-end -->

## Building the project

To build the project, open the Command Palette (Ctrl+Shift+P) and type *CMake:Build*. This will build the project and generate the executable file in the *build* folder.

<!-- prettier-ignore-start -->
\image html cppbuild.png ""
\image latex cppbuild.png ""
<!-- prettier-ignore-end -->

Withing the CMakeLists.txt file, the executable file is by default, configured to be automatically copied to the **Target** machine. You can disable this by editing out the command. However, it is recommended to keep it as it is. The build application is located at *~/Target/SpeedCameraPi*.

<br/>

## Debugging the project

### Preparations
Debugging is crucial when developing a project. This steps need to be done atleast once. To perform debug, we first need to configure the **launch.json** script. To do so, navigate to the script folder:
      
      cd ~/SpeedCameraPi/scripts/debug

Next, run the following command:
      
      sudo chmod +x launch.py

Lastly, run the script with following parameters:

- **ipaddress** - IP address of the **Target** machine. Cannot be raspberrypi
      
      sudo ./launch.py ipaddress

This will generate the **launch.json** file in the *.vscode* folder. Now we need to install gdbserver on the **Target** machine. To do so, run the following command on **Host**:

      ssh RPi0
      sudo apt-get install gdbserver

<br/>

### Debugging

To debug the project, open the Debugger Tab (ctrl + shift + D) and select the profile *(GDB-Auto) Remote GDB Launch* and click on the Run button. This will start the GDBServer on the **Target** machine and connect to it. You should now be able to debug the project.

<!-- prettier-ignore-start -->
\image html debug.png ""
\image latex debug.png ""
<!-- prettier-ignore-end -->

<br/>

### Known Issues

In some cases, these libs cannot be found. To fix run the following command on **Host**:

- **libncurses.so**
      - Run the following command on **Host**:

      sudo apt install libncurses5

- **libpython2.7.so**
      - Run the following command on **Host**:

      sudo apt install libpython2.7

<br/>

## Extra Features

In this section, we will explore some extra features that can be used to improve the development experience.

### VNC Viewer

VNC Viewer is a remote desktop application that allows you to remotely control a computer. It is useful for accessing the **Target** machine remotely. By properly integrating the VNC, your Raspberry Pi can be used without a monitor, keyboard, or mouse.

To download VNC Viewer, go to [this link](https://www.realvnc.com/en/connect/download/viewer/) and download the installer for your operating system. Once installed, you may need to create an account to use the application. 

Once done you may need to prepare the **Target** machine to allow VNC connection. To do so, run the following command on **Host**:

- Access the **Target** machine via ssh:

      ssh RPi0

- Run the following command:
  
        sudo raspi-config

- Navigate to **Interface Options** and enable **VNC**.

<!-- prettier-ignore-start -->
\image html vnc1.png ""
\image latex vnc1.png ""
<!-- prettier-ignore-end -->
<br/>
<!-- prettier-ignore-start -->
\image html vnc2.png ""
\image latex vnc2.png ""
<!-- prettier-ignore-end -->
<br/>
<!-- prettier-ignore-start -->
\image html vnc3.png ""
\image latex vnc3.png ""
<!-- prettier-ignore-end -->

- Now, you should be able to access the **Target** machine via VNC Viewer. It is recommended to reboot the **Target** machine after enabling VNC.

- To access the **Target** machine via VNC Viewer, you need to know the IP address of the **Target** machine. To do so, run the following command on **Host**:

      hostname -I

  - Alternatively, it is defaulted to raspberrypi

- Now, you can access the **Target** machine via VNC Viewer. To do so, open VNC Viewer and create new connection (ctrl + N) and set following parameters:

  - **VNC Server** - IP address of the **Target** machine
  - **Name** - Name of the connection, can be anything

<!-- prettier-ignore-start -->
\image html vnc4.png ""
\image latex vnc4.png ""
<!-- prettier-ignore-end -->

- Now, you should be able to access the **Target** machine via VNC Viewer. You may need to enter the password of the **Target** machine.

<br/>

### VSCode Extensions

Following are some useful extensions that can be used to improve the development experience:

<!-- table -->
| Extension | Description |
| --- | --- |
| [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) | Clang-Format is a tool that formats C/C++/Obj-C code according to a set of style options, similar to the way that clang-format formats code. |
| [Github Copilot](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot) | GitHub Copilot is an AI pair programmer that helps you write code faster and with less work. |
| [Todo Tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree) | Todo Tree is a task manager that helps you manage your TODOs. |

<br/>

# Native compilation

For those that prefer to develop natively on Raspberry Pi, this section will guide you through the process of setting up the development environment.

For native compilation, the steps is much simpler. Simply install the required dependencies on the **target** machine and you are good to go. Refer to [this section](md_Docs_markdown_InstallingRequiredDependency.html) for more information.

The installation of VSCode on RaspberryPi is done with [this](https://code.visualstudio.com/docs/setup/raspberry-pi) instruction.

## Installing required Extensions

To install extensions, open Visual Studio Code and press Ctrl+Shift+X to open the Extensions pane. Search for the following extensions and install them:

- C/C++ Extension Pack
<!-- prettier-ignore-start -->
\image html c++ext.png ""
\image latex c++ext.png ""
<!-- prettier-ignore-end -->

## Opening SpeedCameraPi project

To open the SpeedCameraPi project, open the Explorer pane (Ctrl+Shift+E) and click on the Open Folder button. Navigate to the SpeedCameraPi folder and click on the OK button. You should now see the SpeedCameraPi project in the Explorer pane.

<!-- prettier-ignore-start -->
\image html wslfolder.png ""
\image latex wslfolder.png ""
<!-- prettier-ignore-end -->

<br/>

## Configuring C/C++ extension

To configure the C/C++ extension, open the Command Palette (Ctrl+Shift+P) and type *CMake:Configure* and select the default compiler. This will create a *build* folder in the project directory and generate the CMake cache. 

<!-- prettier-ignore-start -->
\image html cppconf.png ""
\image latex cppconf.png ""
<!-- prettier-ignore-end -->

<br/>

<!-- prettier-ignore-start -->
\image html cppconf4.png ""
\image latex cppconf4.png ""
<!-- prettier-ignore-end -->

If the configuration process is successful, you should see the following message in the terminal:

<!-- prettier-ignore-start -->
\image html cppconf3.png ""
\image latex cppconf3.png ""
<!-- prettier-ignore-end -->

## Building the project

To build the project, open the Command Palette (Ctrl+Shift+P) and type *CMake:Build*. This will build the project and generate the executable file in the *build* folder.

<!-- prettier-ignore-start -->
\image html cppbuild.png ""
\image latex cppbuild.png ""
<!-- prettier-ignore-end -->

If the ui is unrespomsive, highly likely that the building process is using all of the resources available. Either wait until the process complete, or reduce the number of parallel build jobs. To do so, open the Command Palette (Ctrl+Shift+P) and type *Settings: Open Settings (UI)*. Navigate to *CMake: Parallel Jobs* and set the value to 1.

<!-- prettier-ignore-start -->
\image html cppbuild3.png ""
\image latex cppbuild3.png ""
<!-- prettier-ignore-end -->

## Debugging

To debug the project, open the Debugger Tab (ctrl + shift + D) and select the profile *GDB - Native* and click on the Run button. This will compile the project and start the debugger. You should now be able to debug the project.

<!-- prettier-ignore-start -->
\image html debug2.png ""
\image latex debug2.png ""
<!-- prettier-ignore-end -->

<br/>


