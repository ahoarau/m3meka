cmake_minimum_required(VERSION 2.8)
project(m3meka_src)

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



