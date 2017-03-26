cmake_minimum_required(VERSION 3.6)
project(Exceptions)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Exceptions.h Exceptions.cpp)
add_executable(Exceptions ${SOURCE_FILES})