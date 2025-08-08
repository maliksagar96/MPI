cmake_minimum_required(VERSION 3.10)

project(vector_addition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MPI REQUIRED)
set(target_name vector_addition)

add_executable(${target_name} 01_vector_add.cpp)

target_include_directories(${target_name} PRIVATE ${MPI_INCLUDE_DIRS})
target_link_libraries(${target_name} PRIVATE MPI::MPI_CXX)


