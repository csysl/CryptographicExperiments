cmake_minimum_required(VERSION 3.12)
project(ECC)

set(CMAKE_CXX_STANDARD 17)

add_executable(ECC main.cpp func.h ECC.cpp)