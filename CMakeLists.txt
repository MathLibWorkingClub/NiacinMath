cmake_minimum_required (VERSION 3.5)
project(NiacinMath)

set (NiacinMath_VERSION_Major 0)
set (NiacinMath_VERSION_Minor 0)

set (CMAKE_CXX_FLAGS "-std=c++17 -O3")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/number
)

set (CMAKE_INSTALL_PREFIX /usr/local)
add_subdirectory (include)
add_subdirectory (src)

