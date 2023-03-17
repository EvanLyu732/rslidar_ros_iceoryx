#pragma once

#include "std_msgs/Header.h"

struct CustomPointCloud {
  CustomPointCloud() noexcept {}
  CustomPointCloud(std_msgs::Header header, uint32_t height, uint32_t width,
                   uint32_t point_step, uint32_t row_step,
                   std::vector<unsigned char> data, uint8_t is_dense) noexcept
      : header(header), height(height), width(width),
        is_bigendian(is_bigendian), point_step(point_step), row_step(row_step),
        data(data), is_dense(is_dense) {}

  std_msgs::Header header;
  uint32_t height;
  uint32_t width;
  uint8_t is_bigendian;
  uint32_t point_step;
  uint32_t row_step;
  std::vector<unsigned char> data;
  uint8_t is_dense;
};
