
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
include_directories(${CMAKE_CURRENT_BINARY_DIR}/${SUB})
endforeach()

foreach(SUB ${SUBS})
ADD_SUBDIRECTORY(${SUB})
endforeach()

