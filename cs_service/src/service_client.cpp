#include "ros/ros.h"
#include <std_msgs/String.h>
#include <sstream>
   #include <mysql/mysql.h>


// ROS Default Header File
// SrvTutorial Service File Header (Automatically created after build)
#include "CS_service/CS_Srv.h"
#include <cstdlib>	



int main(int argc, char* argv[]){
MYSQL *connection;  
    MYSQL_RES *result;  
    MYSQL_ROW row; 
    std_msgs::String msg;
    std::stringstream ss;
ros::init(argc, argv, "service_client");		

  connection = mysql_init(NULL);
    connection = mysql_real_connect(connection, "localhost", "root", "3031997", "hospital", 0, NULL, 0);


ros::NodeHandle nh;

ros::ServiceClient cs_service_client =
nh.serviceClient<CS_service::CS_Srv>("cs_srv");

CS_service::CS_Srv srv;


 if(mysql_query(connection, "SELECT RoomNo FROM room WHERE RoomStatus='Vacant' and RoomCleaned='Cleaned' and RoomSterilized='Awaiting'") ) 
    {  
        ROS_INFO("Query Error: %s", mysql_error(connection));  
        exit(1);  
    }  
    else  
    {  

        result = mysql_use_result(connection); 
        for(int i=0; i < 100; ++i)  
        {
            
            row = mysql_fetch_row(result);  
            if(row <= 0)  
            {  
                break;  
            }  
           for(int j=0; j < mysql_num_fields(result); ++j)  

            {  
              srv.request.RoomNo = atoll(row[j]);
	if (cs_service_client.call(srv))

		{


ROS_INFO("send srv, srv.Request.RoomNo: %ld", (long int)srv.request.RoomNo);
ROS_INFO("receive srv, srv.Response.result: %ld", (long int)srv.response.result);

}
else
{
ROS_ERROR("Failed to call service cs_srv");
return 1;
}

            }  
		

		 
        }
mysql_free_result(result); 
}    




return 0;
}
