#include "ros/ros.h"
#include <ros/package.h> 
#include <iostream> 
#include <fstream> 
#include <iomanip> 

#include "visualization_msgs/MarkerArray.h"
#include "raspimouse_ros_2/ButtonValues.h"
#include "raspimouse_ros_2/LedValues.h"
#include "cartographer_ros_msgs/FinishTrajectory.h"
#include "cartographer_ros_msgs/WriteState.h"

using namespace ros;

bool mapping_finished = false;
bool trajectory_finished = false;

void callbackButtons(const raspimouse_ros_2::ButtonValues::ConstPtr& msg)
{
	if (msg->front){
		ROS_INFO("mapping terminated");
		mapping_finished = true;
	}
}

void callbackTrajectory(const visualization_msgs::MarkerArray::ConstPtr& msg)
{
	if(trajectory_finished)
		return; 

	std::ofstream f("/tmp/trajectory.tsv"); 
	int size = msg->markers.size();
	for(auto p : msg->markers[size-1].points ){ 
		f << std::fixed;
		f << std::setprecision(3) << p.x << "\t" << p.y << std::endl;
	}
	trajectory_finished = true;
	ROS_INFO("trajectory extracted");
}

int main(int argc, char **argv)
{
	init(argc,argv,"trajectory_extractor");
	NodeHandle n;

	Subscriber sub = n.subscribe("/buttons", 1, callbackButtons);
	Publisher pub = n.advertise<raspimouse_ros_2::LedValues>("leds", 5);

	raspimouse_ros_2::LedValues leds;
	leds.left_side = true;
	leds.right_side = false;
	leds.left_forward = false;
	leds.right_forward = false;

        Rate loop_rate(5);
        while(ok() and not mapping_finished){
                pub.publish(leds);
                spinOnce();
                loop_rate.sleep();
        }


	cartographer_ros_msgs::FinishTrajectory::Request ftr;
	cartographer_ros_msgs::FinishTrajectory::Response ftrs;
	ftr.trajectory_id = 0;
	service::call("/finish_trajectory", ftr, ftrs);
	ROS_INFO("%s", ftrs.status.message.c_str());

	cartographer_ros_msgs::WriteState::Request wsr;
	cartographer_ros_msgs::WriteState::Response wsrs;
	wsr.filename = "/tmp/cartographer.bag.pbstream";
	//wsr.include_unfinished_submaps = true;
	service::call("/write_state", wsr, wsrs);
	ROS_INFO("%s", wsrs.status.message.c_str());

	if(not system("rosrun map_server map_saver -f /tmp/map"))
		ROS_ERROR("CANNOT SAVE MAP");


	/*
	map_msgs::SaveMap::Request msr;
	map_msgs::SaveMap::Response msrs;
	msr.data = "/tmp/map";
	service::call("/save_map", wsr, wsrs);
	*/

	Subscriber sub_trajectory = n.subscribe("/trajectory_node_list", 1, callbackTrajectory);

	leds.left_side = false;
        while(ok() and mapping_finished){
        	pub.publish(leds);

		if(trajectory_finished)
			break;

                spinOnce();
                loop_rate.sleep();
        }

	return 0;
}
