#!/usr/bin/env sh
# generated from catkin/cmake/templates/env.sh.in

if [ $# -eq 0 ] ; then
  /bin/echo "Entering environment at '/home/meka/mekabot/m3meka/ros/m3ctrl_msgs/devel', type 'exit' to leave"
  . "/home/meka/mekabot/m3meka/ros/m3ctrl_msgs/devel/setup.sh"
  "$SHELL" -i
  /bin/echo "Exiting environment at '/home/meka/mekabot/m3meka/ros/m3ctrl_msgs/devel'"
else
  . "/home/meka/mekabot/m3meka/ros/m3ctrl_msgs/devel/setup.sh"
  exec "$@"
fi
