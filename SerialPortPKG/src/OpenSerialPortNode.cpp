#include <iostream>
#include <string>
#include <sstream>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "SerialPortPKG/SerialPort.h"
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include<stdio.h>      /*标准输入输出定义*/
#include<stdlib.h>     /*标准函数库定义*/
#include<unistd.h>     /*Unix 标准函数定义*/
#include<sys/types.h> 
#include<sys/stat.h>   
#include<fcntl.h>      /*文件控制定义*/
#include<termios.h>    /*PPSIX 终端控制定义*/
#include<errno.h>      /*错误号定义*/
#include<string.h>
#include<math.h>
using namespace std;


int main(int argc, char** argv)
{
	ros::init(argc, argv, "talker");
	ros::NodeHandle n;
	ros::Publisher imu_msg_pub = n.advertise<sensor_msgs::Imu>("imu_msg", 1000);

    int fd;                            //文件描述符
    int err;                           //返回调用函数的状态                      
    char rcv_buf[100];  
    long int main_counter = 0;
    double gyro_radian[3];
    fd = UART0_Open(fd); //打开串口，返回文件描述符
    do {
        err = UART0_Init(fd,460800,0,8,1,'N');
        printf("Set Port Exactly!\n");
        //LOG(INFO)<<"Set Port Exactly!";
    }while(FALSE == err || FALSE == fd);

    while (1) { //循环读取数据
      int read_out = UART0_Recv(fd, rcv_buf);
      if (read_out ==1) {
        //CorrectImuData(acce,gyro);
        // imu.delta_A = acce;
        // imu.delta_G = gyro;
        // InsUpdate.GetRudeCeb(Ceb,imu,earth);
        // attitude = Matrix2attitude(Ceb);
        gyro_radian[0] = gyro[0]*3.1415926/180;
        gyro_radian[1] = gyro[1]*3.1415926/180;
        gyro_radian[2] = gyro[2]*3.1415926/180;
        // gyro_degree[0] = degree2arc(gyro[0]);
        // gyro_degree[1] = degree2arc(gyro[1]);
        // gyro_degree[2] = degree2arc(gyro[2]);
        main_counter ++;
        cout<<main_counter<<" ";
        printf("mian  Acc:%-10f,%-10f,%-10f, Gyr:%-10f,%-10f,%-10f\n ",
        acce[0],acce[1],acce[2],gyro_radian[0],gyro_radian[1],gyro_radian[2]);

        sensor_msgs::Imu imu_data;
        imu_data.header.stamp = ros::Time::now();
        imu_data.header.frame_id = "base_link";
        //四元数位姿,所有数据设为固定值，可以自己写代码获取ＩＭＵ的数据，，然后进行传递
        // imu_data.orientation.x = 0;
        // imu_data.orientation.y = 0;
        // imu_data.orientation.z = 0;
        // imu_data.orientation.w = 0;
        //线加速度
        imu_data.linear_acceleration.x =  acce[0]; 
        imu_data.linear_acceleration.y =  acce[1];
        imu_data.linear_acceleration.z =  acce[2];
        //角速度
        imu_data.angular_velocity.x = gyro_radian[0]; 
        imu_data.angular_velocity.y = gyro_radian[1]; 
        imu_data.angular_velocity.z = gyro_radian[2]; 
        //发布IMU
        imu_msg_pub.publish(imu_data);
      }
    }  
    UART0_Close(fd); 
           

	// while(ros::ok())
	// {
	// 	std_msgs::String msg;
	// 	std::stringstream ss;
	// 	ss << "hello world " << count;
	// 	msg.data = ss.str();
	// 	ROS_INFO("%s", msg.data.c_str());
	// 	chatter_pub.publish(msg);
	// 	ros::spinOnce();
	// 	loop_rate.sleep();
	// 	count++;
	// }
	return 0;
}