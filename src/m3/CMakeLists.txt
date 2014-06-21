
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



