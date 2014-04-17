cmake_minimum_required(VERSION 2.8)
project(m3chains)
set(LIBNAME "m3chains")



#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(RTAI REQUIRED)
#find_package(M3 COMPONENTS HARDWARE ROBOTS CHAINS TOOLBOX SHARED_MEM REQUIRED)
find_package(M3rt REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(OROCOS-KDL REQUIRED)
SET(M3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../toolbox
		${CMAKE_CURRENT_SOURCE_DIR}/../hardware
		${CMAKE_CURRENT_SOURCE_DIR}/../toolbox
		${CMAKE_CURRENT_SOURCE_DIR}/../robots
		${CMAKE_CURRENT_SOURCE_DIR}/../shared_mem
		${CMAKE_CURRENT_SOURCE_DIR}/../chains)

include_directories(${M3RT_INCLUDE_DIR} ${RTAI_INCLUDE_DIR} ${THREADS_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${M3_INCLUDE_DIR})


# Start Protobuf stuff
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
SET(PROTOBUF_IMPORT_DIRS ${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${CMAKE_CURRENT_SOURCE_DIR} ${ProtoFiles})
# End Protobuf stuff


SET(LIBS ${RTAI_LIBRARIES} ${M3RT_LIBRARIES} pthread ${Boost_LIBRARIES} ${EIGEN3_LIBRARIES})


## TODO: add local files
##FILE(GLOB SRCFILES *.cxx)
SET(SRCFILES
arm.cpp
dynamatics.cpp
factory_proxy.cpp
gripper.cpp
hand.cpp
hand_ua.cpp
head.cpp
joint_array.cpp
joint_chain.cpp
torso.cpp
)
SET(${LIBNAME}_SRCS
${SRCFILES}
${ProtoSources}
${ProtoHeaders})

add_library(${LIBNAME} SHARED ${${LIBNAME}_SRCS})
target_link_libraries(${LIBNAME} ${LIBS})
add_dependencies(${LIBNAME} m3toolbox m3hardware)



