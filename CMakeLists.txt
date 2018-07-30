cmake_minimum_required (VERSION 3.5)
project(NiacinMath)

# Self-defined version number
set (NiacinMath_VERSION_Major 0)
set (NiacinMath_VERSION_Minor 0)
set (NiacinMath_VERSION_Patch 0)

set (CMAKE_CP_FLAGS "-std=c++17 -O3")

include_directories(
    include
    include/number
)

# Building Type Controll
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
    add_definitions(-DDEBUGNUM)
endif()

# Installation Settings
set (CMAKE_INSTALL_PREFIX /usr/local)
add_subdirectory (include)
add_subdirectory (src)

