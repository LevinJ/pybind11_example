cmake_minimum_required(VERSION 3.4)
project(example)
find_package(OpenCV 3.4.6 EXACT REQUIRED)
find_package(Eigen3)

message(STATUS "EIGEN3_INCLUDE_DIR=${EIGEN3_INCLUDE_DIR}")
include_directories(${EIGEN3_INCLUDE_DIR})

set(CMAKE_BUILD_TYPE Debug)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PYBIND11_PYTHON_VERSION  2.7)
add_subdirectory(pybind11)
pybind11_add_module(example src/main.cpp src/test_fun.cpp src/ekf.cpp src/testimage.cpp)
target_link_libraries(example  PRIVATE ${OpenCV_LIBS})
