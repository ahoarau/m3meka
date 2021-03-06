cmake_minimum_required(VERSION 2.8)
project(robots)
set(LIBNAME "m3robots")

find_package(M3 COMPONENTS CHAINS TOOLBOX HARDWARE)
find_package(M3rt)
include_directories(${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})

## First generate the python 
find_package(Protobuf REQUIRED)
SET(PROTOBUF_IMPORT_DIRS ${PROTOBUF_IMPORT_DIRS} ${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
## Python protobufs
find_package(PythonLibs 2.7 REQUIRED)
find_package(PythonInterp REQUIRED) 
## Generate and copy the python protobuf
PROTOBUF_GENERATE_PYTHON(PySources ${CMAKE_CURRENT_BINARY_DIR} ${ProtoFiles}) 
add_custom_target(${LIBNAME}_python_protobuf_output ALL DEPENDS ${PySources}) # force the generation
# End Protobuf stuff

## YAML CPP 
find_package(PkgConfig REQUIRED)
#find_package(YamlCpp  REQUIRED)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp)
if(${YAMLCPP_VERSION} VERSION_LESS "0.5")
set_property(
   DIRECTORY
   PROPERTY COMPILE_DEFINITIONS YAMLCPP_03
   )
endif(${YAMLCPP_VERSION} VERSION_LESS "0.5")
link_directories(${YAMLCPP_LIBRARY_DIRS})

if(RTAI)
find_package(RTAI REQUIRED)
add_definitions(-D__RTAI__)

find_package(Boost REQUIRED)
find_package(Eigen3 3.0 REQUIRED)
find_package(Protobuf REQUIRED)
find_package(orocos_kdl REQUIRED)
include_directories(${orocos_kdl_INCLUDE_DIRS})


#SET(M3_INCLUDE_DIR 
#	${CMAKE_CURRENT_SOURCE_DIR}/../..
#	${CMAKE_CURRENT_SOURCE_DIR}/../chains
#	${CMAKE_CURRENT_SOURCE_DIR}/../toolbox
#	${CMAKE_CURRENT_SOURCE_DIR}/../hardware
#)

include_directories(${M3RT_INCLUDE_DIR} ${RTAI_INCLUDE_DIR} ${THREADS_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${M3_INCLUDE_DIR})


# Start Protobuf stuff
## Cpp protobufs
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${CMAKE_CURRENT_BINARY_DIR} ${ProtoFiles})
set_source_files_properties(${ProtoSources} ${ProtoHeaders} PROPERTIES
                            GENERATED TRUE)
add_custom_target(${LIBNAME}_protobuf_tmp  ALL DEPENDS ${ProtoSources}) # Force the re-generation



SET(LIBS ${RTAI_LIBRARIES}  pthread ${Boost_LIBRARIES} ${EIGEN3_LIBRARIES} ${PROTOBUF_LIBRARIES} m3chains m3toolbox m3hardware ${orocos_kdl_LIBRARIES} m3base)


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

## Building
add_library(${LIBNAME} SHARED ${ALL_SRCS})
target_link_libraries(${LIBNAME} ${LIBS})
set_target_properties(${LIBNAME} PROPERTIES COMPILE_FLAGS "-I${CMAKE_BINARY_DIR}/src")

## Installing
install(TARGETS ${LIBNAME} DESTINATION lib)
install(FILES ${ALL_HDRS} DESTINATION include/m3/${PROJECT_NAME})

endif(RTAI)


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
   DESTINATION ${PYTHON_SITE_DIR}/m3
   COMPONENT library 
) 
