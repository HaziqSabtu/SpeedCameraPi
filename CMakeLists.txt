cmake_minimum_required(VERSION 3.10)

project(SpeedCameraPi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_compile_options(-Wno-psabi -D gtest_disable_pthreads=OFF)

include_directories(include)
file(GLOB_RECURSE SRCS ./src/*.cpp EXCLUDE ./src/main.cpp)
add_executable(SpeedCameraPi ./src/main.cpp ${SRCS})

target_compile_definitions(SpeedCameraPi PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")
# Check which Linux distribution is being used
# Currently only Ubuntu and Debian are supported
# If Ubuntu is Detected, run Cross Compile
# If Debian is Detected, run Native Compile
# If neither is detected, throw an error
if(UNIX AND EXISTS "/etc/os-release")
  file(READ "/etc/os-release" OS_RELEASE)
  if(OS_RELEASE MATCHES "Ubuntu")
    message("Ubuntu detected")
    message("Cross compiling")
    set(CROSS_COMPILING ON)
  elseif(OS_RELEASE MATCHES "debian")
    message("Debian detected")
    message("Native compiling")
    set(CROSS_COMPILING OFF)
  else()
    message(FATAL_ERROR "Unsupported Linux distribution")
  endif()
else() 
  message(FATAL_ERROR "Not a Linux system")
endif() # UNIX AND EXISTS "/etc/os-release"

if(CROSS_COMPILING)
    message("Cross compiling")  
  # allow pkg-config to find the libraries in sysroot
    set(ENV{PKG_CONFIG_DIR} "")
    set(ENV{LD_LIBRARY_PATH} "${CMAKE_SYSROOT}/usr/local/lib/arm-linux-gnueabihf:${CMAKE_SYSROOT}/usr/local/lib:${CMAKE_SYSROOT}/usr/local/share:${CMAKE_SYSROOT}/usr/local/local/lib/arm-linux-gnueabihf")
    set(ENV{PKG_CONFIG_LIBDIR} "${CMAKE_SYSROOT}/usr/local/lib/arm-linux-gnueabihf/pkgconfig:${CMAKE_SYSROOT}/usr/local/lib/pkgconfig:${CMAKE_SYSROOT}/usr/local/share/pkgconfig:${CMAKE_SYSROOT}/usr/local/local/lib/arm-linux-gnueabihf/pkgconfig")
    set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/usr/local/lib/arm-linux-gnueabihf/pkgconfig")
    set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})

    set(pathToLibcamera ${CMAKE_SYSROOT}/usr/local/lib/arm-linux-gnueabihf/libcamera.so)
    set(pathToLibcameraBase ${CMAKE_SYSROOT}/usr/local/lib/arm-linux-gnueabihf/libcamera-base.so)

    # set the include directory for libcamera
    set(libcamIncludeDir ${CMAKE_SYSROOT}/usr/local/include/libcamera)

    # set the prefix location for wxWidgets
    set(wxWidgets_CONFIG_OPTIONS --prefix=${CMAKE_SYSROOT}/usr/local)

    # Check Process Availability
    add_custom_command(
    TARGET SpeedCameraPi PRE_BUILD
    COMMAND ssh RPi0 "killall SpeedCameraPi" || true
    )

    # POST_BUILD command to copy executable to RPi0(target)
    add_custom_command(TARGET SpeedCameraPi POST_BUILD
        COMMAND ssh RPi0 "mkdir -p ~/Target"
        COMMAND scp $<TARGET_FILE:SpeedCameraPi> RPi0:~/Target/
        COMMAND scp -r ${CMAKE_SOURCE_DIR}/Assets RPi0:~/Target
    )
else()
    message("Native compiling")
    set(libcamIncludeDir /usr/local/include/libcamera)

    set(pathToLibcamera /usr/local/lib/arm-linux-gnueabihf/libcamera.so)
    set(pathToLibcameraBase /usr/local/lib/arm-linux-gnueabihf/libcamera-base.so)
    
    add_custom_command(TARGET SpeedCameraPi POST_BUILD
    COMMAND cp -r ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:SpeedCameraPi>
    )
endif() # CROSS_COMPILING

# Find OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  message(STATUS "OpenCV found!")
  message(STATUS "    version: ${OpenCV_VERSION}")
  message(STATUS "    libraries: ${OpenCV_LIBS}")
  message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
  include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "OpenCV not found!")
endif() # OpenCV_FOUND

# Find wxWidgets
find_package(wxWidgets REQUIRED)
if(wxWidgets_FOUND)
  message(STATUS "wxWIdgets found!")
  message(STATUS "    version: ${wxWidgets_VERSION}")
  message(STATUS "    libraries: ${wxWidgets_LIBRARIES}")
  message(STATUS "    include path: ${wxWidgets_INCLUDE_DIRS}")
  include(${wxWidgets_USE_FILE})
else()
    message(FATAL_ERROR "wxWIdgets not found!")
endif() # wxWidgets_FOUND

# Find libcamera
find_package(PkgConfig REQUIRED)
message(STATUS "pkg-config path: $ENV{PKG_CONFIG_PATH}")
pkg_check_modules(LIBCAMERA REQUIRED libcamera)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(Threads_FOUND AND LIBCAMERA_FOUND)
    message(STATUS "Threads found")
    message(STATUS "libcamera library found:")
    message(STATUS "    version: ${LIBCAMERA_VERSION}")
    message(STATUS "    libraries: ${LIBCAMERA_LINK_LIBRARIES}")
    message(STATUS "    include path: ${LIBCAMERA_INCLUDE_DIRS}")
    message(STATUS "    Library found in directory: ${LIBCAMERA_LIBRARY_DIRS}")

    message (STATUS "libcamera include dir: ${libcamIncludeDir}")
    message (STATUS "path to libcamera: ${pathToLibcamera}")
    message (STATUS "path to libcamera-base: ${pathToLibcameraBase}")

    target_link_libraries(SpeedCameraPi PRIVATE Threads::Threads ${pathToLibcamera} ${pathToLibcameraBase})
    target_include_directories(SpeedCameraPi PRIVATE ${libcamIncludeDir})
else()
    message(FATAL_ERROR "Threads not found")
endif() # Threads_FOUND

# Link libraries
target_link_libraries(SpeedCameraPi PRIVATE ${OpenCV_LIBS} ${wxWidgets_LIBRARIES})


