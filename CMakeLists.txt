cmake_minimum_required(VERSION 2.8.3)
project(nautonomous_msgs_authentication)


find_package(catkin REQUIRED COMPONENTS 
  roscpp 
  nautonomous_authentication_msgs
  message_generation
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
)


include_directories(
  include
  ${PROJECT_SOURCE_DIR}/include
  ${catkin_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "-std=c++11 -L/usr/local/lib ${CMAKE_CXX_FLAGS} -g")

add_executable(msg_authentication_node src/msg_authentication_node.cpp)

target_link_libraries(msg_authentication_node
  ${catkin_LIBRARIES}
  crypto
)