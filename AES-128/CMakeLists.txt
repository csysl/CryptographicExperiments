cmake_minimum_required(VERSION 3.12)
project(AES)

set(CMAKE_CXX_STANDARD 17)

add_executable(AES func.h main.cpp AES.cpp)