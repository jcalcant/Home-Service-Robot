#!/bin/sh
xterm -e " cd $(pwd)/../..;
source devel/setup.bash;
export ROBOT_INITIAL_POSE='-x -2.5 -y 2.05 -z 0 -R 0 -P 0 -Y 0';
roslaunch turtlebot_gazebo turtlebot_world.launch  world_file:=$(pwd)/../my_robot/worlds/project4.world " &
sleep 5
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
roslaunch turtlebot_gazebo amcl_demo.launch " & 
sleep 5
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
roslaunch turtlebot_rviz_launchers view_navigation.launch "


