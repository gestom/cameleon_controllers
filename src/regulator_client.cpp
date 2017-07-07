#include "ros/ros.h"
#include "beginner_tutorials/RegulatePosition.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "regulator_client");
  if (argc != 2)
  {
    ROS_INFO("usage: regulator_client pos");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<beginner_tutorials::RegulatePosition>("regulate");
  beginner_tutorials::RegulatePosition srv;
  srv.request.pos = atof(argv[1]);
  if (client.call(srv))
  {
    ROS_INFO("Done: %s", srv.response.result);
  }
  else
  {
    ROS_ERROR("Failed to call service listener");
    return 1;
  }

  return 0;
}
