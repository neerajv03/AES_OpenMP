cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(aes_test)

add_executable(
    aes_encryption
    aes_encryption.cpp
    constant.hpp
    project_utilities.cpp
    project_utilities.hpp
    counter_mode.cpp
    counter_mode.hpp
    parallelize_operation.cpp
    parallelize_operation.hpp
)