# M3 -- Meka Robotics Real-Time Control System
# Copyright (c) 2010 Meka Robotics
# Author: edsinger@mekabot.com (Aaron Edsinger)
# 
# M3 is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# M3 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with M3.  If not, see <http://www.gnu.org/licenses/>.

rtai_inc = $(RTAI_DIR)/include
rtai_lib = $(RTAI_DIR)/lib
m3rt_dir = $(prefix)/include/m3rt
m3rtb_dir = $(prefix)/include/m3rt/base

m3_dir = $(top_srcdir)/src/m3
bin_PROGRAMS = m3humanoid_shm_test
m3humanoid_shm_test_SOURCES = m3humanoid_shm_test.cpp
m3humanoid_shm_test_LDADD = -lprotobuf -lm3base -lorocos-kdl -lm3hardware -lm3chains -lm3robots -lm3toolbox -lyaml-cpp  -llxrt -ldl

m3humanoid_shm_test_LDFLAGS = -version-info 1:1:0 -module \
	-L$(ros_dir)/core/roscpp/lib \
	-L$(ros_dir)/core/roslib/lib \
	-L$(ros_dir)/core/rosconsole/lib \
	-L$(ros_dir)/3rdparty/xmlrpcpp/lib \
	-L$(top_srcdir)/src/m3/toolbox \
	-L$(top_srcdir)/src/m3/hardware \
	-L$(top_srcdir)/src/m3/chains \
	-L$(ros_dir)/../stacks/ros_comm/utilities/cpp_common/lib \
	-L$(ros_dir)/../stacks/ros_comm/clients/cpp/roscpp_traits/lib \
	-L$(ros_dir)/../stacks/ros_comm/clients/cpp/roscpp_serialization/lib \
	-L$(ros_dir)/../stacks/ros_comm/clients/cpp/roscpp/lib \
	-L$(ros_dir)/../stacks/ros_comm/tools/rosconsole/lib \
	-L$(ros_dir)/../stacks/ros_comm/utilities/xmlrpcpp/lib \
	-L$(rtai_lib)
m3humanoid_shm_test_CPPFLAGS =   -I$(m3_dir)/chains -I$(m3_dir)/toolbox -I$(m3_dir)/hardware -I$(m3_dir) -I$(m3tb_dir) \
	-I$(m3rt_dir) -I$(m3rtb_dir) -I$(eigen_dir) -ffast-math -pipe -mhard-float \
	$(EIGEN2_CFLAGS)\
	-I/usr/realtime/include
	-I$(ros_dir)/core/roscpp/include \
	-I$(top_srcdir)/ros/m3meka_msgs/srv_gen/cpp/include \
	-I$(top_srcdir)/ros/m3meka_msgs/msg_gen/cpp/include \
	-I$(ros_dir)/core/roslib/include \
	-I$(ros_dir)/core/rosconsole/include \
	-I$(ros_dir)/3rdparty/xmlrpcpp/src \
	-I$(ros_dir)/../stacks/ros_comm/utilities/cpp_common/include \
	-I$(ros_dir)/../stacks/ros_comm/clients/cpp/roscpp_traits/include \
	-I$(ros_dir)/../stacks/ros_comm/clients/cpp/roscpp_serialization/include \
	-I$(ros_dir)/../stacks/ros_comm/clients/cpp/roscpp/include \
	-I$(ros_dir)/../stacks/ros_comm/tools/rosconsole/include \
	-I$(ros_dir)/../stacks/ros_comm/utilities/xmlrpcpp/src \
	-I$(ros_dir)/../stacks/ros_comm/utilities/rostime/include \
	-I/opt/ros/cturtle/stacks/common_msgs/sensor_msgs/msg_gen/cpp/include \
	-I/opt/ros/cturtle/ros/core/roslib/msg_gen/cpp/include \
	-I$(rtai_inc) \
	-D__RTAI__ 
# AM_CPPFLAGS = 			-I/usr/realtime/include \
# 				$(EIGEN2_CFLAGS)
# 				-I$(m3_dir)\
# 				-I$(rtai_inc) \
# 				-D__IN_RTAI__ -ffast-math 







