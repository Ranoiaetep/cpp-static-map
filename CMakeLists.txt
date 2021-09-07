cmake_minimum_required(VERSION 3.20)
project(cpp_static_map)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(cpp_static_map
        main.cpp static_map.cpp static_map.h)
