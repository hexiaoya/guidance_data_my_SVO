/*
	FILE: 
	Author:hy
	Description:
*/
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ofstream outfile;
ofstream outfile1;

/* imu from SVO_bag */
/*
void Rig_callback(const geometry_msgs::PoseStamped& g_imu)
{ 
	outfile <<  std::setprecision(9) \
		<< setiosflags(ios::fixed) \
		<< g_imu.header.stamp.sec+g_imu.header.stamp.nsec*1e-9 << " "\
		<< g_imu.pose.position.x << " "\
		<< g_imu.pose.position.y << " " \
		<< g_imu.pose.position.z << " " \
		<< g_imu.pose.orientation.x << " "\
		<< g_imu.pose.orientation.y << " "\
		<< g_imu.pose.orientation.z << " "\
		<< g_imu.pose.orientation.w << " " << endl;
}*/
/* svo from EuRoC_bag */
/*
void EuRoC_callback(const geometry_msgs::TransformStamped& g_imu)
{ 
	outfile <<  std::setprecision(9) \
		<< setiosflags(ios::fixed) \
		<< g_imu.header.stamp.sec+g_imu.header.stamp.nsec*1e-9 << " "\
		<< g_imu.transform.translation.x << " "\
		<< g_imu.transform.translation.y << " " \
		<< g_imu.transform.translation.z << " " \
		<< g_imu.transform.rotation.x << " "\
		<< g_imu.transform.rotation.y << " "\
		<< g_imu.transform.rotation.z << " "\
		<< g_imu.transform.rotation.w << " " << endl;
}*/
/* svo from 真实数据 */
void svo_callback(const geometry_msgs::PoseWithCovarianceStamped& g_imu)
{ 
	outfile1 <<  std::setprecision(9) \
		<< setiosflags(ios::fixed) \
		<< g_imu.header.stamp.sec+g_imu.header.stamp.nsec*1e-9 << " "\
		<< g_imu.pose.pose.position.x << " "\
		<< g_imu.pose.pose.position.y << " " \
		<< g_imu.pose.pose.position.z << " " \
		<< g_imu.pose.pose.orientation.x << " "\
		<< g_imu.pose.pose.orientation.y << " "\
		<< g_imu.pose.pose.orientation.z << " "\
		<< g_imu.pose.pose.orientation.w << " " << endl;
}
/* svo from guidance */
void guidance_callback(const geometry_msgs::Vector3Stamped& g_imu)
{ 
	outfile <<  std::setprecision(9) \
		<< setiosflags(ios::fixed) \
		<< g_imu.header.stamp.sec+g_imu.header.stamp.nsec*1e-9 << " "\
		<< g_imu.vector.x << " "\
		<< g_imu.vector.y << " " \
		<< g_imu.vector.z << " " << endl;
}

int main(int argc, char** argv)
{
	ros::init(argc,argv,"mono_video_sub");
	ros::NodeHandle my_node;

	/* Topic: mono_video -- Type: sensor_msgs::Image */
	// ros::Subscriber rig_sub = my_node.subscribe("/Rig",2,Rig_callback);
	// ros::Subscriber svo_sub = my_node.subscribe("/svo/pose",2,svo_callback);
	
	ros::Subscriber rig_sub = my_node.subscribe("/guidance/position",2,guidance_callback);
	ros::Subscriber svo_sub = my_node.subscribe("/svo/pose",2,svo_callback);
	outfile.open("/home/hexiaoya/svo_acc/trajectory.txt");

	outfile1.open("/home/hexiaoya/svo_acc/svo.txt");
	while(ros::ok())
	{
		ros::spin();
	}	
 
	outfile.close();
	outfile1.close();

	return 0;
}
