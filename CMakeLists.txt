cmake_minimum_required(VERSION 3.6)
project(signal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test.cpp signal.h)
add_executable(signal ${SOURCE_FILES})