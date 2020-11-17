#include <iostream>
// Eigen 部分
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆，特征值等）
#include <Eigen/Dense>
//#include "logger.h"
#include "InsAlignmentPKG/global_var.h"
#include "InsAlignmentPKG/InsAlignment.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

using namespace std;

void handle_imu_msg(const sensor_msgs::Imu& imu_msg)
{
    ROS_INFO("IMU message sub: acc: %f,%f,%f; gyro: %f,%f,%f ", 
    imu_msg.linear_acceleration.x, imu_msg.linear_acceleration.y, imu_msg.linear_acceleration.z,
    imu_msg.angular_velocity.x,imu_msg.angular_velocity.y,imu_msg.angular_velocity.z);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "user_msg_client");
  ros::NodeHandle ins_alignment_node_handle;
  ros::Subscriber imu_msg_sub = ins_alignment_node_handle.subscribe("imu_msg", 1000, handle_imu_msg);
  ros::spin();
  return 0;
}