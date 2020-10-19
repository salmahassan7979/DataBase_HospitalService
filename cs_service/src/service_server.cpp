#include "ros/ros.h"	
// SrvTutorial Service File Header (Automatically created after build)
#include "CS_service/CS_Srv.h"



bool calculation(CS_service::CS_Srv::Request &req,
CS_service::CS_Srv::Response &res)
{
// The service name is 'ros_tutorial_srv' and it will call 'calculation' function
// upon the service request.
res.result = 1;
ROS_INFO("request: x=%ld", (long int)req.RoomNo);
ROS_INFO("sending back response: %ld", (long int)res.result);
return true;
}


int main(int argc, char* argv[]){


ros::init(argc, argv, "service_server"); 	 // Initializes Node Name
ros::NodeHandle nh; 	 // Node handle declaration
// Declare service server 'ros_tutorials_service_server'
// using the 'SrvTutorial' service file in the 'ros_tutorials_service' package.
// The service name is 'ros_tutorial_srv' and it will call 'calculation' function
// upon the service request.
ros::ServiceServer cs_service_server = nh.advertiseService("cs_srv",
calculation);
ROS_INFO("ready srv server!");
ros::spin();
					
// Wait for the service request
return 0;
}
