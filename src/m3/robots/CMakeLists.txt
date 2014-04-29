cmake_minimum_required(VERSION 2.8)
project(robots)
set(LIBNAME "m3robots")



#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(RTAI REQUIRED)
#find_package(M3 COMPONENTS HARDWARE ROBOTS CHAINS TOOLBOX SHARED_MEM REQUIRED)
find_package(M3rt REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(OROCOS-KDL REQUIRED)
SET(M3_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
	${CMAKE_CURRENT_SOURCE_DIR}/../chains
	${CMAKE_CURRENT_SOURCE_DIR}/../toolbox
	${CMAKE_CURRENT_SOURCE_DIR}/../hardware
)

include_directories(${M3RT_INCLUDE_DIR} ${RTAI_INCLUDE_DIR} ${THREADS_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${M3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})


# Start Protobuf stuff
## Cpp protobufs
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
PROTOBUF_GENERATE_PYTHON(PySources ${CMAKE_CURRENT_BINARY_DIR} ${ProtoFiles}) 
add_custom_target(${LIBNAME}_python_protobuf_output ALL DEPENDS ${PySources}) # force the generation
# End Protobuf stuff


SET(LIBS ${RTAI_LIBRARIES} ${M3RT_LIBRARIES} pthread ${Boost_LIBRARIES} ${EIGEN3_LIBRARIES} ${PROTOBUF_LIBRARIES} m3chains m3toolbox m3hardware orocos-kdl)


set( ALL_SRCS 
factory_proxy.cpp
haptic_demo.cpp
humanoid.cpp
humanoid_shm.cpp
robot.cpp

)
set( ALL_HDRS 
chain_name.h
haptic_demo.h
humanoid.h
humanoid_shm.h
humanoid_shm_sds.h
robot.h

)

list(APPEND ALL_SRCS ${ProtoSources})

#file(GLOB ProtoFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.proto )
list(APPEND ALL_HDRS
${ProtoHeaders}
${ProtoFiles}
)

message("ALL SRC in ${PROJECT_NAME}:${ALL_SRCS}")


## Building
add_library(${LIBNAME} SHARED ${ALL_SRCS})
target_link_libraries(${LIBNAME} ${LIBS})
add_dependencies(${LIBNAME} m3chains m3toolbox m3hardware orocos-kdl)
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
