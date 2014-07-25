cmake_minimum_required(VERSION 2.8)
project(m3meka)

OPTION(RTAI "Enable/Disable RTAI (used for python proxy users only)" ON)
if(RTAI)
  find_package(RTAI)
endif()
if(RTAI AND NOT RTAI_FOUND)
  set(RTAI OFF)
  message(WARNING "Rtai not present, only generating python")
endif()

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

