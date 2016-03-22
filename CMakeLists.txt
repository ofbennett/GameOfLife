cmake_minimum_required(VERSION 2.8)
project(GameOfLife)

#find_package(OpenMP)
find_package(MPI)

#set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

include_directories(${MPI_CXX_INCLUDE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MPI_C_COMPILE_FLAGS}")

include_directories(src)
include_directories(lib)

add_subdirectory(src)
add_subdirectory(test)
