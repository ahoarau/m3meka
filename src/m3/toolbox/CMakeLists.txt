cmake_minimum_required(VERSION 2.8.8)
project(toolbox)
set(LIBNAME "m3toolbox")



#set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#find_package(RTAI REQUIRED)
#find_package(M3 COMPONENTS HARDWARE ROBOTS CHAINS TOOLBOX SHARED_MEM REQUIRED)
find_package(M3rt REQUIRED)
#find_package(Boost COMPONENTS filesystem system REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Protobuf REQUIRED)
SET(M3_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/../..
)


include_directories(${M3RT_INCLUDE_DIR} ${RTAI_INCLUDE_DIR} ${THREADS_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${M3_INCLUDE_DIR})


# Start Protobuf stuff
file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
SET(PROTOBUF_IMPORT_DIRS ${M3RT_INCLUDE_DIR} ${M3_INCLUDE_DIR})

PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${CMAKE_CURRENT_SOURCE_DIR} ${ProtoFiles})
set_source_files_properties(${ProtoSources} ${ProtoHeaders} PROPERTIES
                            GENERATED TRUE)
                            message("ProtoFiles:${ProtoFiles} 
		ProtoSources: ${ProtoSources} 
		ProtoHeaders: ${ProtoHeaders}")
# End Protobuf stuff
message("Cmake binary dir:${CMAKE_BINARY_DIR}")

SET(LIBS ${RTAI_LIBRARIES} ${M3RT_LIBRARIES} pthread ${Boost_LIBRARIES} ${EIGEN3_LIBRARIES} ${PROTOBUF_LIBRARIES})


file(GLOB ALL_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.cpp)
file(GLOB ALL_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.h)


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
set_target_properties(${LIBNAME} PROPERTIES COMPILE_FLAGS "-I${CMAKE_BINARY_DIR}/src")

## Installing
install(TARGETS ${LIBNAME} DESTINATION lib)
install(FILES ${ALL_HDRS} DESTINATION include/m3/${PROJECT_NAME})



