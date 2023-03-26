cmake_minimum_required(VERSION 3.10)

project(Example_ObjectDetection)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
if(OpenCV_FOUND)
    message("OpenCV found!")
else()
    message(FATAL_ERROR "OpenCV not found!")
endif()

include_directories(../../include)
message("Include directories: ${CMAKE_INCLUDE_DIRECTORIES}")
file(GLOB_RECURSE ALGORITHM_SRCS ../../src/Algorithm/*.cpp)
file(GLOB_RECURSE DATA_STRUCT_SRCS ../../src/Utils/DataStruct.cpp)
file(GLOB_RECURSE IMAGEUTILS_SRCS ../../src/Utils/ImageUtils.cpp)
file(GLOB_RECURSE STRUCT_SRCS ../../src/Utils/Struct/*.cpp)

add_executable(Example_ObjectDetection ${ALGORITHM_SRCS} ${DATA_STRUCT_SRCS} ${STRUCT_SRCS} ${IMAGEUTILS_SRCS} objectDetection.cpp)
target_link_libraries(Example_ObjectDetection PRIVATE ${OpenCV_LIBS})