cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(aes_test)

add_executable(
    aes_test
    aes_encryption.cpp
    constant.hpp
)