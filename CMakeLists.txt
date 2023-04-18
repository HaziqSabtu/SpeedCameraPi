cmake_minimum_required(VERSION 3.10)

project(SpeedCameraPi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wno-psabi)

file(GLOB_RECURSE SRCS ./src/*.cpp EXCLUDE ./src/main.cpp)
add_executable(SpeedCameraPi ./src/main.cpp ${SRCS})

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
endif()

if(CROSS_COMPILING)
    # allow pkg-config to find the libraries in sysroot
    set(ENV{PKG_CONFIG_DIR} "")
    set(ENV{PKG_CONFIG_LIBDIR} "${CMAKE_SYSROOT}/usr/lib/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig:${CMAKE_SYSROOT}/usr/local/lib/arm-linux-gnueabihf/pkgconfig")
    set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})

    # set the include directory for libcamera
    set(libcamIncludeDir ${CMAKE_SYSROOT}/usr/local/include/libcamera)

    # POST_BUILD command to copy executable to RPi0(target)
    add_custom_command(TARGET SpeedCameraPi POST_BUILD
        COMMAND scp SpeedCameraPi RPi0:~/CrossCompile/Target
    )
else()
    set(libcamIncludeDir /usr/local/include/libcamera)
endif()

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
if(OpenCV_FOUND)
    message(STATUS "OpenCV found!")
else()
    message(FATAL_ERROR "OpenCV not found!")
endif()

# Find wxWidgets
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})
if(wxWidgets_FOUND)
    message(STATUS "wxWIdgets found!")
else()
    message(FATAL_ERROR "wxWIdgets not found!")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(Threads_FOUND AND LIBCAMERA_FOUND)
    message(STATUS "Threads found")
    message(STATUS "libcamera library found:")
    message(STATUS "    version: ${LIBCAMERA_VERSION}")
    message(STATUS "    libraries: ${LIBCAMERA_LINK_LIBRARIES}")
    message(STATUS "    include path: ${LIBCAMERA_INCLUDE_DIRS}")
    target_link_libraries(SpeedCameraPi PRIVATE Threads::Threads ${LIBCAMERA_LINK_LIBRARIES})
    target_include_directories(SpeedCameraPi PRIVATE ${libcamIncludeDir})
else()
    message(FATAL_ERROR "Threads not found")
endif()

# set(CMAKE_MODULE_PATH "/usr/local/lib/cmake" ; ${CMAKE_MODULE_PATH})
# find_package(raspicam REQUIRED)
# if(raspicam_CV_FOUND)
#     message("raspicam found!")
# else()
#     message(FATAL_ERROR "raspicam not found!")
# endif()

include_directories(include)
target_link_libraries(SpeedCameraPi PRIVATE ${OpenCV_LIBS} ${wxWidgets_LIBRARIES})


# enable_testing()
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# Add test directory and link with gtest
# add_subdirectory(test)
# target_link_libraries(SpeedCameraPi PRIVATE ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

# Add test executable
# file(GLOB_RECURSE UTILS ./src/Utils/*.cpp)
# add_executable(SpeedCameraPiTest ./test/Test.cpp ${UTILS})
# target_link_libraries(SpeedCameraPiTest PRIVATE ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${OpenCV_LIBS} ${wxWidgets_LIBRARIES})

# if(Threads_FOUND AND LIBCAMERA_FOUND)
#     message(STATUS "Threads found for test")
#     target_link_libraries(SpeedCameraPiTest PRIVATE Threads::Threads ${LIBCAMERA_LINK_LIBRARIES})
#     target_include_directories(SpeedCameraPiTest PRIVATE /usr/local/include/libcamera)
# else()
#     message(FATAL_ERROR "Threads not found")
# endif()
# # Add test to CTest
# add_test(NAME SpeedCameraPiTest COMMAND SpeedCameraPiTest)