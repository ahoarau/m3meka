cmake_minimum_required(VERSION 2.8.8)
project(m3vehicles)
set(LIBNAME "m3vehicles")



#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(RTAI REQUIRED)
#find_package(M3 COMPONENTS HARDWARE ROBOTS CHAINS TOOLBOX SHARED_MEM REQUIRED)
find_package(Holomni REQUIRED)
find_package(M3rt REQUIRED)
find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Protobuf REQUIRED)
SET(M3_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../chains
	${CMAKE_CURRENT_SOURCE_DIR}/../toolbox
	${CMAKE_CURRENT_SOURCE_DIR}/../hardware
)


include_directories(${M3RT_INCLUDE_DIR} ${RTAI_INCLUDE_DIR} ${THREADS_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${M3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})


# Start Protobuf stuff
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
SET(PROTOBUF_IMPORT_DIRS ${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${CMAKE_CURRENT_SOURCE_DIR} ${ProtoFiles})
# End Protobuf stuff


SET(LIBS ${RTAI_LIBRARIES} ${M3RT_LIBRARIES} pthread ${Boost_LIBRARIES} ${EIGEN3_LIBRARIES} ${PROTOBUF_LIBRARIES} m3chains m3toolbox m3hardware)


#FILE(GLOB SRCFILES *.cxx)
SET(SRCFILES
factory_proxy.cpp
omnibase.cpp
omnibase_shm.cpp
vehicle.cpp
)

SET(${LIBNAME}_SRCS
${SRCFILES}
${ProtoSources}
${ProtoHeaders})

add_library(${LIBNAME} SHARED ${${LIBNAME}_SRCS})
target_link_libraries(${LIBNAME} ${LIBS})
