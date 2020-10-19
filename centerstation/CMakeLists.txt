cmake_minimum_required(VERSION 2.8.3)
project(centerstation)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake-modules)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
 std_msgs
)
find_package(MySqlClient REQUIRED)
add_definitions(${MYSQL_DEFINITIONS})
include_directories( ${catkin_INCLUDE_DIRS})
include_directories(${MYSQL_INCLUDE_DIRS})
add_executable(${PROJECT_NAME}_node src/centerstation_node.cpp)
target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
   ${MYSQL_LIBRARIES}
)

