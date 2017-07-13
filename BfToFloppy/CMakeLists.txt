cmake_minimum_required(VERSION 3.4)
project(BfToFloppy)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/FloppyImage.cpp)
add_executable(BfToFloppy ${SOURCE_FILES})
