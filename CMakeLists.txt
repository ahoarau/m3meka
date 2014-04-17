cmake_minimum_required(VERSION 2.8)
project(m3meka)
#set(LIBNAME "m3core")

SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

# Options

# Compile in c++11 (not compiling yet)
OPTION(USE_C++11 "Use c++11 (not compiling yet 10 avril 2014)" 0)


if(USE_C++11)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")
	message("-- Using c++11")
endif(USE_C++11)
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)
#find_package(RTAI REQUIRED)
#find_package(M3 COMPONENTS HARDWARE ROBOTS CHAINS TOOLBOX SHARED_MEM REQUIRED)
#find_package(M3rt REQUIRED)
#find_package(Boost COMPONENTS filesystem system REQUIRED)
#find_package(Eigen3 REQUIRED)
#find_package(Protobuf REQUIRED)

set(M3_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/m3")



MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()





SUBDIRLIST(SUBDIRS ${M3_SOURCE_DIR})
FOREACH(subdir ${SUBDIRS})
        message("-- adding dir : ${M3_SOURCE_DIR}/${subdir}")
ENDFOREACH()

FOREACH(subdir ${SUBDIRS})
    ADD_SUBDIRECTORY(${M3_SOURCE_DIR}/${subdir})
ENDFOREACH()
############set(M3RT_RT_SYSTEM_SOURCE_DIR "${M3RT_SOURCE_DIR}/rt_system")
#add_subdirectory(src/m3rt/ethercat)
#add_subdirectory(python)
#add_subdirectory(src/m3rt/base)
#add_subdirectory(src/m3rt/rt_system)

    

#add_subdirectory(python)


########### install files ###############

#install(FILES  m3base.pc $(DESTINATION) )
#install(FILES  
#ros/m3_msgs/msg_gen/cpp/include/m3_msgs/M3BaseStatus.h  		
#ros/m3_msgs/srv_gen/cpp/include/m3_msgs/M3ComponentCmd.h  		
#ros/m3_msgs/srv_gen/cpp/include/m3_msgs/M3ComponentParam.h  		
#ros/m3_msgs/srv_gen/cpp/include/m3_msgs/M3ComponentStatus.h $(DESTINATION)/include)
#install(FILES  scripts/m3rt_rotate_logs  	scripts/m3rt_server_run  	scripts/m3rt_server_kill  	scripts/m3rt_server_debug  	scripts/disable_ros  	scripts/lsec scripts/m3rt_insmods  	scripts/m3rt_rmmods	 $(DESTINATION) )



#original Makefile.am contents follow:

## M3 -- Meka Robotics Robot Components
## Copyright (c) 2010 Meka Robotics
## Author: edsinger@mekabot.com (Aaron Edsinger)
#
## 
## M3 is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## M3 is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
## 
## You should have received a copy of the GNU Lesser General Public License
## along with M3.  If not, see <http://www.gnu.org/licenses/>.
#ACLOCAL_AMFLAGS = -I m4
#AM_CPPFLAGS = -g 
#
## NOTE:  must add ros path to ROS_PACKAGE_PATH first...
#
## NOTE: to do make install you must 'su root'
#
##ros/m3_msgs 
#if ETHERCAT
#SUBDIRS = src/m3rt/base \
#	src/m3rt/rt_system \
#	src/m3rt/ethercat \
#	python
#else
#SUBDIRS = src/m3rt/base \
#	src/m3rt/rt_system \
#	src/m3rt/ethercat_fake \
#	python
#endif
#
#dist_bin_SCRIPTS = \
#	scripts/m3rt_rotate_logs \
#	scripts/m3rt_server_run \
#	scripts/m3rt_server_kill \
#	scripts/m3rt_server_debug \
#	scripts/disable_ros \
#	scripts/lsec scripts/m3rt_insmods \
#	scripts/m3rt_rmmods	
#
#EXTRA_DIST = \
#        autogen.sh \
#        configure
#
#pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = m3base.pc
#
#includedir =  /usr/local/include/m3_msgs
#
#include_HEADERS = ros/m3_msgs/msg_gen/cpp/include/m3_msgs/M3BaseStatus.h \
#		ros/m3_msgs/srv_gen/cpp/include/m3_msgs/M3ComponentCmd.h \
#		ros/m3_msgs/srv_gen/cpp/include/m3_msgs/M3ComponentParam.h \
#		ros/m3_msgs/srv_gen/cpp/include/m3_msgs/M3ComponentStatus.h
#
#
#
#		
#package: 
#	dpkg-buildpackage
