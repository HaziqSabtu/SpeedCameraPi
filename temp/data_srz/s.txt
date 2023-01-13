# cmake_minimum_required(VERSION 3.0.0)
# project(P1 VERSION 0.1.0)

# include(CTest)
# enable_testing()

# find_package(OpenCV REQUIRED PATHS C://opencv/build/x64/vc15/lib)
# include_directories(${OpenCV_INCLUDE_DIRS})


# add_executable(P1 main.cpp)

# target_link_libraries(P1 ${OpenCV_LIBS})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)


cmake_minimum_required(VERSION 3.0.0)
project( dataSrz )
find_package(OpenCV REQUIRED PATHS C://Users/kakik/OpenCV/build/install/x64/vc16/lib)
include_directories( ${OpenCV_INCLUDE_DIRS} )
# add_executable( dataSrz dataSrz.cpp DescriptorMatcher.cpp Homography.cpp ORBDetection.cpp SIFTDetection.cpp)
add_executable( dataSrz main.cpp fileWR.cpp)

target_link_libraries( dataSrz ${OpenCV_LIBS} )