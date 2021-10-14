cmake_minimum_required(VERSION 3.20)
project(cpp_static_map)

set(CMAKE_CXX_COMPILER "g++-11")
set(CMAKE_CXX_STANDARD 20)

add_library(Static_map INTERFACE Static_map.hpp)
target_include_directories(Static_map INTERFACE ./)
link_libraries(Static_map)

#add_definitions(-DSM_NO_DUPLICATE -DSM_NO_THROW)

include(CTest)
include(CMakeDependentOption)
cmake_dependent_option(STATIC_MAP_BUILD_TESTS "Build Static Map Tests" ON
        "BUILD_TESTING;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)
cmake_dependent_option(STATIC_MAP_BUILD_PACKAGE "Build Static Map Packages" ON
        "CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if (BUILD_TESTING)
        add_subdirectory(tests)
    endif ()
endif()