#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

#include "iceoryx_posh/popo/publisher.hpp"
#include "iceoryx_posh/runtime/posh_runtime.hpp"

#include <unistd.h>

#include <iostream>

#include "CustomPointCloud.h"

CustomPointCloud cp;

void pointcloudcallback(const sensor_msgs::PointCloud2ConstPtr &msg_ptr) {
  cp.width = msg_ptr->width;
  cp.height = msg_ptr->height;
  cp.is_bigendian = msg_ptr->is_bigendian;
  cp.header = msg_ptr->header;
  cp.row_step = msg_ptr->row_step;
  cp.data = msg_ptr->data;
  cp.is_dense = msg_ptr->is_dense;
  return;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sample_node1");
  ros::NodeHandle n;

  constexpr char APP_NAME[] = "points_raw_pub";
  iox::runtime::PoshRuntime::initRuntime(APP_NAME);
  iox::popo::Publisher<CustomPointCloud> p({"Radar", "FrontLeft", "Object"});
  ;

  auto sub = n.subscribe("/points_raw", 1, &pointcloudcallback);

  while (true) {
    ros::spinOnce();
    auto load = p.loan();
    if (!load.has_error()) {
      auto &sample = load.value();
      sample->is_bigendian = cp.is_bigendian;
      sample->width = cp.width;
      sample->height = cp.height;
      sample->data = cp.data;
      sample->header = cp.header;
      sample->row_step = cp.row_step;
      sample.publish();
      std::cout << "sending success" << std::endl;
    } else {
      auto error = load.get_error();
      std::cerr << "Unable to loan sample " << error << std::endl;
    }

    //    p.publishCopyOf(cp).or_else([](auto& error) {
    //          // Do something with error
    //          std::cerr << "Unable to loan sample, error: " << error <<
    //          std::endl;
    //        });
    sleep(0.1);
  }

  //! [API Usage #1]

  //! [iniox::popo::Publisher<sensor_msgs::PointCloud2> p({"Radar", "FrontLeft",
  //! "Object"});;itialize runtime]
}