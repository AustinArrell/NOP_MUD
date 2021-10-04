
cmake_minimum_required(VERSION 3.0)

project(nopmud)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/sfml")
add_subdirectory("${CMAKE_SOURCE_DIR}/server")
add_subdirectory("${CMAKE_SOURCE_DIR}/client")
