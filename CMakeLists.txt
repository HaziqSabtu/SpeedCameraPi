cmake_minimum_required(VERSION 3.10)

project(SpeedCamera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")
add_compile_options(-Wno-psabi)

file(GLOB_RECURSE SRCS ./src/*.cpp)
add_executable(SpeedCamera ./src/main.cpp ${SRCS})

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
if(OpenCV_FOUND)
    message("OpenCV found!")
else()
    message(FATAL_ERROR "OpenCV not found!")
endif()

# Find wxWidgets
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})
if(wxWidgets_FOUND)
    message("wxWIdgets found!")
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
    target_link_libraries(SpeedCamera PRIVATE Threads::Threads ${LIBCAMERA_LINK_LIBRARIES})
    target_include_directories(SpeedCamera PRIVATE /usr/local/include/libcamera)
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
target_link_libraries(SpeedCamera PRIVATE ${OpenCV_LIBS} ${wxWidgets_LIBRARIES})
