/*
 * Copyright (c) 2010, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
// %Tag(INCLUDES)%
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include<math.h>
#include <std_msgs/Int32.h>

double current_position[2] = {0,0};
double pickup_location[2]={1.7,-6.5};
double drop_location[2]={15.08,-7.3};
double mindist = 10.0;
bool pickup = false;
bool drop = false;
bool carry = false;
bool done = false;
bool started = false;

enum action {picked_done = 1, dropped_done = 2};

void statusChange(const std_msgs::Int32::ConstPtr& msg){
  ROS_INFO("New status");
  switch(msg->data)
  {
    case picked_done:
      pickup = true;
      ROS_INFO("Picked up object!");
      break;
    case dropped_done:
      drop = true;
      ROS_INFO("Dropped off object!");
      break;
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber status_sub = n.subscribe("robot_status",1,statusChange);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  while (ros::ok())
  {
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    if (!pickup and !started){
      marker.pose.position.x = pickup_location[0];
      marker.pose.position.y = pickup_location[1];
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;

      // Set the scale of the marker -- 1x1x1 here means 1m on a side
      marker.scale.x = 0.5;
      marker.scale.y = 0.5;
      marker.scale.z = 0.5;


      // Set the color -- be sure to set alpha to something non-zero!
      marker.color.r = 0.0f;
      marker.color.g = 1.0f;
      marker.color.b = 0.0f;
      marker.color.a = 1.0;
  
      marker.lifetime = ros::Duration();
      
      // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
   	  marker.action = visualization_msgs::Marker::ADD;

      // Publish the marker

      while (marker_pub.getNumSubscribers() < 1)
      {
        if (!ros::ok())
        {
          return 0;
        }
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
      }
      marker_pub.publish(marker);
      ROS_INFO("object created");
      started = true;
    }
    else if(pickup and !carry){
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ros::Duration(5).sleep();
      ROS_INFO("picked up object");
      carry = true;
    }
    else if(drop and !done){
      //ros::Duration(5).sleep();
      marker.id = 1;
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = drop_location[0];
      marker.pose.position.y = drop_location[1];
      marker_pub.publish(marker);
      ROS_INFO("dropped off object");
      done = true;
      ros::Duration(10).sleep();
    }
    ros::spinOnce();
  }
}
