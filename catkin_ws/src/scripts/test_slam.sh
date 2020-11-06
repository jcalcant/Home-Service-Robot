#!/bin/sh
xterm -e " cd $(pwd)/../..;
source devel/setup.bash;
export ROBOT_INITIAL_POSE='-x -6.5 -y 3.7 -z 0 -R 0 -P 0 -Y 0';
roslaunch turtlebot_gazebo turtlebot_world.launch  world_file:=$(pwd)/../my_robot/worlds/HSR_project.world " &
sleep 20
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash;
rosparam set /slam_gmapping/map_update_interval 0.08;
rosparam set /slam_gmapping/linearUpdate 0.05;
rosparam set /slam_gmapping/angularUpdate 0.05;
rosparam set /slam_gmapping/particles 200;
rosparam set /slam_gmapping/srr 0.02;
rosparam set /slam_gmapping/srt 0.02;
rosparam set /slam_gmapping/str 0.02;
rosparam set /slam_gmapping/stt 0.02;
rosparam set /slam_gmapping/xmin -10.0;
rosparam set /slam_gmapping/ymin -10.0;
rosparam set /slam_gmapping/xmax 10.0;
rosparam set /slam_gmapping/ymax 10.0;
rosparam set /slam_gmapping/minimumScore 100.0;
roslaunch turtlebot_gazebo gmapping_demo.launch " & 
sleep 5
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm  -e  " cd $(pwd)/../..;
source devel/setup.bash; 
roslaunch turtlebot_teleop keyboard_teleop.launch "



