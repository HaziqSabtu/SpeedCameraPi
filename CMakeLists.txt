cmake_minimum_required(VERSION 3.10)

project(SpeedCamera)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")
add_compile_options(-Wno-psabi)

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


set(CMAKE_MODULE_PATH "/usr/local/lib/cmake" ; ${CMAKE_MODULE_PATH})
find_package(raspicam REQUIRED)
if(raspicam_CV_FOUND)
    message("raspicam found!")
else()
    message(FATAL_ERROR "raspicam not found!")
endif()

include_directories(include)
file(GLOB_RECURSE SRCS ./src/*.cpp)
add_executable(SpeedCamera ./src/main.cpp ${SRCS})
target_link_libraries(SpeedCamera PRIVATE ${OpenCV_LIBS} ${wxWidgets_LIBRARIES} ${raspicam_CV_LIBS})
