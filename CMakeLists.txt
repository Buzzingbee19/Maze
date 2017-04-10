cmake_minimum_required(VERSION 3.6)
project(Maze)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp graph.h Cell.cpp Cell.h d_except.h d_matrix.h)
add_executable(Maze ${SOURCE_FILES})