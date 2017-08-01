// ROS
#include <ros/ros.h>
// file stream to read secret key
#include <fstream>
// string stream used to concat strings
#include <stdio.h>
#include <sstream>
#include <string>
// sha encryption for generating MAC
#include <openssl/sha.h>
// service messages
#include <nautonomous_authentication_msgs/Authentication.h>
#include <nautonomous_authentication_msgs/Encryption.h>

// the secret key for this boat
std::string secret_key;

//callback for authentication service
bool authenticate(nautonomous_authentication_msgs::Authentication::Request &req, nautonomous_authentication_msgs::Authentication::Response &res);

//callback for generating MAC service
bool generate_mac(nautonomous_authentication_msgs::Encryption::Request &req, nautonomous_authentication_msgs::Encryption::Response &res);