#!/bin/sh
xterm -e " cd $(pwd)/../..;
source devel/setup.bash;
export ROBOT_INITIAL_POSE='-x -6.5 -y 3.7 -z 0 -R 0 -P 0 -Y 0';
roslaunch turtlebot_gazebo turtlebot_world.launch  world_file:=$(pwd)/../my_robot/worlds/HSR_project.world " &
sleep 20
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../map/map.yaml" & 
sleep 5
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 20
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
rosrun add_markers add_markers " &
sleep 60
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
rosrun pick_objects pick_objects "

