cmake_minimum_required(VERSION 2.8.3)
project(cameleon_controllers)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  actionlib
  actionlib_msgs
)

find_package(Boost REQUIRED COMPONENTS system)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   Pos.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   RegulatePosition.srv
 )

## Generate actions in the 'action' folder
 add_action_files(
   FILES
   RegulatePosition.action
 )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
   actionlib_msgs
 )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  #INCLUDE_DIRS include
  #LIBRARIES cameleon_controllers
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime actionlib_msgs actionlib
  #DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS}
)


add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener ${catkin_EXPORTED_TARGETS})

add_executable(regulator_client src/regulator_client.cpp)
target_link_libraries(regulator_client ${catkin_LIBRARIES})
add_dependencies(regulator_client cameleon_controllers_gencpp)





