
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <actionlib/server/simple_action_server.h>
#include <cameleon_controllers/RegulatePositionAction.h>

ros::Publisher chatter_pub;
float des_pos=0;
float p=0.1;
bool done = true;
typedef actionlib::SimpleActionServer<cameleon_controllers::RegulatePositionAction> Server;
float position;
cameleon_controllers::RegulatePositionResult result;
Server *server;

/*bool changePos(cameleon_controllers::RegulatePosition::Request  &req,
         cameleon_controllers::RegulatePosition::Response &res)
{
  
}*/


void chatterCallback(const std_msgs::Float32::ConstPtr& input)
{
  if(done == false){
  position = input->data;
  std_msgs::Float32 output;
  output.data = p*(des_pos-position);
  chatter_pub.publish(output);
  if(fabs(position-des_pos)<0.01){
     done = true;
  }
 }
 
}

void executeCB(const cameleon_controllers::RegulatePositionGoalConstPtr &goal, Server *serv)
{
  //ROS_INFO("callback");
  //ROS_INFO("request: pos=%f", (float)req.pos);
  done = false;
  des_pos = goal->des_pos;
  while(done == false){
    usleep(200000);
    if(server->isPreemptRequested()){
     done = true;
     server->setPreempted(result);
    }
  }
  //ROS_INFO("processing");
  
  //res.actual_pos = 
  ROS_INFO("done");
  //return true;
  std_msgs::Float32 output;
  output.data = 0;
  chatter_pub.publish(output);
  if(fabs(position-des_pos)<0.01){
     server->setSucceeded(result);
  }

  
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("flipperPosition", 1000, chatterCallback);
  chatter_pub = n.advertise<std_msgs::Float32>("flipperVelocity", 1000);
  server = new Server (n, "regulate", boost::bind(&executeCB, _1, server), false);
   server->start();
  //ros::ServiceServer service = n.advertiseService("regulate", changePos);
  ROS_INFO("Ready for position.");

  ros::spin();

  return 0;
}


