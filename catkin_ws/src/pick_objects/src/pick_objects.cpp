#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <std_msgs/Int32.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

enum action {picked_done = 1, dropped_done = 2};

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  
  ros::Publisher status_pub = n.advertise<std_msgs::Int32>("robot_status", 1);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup_goal;
  move_base_msgs::MoveBaseGoal dropoff_goal;
  std_msgs::Int32 statusMsg;

  // set up the frame parameters
  pickup_goal.target_pose.header.frame_id = "map";
  pickup_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pickup_goal.target_pose.pose.position.x = 1.7;
  pickup_goal.target_pose.pose.position.y = -6.5; //-8.0
  pickup_goal.target_pose.pose.orientation.w = 1.0;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(pickup_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Reached pickup goal");
    statusMsg.data = picked_done;
  	status_pub.publish(statusMsg);
  	ros::Duration(5).sleep();
  }
  else{
    ROS_INFO("The robot failed to reach the pickup goal");
  }
  
  
  // set up the frame parameters
  dropoff_goal.target_pose.header.frame_id = "map";
  dropoff_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  dropoff_goal.target_pose.pose.position.x = 15.08;
  dropoff_goal.target_pose.pose.position.y = -7.3;
  dropoff_goal.target_pose.pose.orientation.w = 0.74;
  
  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending dropoff goal");
  ac.sendGoal(dropoff_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Reached dropoff goal");
    statusMsg.data = dropped_done;
  	status_pub.publish(statusMsg);
    ros::Duration(15).sleep();
  }
  else{
    ROS_INFO("The robot failed to reach the dropoff goal");
  }

  return 0;
}