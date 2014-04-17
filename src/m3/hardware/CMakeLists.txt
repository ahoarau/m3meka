cmake_minimum_required(VERSION 2.8.8)
project(m3hardware)
set(LIBNAME "m3hardware")



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

SET(M3_INCLUDE_DIR
                ${CMAKE_CURRENT_SOURCE_DIR}/../..)
message("M3 : ${M3_INCLUDE_DIR}")
include_directories(${M3RT_INCLUDE_DIR} ${RTAI_INCLUDE_DIR} ${THREADS_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${M3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})


# Start Protobuf stuff
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
SET(PROTOBUF_IMPORT_DIRS ${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${CMAKE_CURRENT_SOURCE_DIR} ${ProtoFiles})
# End Protobuf stuff


SET(LIBS ${RTAI_LIBRARIES} ${M3RT_LIBRARIES} pthread ${Boost_LIBRARIES} ${EIGEN3_LIBRARIES})


#FILE(GLOB SRCFILES *.cxx)
SET(SRCFILES
actuator.cpp
actuator_ec.cpp
actuator_virtual.cpp
async_io.cpp
ctrl_simple.cpp
factory_proxy.cpp
joint.cpp
joint_slave.cpp
joint_zlift.cpp
joint_zlift_shm.cpp
led_matrix_ec.cpp
led_matrix_ec_shm.cpp
ledx2_ec.cpp
ledx2xn_ec.cpp
ledx2xn_ec_shm.cpp
loadx1.cpp
loadx1_ec.cpp
loadx6.cpp
loadx6_ec.cpp
loadx6_virtual.cpp
log_test.cpp
motor.cpp
pwr.cpp
pwr_ec.cpp
pwr_virtual.cpp
robot_monitor.cpp
sensor.cpp
tactile_pps22_ec.cpp
transmission.cpp
)
SET(${LIBNAME}_SRCS
${SRCFILES}
${ProtoSources}
${ProtoHeaders})

add_library(${LIBNAME} SHARED ${${LIBNAME}_SRCS})
target_link_libraries(${LIBNAME} ${LIBS})
add_dependencies(${LIBNAME} m3toolbox)




