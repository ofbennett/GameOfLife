cmake_minimum_required(VERSION 2.8)
project(GameOfLife)

find_package(CUDA)

list(APPEND CUDA_NVCC_FLAGS -arch sm_35;-std=c++11;)
include_directories(src)
include_directories(lib)

add_subdirectory(src)
add_subdirectory(test)
