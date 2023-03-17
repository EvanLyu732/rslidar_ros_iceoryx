cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(iceoryx_pointcloud)

set(CMAKE_CXX_FLAGS "-O1 -Wall -g")
set(CMAKE_CXX_STANDARD 17)

#Ros#
find_package(iceoryx_posh CONFIG REQUIRED)
find_package(iceoryx_hoofs CONFIG REQUIRED)
#find_package(catkin REQUIRED COMPONENTS roscpp)
find_package(roscpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cpptoml REQUIRED)
find_package(std_msgs REQUIRED)


get_target_property(ICEORYX_CXX_STANDARD iceoryx_posh::iceoryx_posh CXX_STANDARD)

include(IceoryxPlatform)
include(IceoryxPackageHelper)

add_executable(pointcloud_pub_node
        pub_node.cpp
        )

add_executable(pointcloud_sub_node
        sub_node.cpp
        )

#target_include_directories(pointcloud_pub_node PRIVATE
#)

target_include_directories(pointcloud_pub_node PRIVATE
        ${roscpp_INCLUDE_DIRS}
        ${sensor_msgs_INCLUDE_DIRS}
        ${std_msgs_INCLUDE_DIRS}
        )

target_include_directories(pointcloud_sub_node PRIVATE
        ${roscpp_INCLUDE_DIRS}
        ${sensor_msgs_INCLUDE_DIRS}
        ${std_msgs_INCLUDE_DIRS}
        )

target_link_libraries(pointcloud_pub_node PRIVATE
        ${roscpp_LIBRARIES}
        ${cpptoml_LIBRARIES}
        iceoryx_posh::iceoryx_posh_roudi
        iceoryx_posh::iceoryx_posh_config
        )

target_link_libraries(pointcloud_sub_node PRIVATE
        ${roscpp_LIBRARIES}
        ${cpptoml_LIBRARIES}
        iceoryx_posh::iceoryx_posh_roudi
        iceoryx_posh::iceoryx_posh_config
        )
