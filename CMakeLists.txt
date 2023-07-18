cmake_minimum_required(VERSION 3.10)

project(SpeedCameraPi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wno-psabi -D gtest_disable_pthreads=OFF)

include_directories(include)
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
endif() # UNIX AND EXISTS "/etc/os-release"

if(CROSS_COMPILING)
    # allow pkg-config to find the libraries in sysroot
    set(ENV{PKG_CONFIG_DIR} "")
    set(ENV{PKG_CONFIG_LIBDIR} "${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf/pkgconfig:${CMAKE_SYSROOT}/usr/lib/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig:${CMAKE_SYSROOT}/usr/local/lib/arm-linux-gnueabihf/pkgconfig")
    set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})

    # set the include directory for libcamera
    set(libcamIncludeDir ${CMAKE_SYSROOT}/usr/include/libcamera)

    # set the prefix location for wxWidgets
    set(wxWidgets_CONFIG_OPTIONS --prefix=${CMAKE_SYSROOT}/usr/local)

    # POST_BUILD command to copy executable to RPi0(target)
    add_custom_command(TARGET SpeedCameraPi POST_BUILD
        COMMAND ssh RPi0 "mkdir -p ~/Target"
        COMMAND scp $<TARGET_FILE:SpeedCameraPi> RPi0:~/Target/
        COMMAND scp ${CMAKE_SOURCE_DIR}/Speed.ico RPi0:~/Target/
        COMMAND scp ${CMAKE_SOURCE_DIR}/exit.ico RPi0:~/Target/
    )

    # POST_BUILD command curl
    # add_custom_command(TARGET SpeedCameraPi POST_BUILD
    #     COMMAND curl --location '192.168.178.20:8080/wav/succ'
    # )
else()
    set(libcamIncludeDir /usr/include/libcamera)
    
    add_custom_command(TARGET SpeedCameraPi POST_BUILD
        COMMAND cp ${CMAKE_SOURCE_DIR}/Speed.ico $<TARGET_FILE_DIR:SpeedCameraPi>
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
    message(STATUS "    Library found in directory: ${LIBCAMERA_LIBRARY_DIRS}")

    target_link_libraries(SpeedCameraPi PRIVATE Threads::Threads ${LIBCAMERA_LINK_LIBRARIES})
    target_include_directories(SpeedCameraPi PRIVATE ${libcamIncludeDir})
else()
    message(FATAL_ERROR "Threads not found")
endif() # Threads_FOUND

# set(CMAKE_MODULE_PATH "/usr/local/lib/cmake" ; ${CMAKE_MODULE_PATH})
# find_package(raspicam REQUIRED)
# if(raspicam_CV_FOUND)
#     message("raspicam found!")
# else()
#     message(FATAL_ERROR "raspicam not found!")
# endif()

target_link_libraries(SpeedCameraPi PRIVATE ${OpenCV_LIBS} ${wxWidgets_LIBRARIES})

# set boolean
option(ENABLE_TESTING "Enable Test Builds" OFF)

if(ENABLE_TESTING)
  message(STATUS "Testing enabled")

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  file(GLOB_RECURSE ALG    src/Algorithm/*.cpp)
  file(GLOB_RECURSE EVENT  src/Event/*.cpp)
  file(GLOB_RECURSE MODEL  src/Model/*.cpp)
  file(GLOB_RECURSE THREAD src/Thread/*.cpp)
  file(GLOB_RECURSE UTILS  src/Utils/*.cpp)

  file(GLOB_RECURSE MODELTEST tests/Model/*.cpp)

  add_executable(
    Tests
    tests/testableframe.cpp

    ${THREAD} 
    ${MODEL} 
    ${EVENT} 
    ${UTILS} 
    ${ALG}

    ${MODELTEST}
  )

  target_link_libraries(
    Tests
    GTest::gtest_main
    GTest::gmock_main
    ${OpenCV_LIBS} 
    ${wxWidgets_LIBRARIES}
    ${LIBCAMERA_LINK_LIBRARIES}
    Threads::Threads 
  )

  target_include_directories(Tests PRIVATE ${libcamIncludeDir})

  add_custom_command(TARGET Tests POST_BUILD
          COMMAND ssh RPi0 "mkdir -p ~/Target"
          COMMAND scp $<TARGET_FILE:Tests> RPi0:~/Target/
      )
  
endif() # ENABLE_TESTING  


