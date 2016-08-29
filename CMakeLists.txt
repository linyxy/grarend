cmake_minimum_required(VERSION 3.6)
project(cs184_abx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    example_00/example_00/glut-3.7.6-bin/GL/glut.h
    example_00/example_00/example_00.cpp)

add_executable(cs184_abx ${SOURCE_FILES})