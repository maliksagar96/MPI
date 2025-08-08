cmake_minimum_required(VERSION 3.10)

project(mat_mult)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STNDARD_REQUIRED ON)
set(target_name mat_mult)

find_package(MPI REQUIRED)

add_executable(${target_name} 03_mpi_mat_mult.cpp)
target_include_directories(${target_name} PRIVATE ${MPI_INCLUDE_DIRS})
target_link_libraries(${target_name} PRIVATE MPI::MPI_CXX)