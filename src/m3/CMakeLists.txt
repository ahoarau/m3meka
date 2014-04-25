cmake_minimum_required(VERSION 2.8)
project(m3)

#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#find_package(RTAI REQUIRED)
#find_package(M3 COMPONENTS HARDWARE ROBOTS CHAINS TOOLBOX SHARED_MEM REQUIRED)
#find_package(M3rt REQUIRED)
#find_package(Boost COMPONENTS filesystem system REQUIRED)
#find_package(Eigen3 REQUIRED)
#find_package(Protobuf REQUIRED)


SET(SUBS
chains
hardware
inverse_kine
robot_ctrl
robots
shared_mem
toolbox
vehicles
)

foreach(SUB ${SUBS})
ADD_SUBDIRECTORY(${SUB})
endforeach()



