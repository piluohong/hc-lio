/***********************************************************
 *                                                         *
 * Copyright (c)                                           *
 *                                                         *
 * The Verifiable & Control-Theoretic Robotics (VECTR) Lab *
 * University of California, Los Angeles                   *
 *                                                         *
 * Authors: Kenny J. Chen, Ryan Nemiroff, Brett T. Lopez   *
 * Contact: {kennyjchen, ryguyn, btlopez}@ucla.edu         *
 *                                                         *
 ***********************************************************/

#include "dlio/dlio.h"
#include <std_srvs/Empty.h>
#include <string>
#include "octomap_msgs/Octomap.h"
#include "octomap/OcTree.h"
#include "octomap_msgs/conversions.h"

class dlio::MapNode {

public:

  MapNode(ros::NodeHandle node_handle);
  ~MapNode();

  void start();

private:

  void getParams();

  void publishTimer(const ros::TimerEvent& e);
  void callbackKeyframe(const sensor_msgs::PointCloud2ConstPtr& keyframe);
  void visualizeOctomap(pcl::PointCloud<PointType>::Ptr& global_cloud);
  bool serviceCallback(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);

  bool savePcd(direct_lidar_inertial_odometry::save_pcd::Request& req,
               direct_lidar_inertial_odometry::save_pcd::Response& res);

  ros::NodeHandle nh;
  ros::Timer publish_timer;

  ros::ServiceServer map_server;
  ros::Subscriber keyframe_sub;
  ros::Publisher map_pub;
  ros::Publisher octomap_pub;

  ros::ServiceServer save_pcd_srv;

  pcl::PointCloud<PointType>::Ptr dlio_map;
  pcl::VoxelGrid<PointType> voxelgrid;

  std::string odom_frame;

  double publish_freq_;
  double leaf_size_;

};
