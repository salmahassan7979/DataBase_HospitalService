cmake_minimum_required(VERSION 2.8.3)
project(CS_service)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake-modules)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
)

add_service_files(
FILES 
CS_Srv.srv
)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(

)
find_package(MySqlClient REQUIRED)
add_definitions(${MYSQL_DEFINITIONS})
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
include_directories(${MYSQL_INCLUDE_DIRS})
add_executable(service_server src/service_server.cpp)
add_dependencies(service_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service_server ${catkin_LIBRARIES}
${MYSQL_LIBRARIES})

## Build option for the "service_client" node.
add_executable(service_client src/service_client.cpp)
add_dependencies(service_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service_client ${catkin_LIBRARIES}

${MYSQL_LIBRARIES})
