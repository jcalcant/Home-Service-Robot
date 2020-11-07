This is the project repo for the final project of the Udacity Robotics Software Engineer Nanodegree: Home Service Robot.

### Usage
pip install rospkg

```
cd catkin_ws
catkin_make
source devel/setup.bash

cd src/scripts
./{$script name} e.g. add_marker.sh, home_service.sh, pick_objects.sh, test_navigation.sh, test_slam.sh
```

### Project Reflection
This project covered several topics from the nanodegree. First, I experimented with creating shell scripts for launching several ros nodes, which would be the case for the next steps. Then, I set up my ros environment by downloading the necessary ros packages for mapping, navigating and using the turtlebot 3. I then mapped (test_slam.sh) my previously created gazebo .world file. There were complications since the kinect from the turtlebot didn't sense all the landmarks and also the environment was too big. Thus, I resized and refactored the environment for optimal mapping. After saving the .pgm and .yaml map files, I cleaned the .pgm with gimp, since unexplored regions wouldn't allow the robot to move forwards. With a clean map, I tested navigation with the turtlebot navigation demo (test_navigation.sh). From there, things got more intereseting, by creating my own navigation goal node and setting a pick up and drop off location, for simulating that the robot would pick and drop off objects within a home (pick_objects.sh). In addition I created a basic marker shape to appear at the pickup location and then disappear until it was dropped off (add_marker.sh). The corresponding node for this (add_marker) would then be connected with the previous (pick_objects) so that the robot would perform the whole task. The challenge was connecting them. My first attempts used pose from /odom and /acml_pose, but /odom was not precise and /acml_pose didn't publish messages. Thus, I sent a flag or status message directly from the pick_objects node) and added a corresponding subscriber in the add_marker node. This flag would then trigger the apparition or disapparition of the marker.
Overall, this capstone project helped me consolidate these main topics: localization, mapping, navigation, setting, goals and markers, ros services.

This is the video of the final task (home_service.sh): https://youtu.be/pNJ9dDrOIL0
