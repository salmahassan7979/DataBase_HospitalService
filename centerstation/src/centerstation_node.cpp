#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>
   #include <mysql/mysql.h>



int main(int argc, char* argv[])
{
MYSQL *connection;  
    MYSQL_RES *result;  
    MYSQL_ROW row; 
    std_msgs::String msg;
    std::stringstream ss;
	std_msgs::String RoomStatus,RoomStatus1,RoomCleaned,RoomSterilized;
    connection = mysql_init(NULL);
    connection = mysql_real_connect(connection, "localhost", "root", "3031997", "hospital", 0, NULL, 0);

ros::init(argc, argv, "centerstation_node");
ros::NodeHandle nh;
ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("centerstation", 10);
ros::Rate loop_rate(1);

while (ros::ok())
{


    if(mysql_query(connection, "SELECT RoomNo FROM room WHERE RoomStatus='Vacant' and RoomCleaned='Cleaned' and RoomSterilized='Awaiting'") ) 
    {  
        ROS_INFO("Query Error: %s", mysql_error(connection));  
        exit(1);  
    }  
    else  
    {  

        result = mysql_use_result(connection); 
     for(int i=0; i < 1000; ++i)  
        {
            
            row = mysql_fetch_row(result);  
            if(row <= 0)  
            {  
                break;  
            }  
           for(int j=0; j < mysql_num_fields(result); ++j)  

            {  
                ss << row[j] << " ";  
            }         			

		
        }
   
     
    }  
  msg.data = ss.str();
chatter_pub.publish(msg);

 	ROS_INFO("%s", msg.data.c_str());
mysql_free_result(result); 

	ros::spinOnce();
	loop_rate.sleep();
 
}
 
		
	
  return 0;
}
