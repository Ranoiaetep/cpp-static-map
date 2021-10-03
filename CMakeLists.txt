cmake_minimum_required(VERSION 3.20)
project(cpp_static_map)

set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-11")
set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(cpp_static_map tests/make_static_map.cpp tests/static_map.cpp)

#add_definitions(-DSM_NO_DUPLICATE -DSM_NO_THROW)

include(CTest)
include(CMakeDependentOption)
cmake_dependent_option(STATIC_MAP_BUILD_TESTS "Build Static Map Tests" ON
        "BUILD_TESTING;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
cmake_dependent_option(STATIC_MAP_BUILD_PACKAGE "Build Static Map Packages" ON
        "CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)