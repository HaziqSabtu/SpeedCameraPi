cmake_minimum_required(VERSION 3.10)

project(Example_ImageAlignment)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
set(CMAKE_PREFIX_PATH "~/cxcmpl/cv/local/lib/cmake/opencv4" ${CMAKE_PREFIX_PATH})

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

add_executable(Example_ImageAlignment ImageAlignment.cpp ${ALGORITHM_SRCS} ${DATA_STRUCT_SRCS} ${STRUCT_SRCS} ${IMAGEUTILS_SRCS})
target_link_libraries(Example_ImageAlignment PRIVATE ${OpenCV_LIBS})

add_custom_command(TARGET Example_ImageAlignment POST_BUILD
COMMAND ssh RPi0 "mkdir -p ~/Target"
COMMAND scp $<TARGET_FILE:Example_ImageAlignment> RPi0:~/Target/
)