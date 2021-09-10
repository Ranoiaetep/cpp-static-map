cmake_minimum_required(VERSION 3.20)
project(cpp_static_map)

set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-11")
set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(cpp_static_map main.cpp)

add_definitions(-DSM_NO_DUPLICATE -DSM_NO_THROW)
