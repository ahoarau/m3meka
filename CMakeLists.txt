cmake_minimum_required(VERSION 2.8)
project(m3meka)

# Tmp solution for the FindXXX.cmake 
set(CMAKE_MODULE_PATH 
    "${CMAKE_CURRENT_SOURCE_DIR}/../meka-cmake-modules/Modules/"
    ${CMAKE_MODULE_PATH})

set(M3_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src 
)

# Include dirs to look for
include_directories(
    ${M3_SRC}
    ${CMAKE_CURRENT_BINARY_DIR}/src
)


add_subdirectory(src)
add_subdirectory(python)

