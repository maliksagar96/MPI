cmake_minimum_required(VERSION 3.10)

project(arraysum)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(target_name arraysum)

find_package(MPI REQUIRED)

add_executable(${target_name} 02_arraysum_mpi.cpp)
target_include_directories(${target_name} PRIVATE ${MPI_INCLUDE_DIRS})
target_link_libraries(${target_name} PRIVATE MPI::MPI_CXX)
