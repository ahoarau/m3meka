cmake_minimum_required(VERSION 2.8)
project(chains)
set(LIBNAME "m3chains")


#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(RTAI REQUIRED)
#find_package(M3 COMPONENTS HARDWARE ROBOTS CHAINS TOOLBOX SHARED_MEM REQUIRED)
find_package(M3rt REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 3.0 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(OROCOS-KDL REQUIRED)
SET(M3_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../toolbox
	${CMAKE_CURRENT_SOURCE_DIR}/../hardware
)

include_directories(${M3RT_INCLUDE_DIR} ${RTAI_INCLUDE_DIR} ${THREADS_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${M3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${KDL_INCLUDE_DIRS})


# Start Protobuf stuff
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
SET(PROTOBUF_IMPORT_DIRS ${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${CMAKE_CURRENT_SOURCE_DIR} ${ProtoFiles})
set_source_files_properties(${ProtoSources} ${ProtoHeaders} PROPERTIES
                            GENERATED TRUE)
add_custom_target(${LIBNAME}_protobuf_tmp  ALL DEPENDS ${ProtoSources}) # Force the re-generation
## Python protobufs
find_package(PythonLibs 2.7 REQUIRED)
find_package(PythonInterp REQUIRED) 
## Generate and copy the python protobuf
SET(PROTOBUF_IMPORT_DIRS ${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})
PROTOBUF_GENERATE_PYTHON(PySources ${CMAKE_CURRENT_BINARY_DIR} ${ProtoFiles}) 
add_custom_target(${LIBNAME}_python_protobuf_output ALL DEPENDS ${PySources}) # force the generation
# End Protobuf stuff


SET(LIBS ${RTAI_LIBRARIES}  pthread ${Boost_LIBRARIES} ${EIGEN3_LIBRARIES} ${PROTOBUF_LIBRARIES} m3hardware m3toolbox m3base)


set( ALL_SRCS 
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
set( ALL_HDRS 
arm.h
dynamatics.h
dynamatics.pb.h
gripper.h
hand.h
hand_ua.h
hand_ua.pb.h
head.h
joint_array.h
joint_array_mode.pb.h
joint_array.pb.h
joint_chain.h
torso.h
)

list(APPEND ALL_SRCS ${ProtoSources})

list(APPEND ALL_HDRS
${ProtoHeaders}
${ProtoFiles}
)



## Building
add_library(${LIBNAME} SHARED ${ALL_SRCS})
target_link_libraries(${LIBNAME} ${LIBS})
set_target_properties(${LIBNAME} PROPERTIES COMPILE_FLAGS "-I${CMAKE_BINARY_DIR}/src")

## Installing
install(TARGETS ${LIBNAME} DESTINATION lib)
install(FILES ${ALL_HDRS} DESTINATION include/m3/${PROJECT_NAME})

execute_process ( 
   COMMAND ${PYTHON_EXECUTABLE} -c 
   	"import site, sys; sys.stdout.write(site.PREFIXES[-1])" 
   OUTPUT_VARIABLE PYTHON_PREFIX 
) 
file ( TO_CMAKE_PATH "${PYTHON_PREFIX}" PYTHON_PREFIX ) 
execute_process ( 
   COMMAND ${PYTHON_EXECUTABLE} -c 
   	"import site, sys; sys.stdout.write(site.getsitepackages()[-1])" 
   OUTPUT_VARIABLE PYTHON_SITE_DIR 
) 
file ( TO_CMAKE_PATH "${PYTHON_SITE_DIR}" PYTHON_SITE_DIR ) 
string ( REGEX REPLACE "^${PYTHON_PREFIX}/" "" 
   PYTHON_SITE_DIR "${PYTHON_SITE_DIR}" 
) 


install ( FILES ${PySources} 
   DESTINATION ${PYTHON_SITE_DIR}/m3/
   COMPONENT library 
) 


