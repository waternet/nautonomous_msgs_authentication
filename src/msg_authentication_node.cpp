#include <nautonomous_msgs_authentication/msg_authentication_node.h>

using namespace std;

bool authenticate(nautonomous_authentication_msgs::Authentication::Request &req, 
                  nautonomous_authentication_msgs::Authentication::Response &res)
{
    stringstream ss;
    ss << secret_key << req.token;
    string local_hash = ss.str();

    // check the request
    unsigned char sha512_hash[SHA512_DIGEST_LENGTH];
    SHA512((unsigned char *)local_hash.c_str(), local_hash.length(), sha512_hash);

    // convert to a hex string to compare
    char hex[SHA512_DIGEST_LENGTH * 2];
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        sprintf(&hex[i * 2], "%02x", sha512_hash[i]);

    // return result of comparison, true or false
    res.authenticated = (strcmp(hex, req.mac.c_str()) == 0);

    return true;
}

//callback for generating MAC service
bool generate_mac(nautonomous_authentication_msgs::Encryption::Request &req, 
                  nautonomous_authentication_msgs::Encryption::Response &res)
{
    stringstream ss;

    // combine secret key and token in a single string
    ss << secret_key << req.token;
    string token = ss.str();


    // copied from mac_authentication source code, for reference check http://docs.ros.org/kinetic/api/rosauth/html/ros__mac__authentication_8cpp_source.html 
    unsigned char sha512_hash[SHA512_DIGEST_LENGTH];
    SHA512((unsigned char *)token.c_str(), token.length(), sha512_hash);

    char hex[SHA512_DIGEST_LENGTH * 2];
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        sprintf(&hex[i * 2], "%02x", sha512_hash[i]);
    
    //convert the hex char array to a string
    string mac(hex);

    //response contains the generated mac
    res.mac = mac;

    return true;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "msg_authentication_node");

    ros::NodeHandle node;

    string file;
    
    ros::NodeHandle priv_node("~");
    priv_node.param<std::string>("secret_file", file, "");

     // Set secret string
    ifstream f;
    f.open(file.c_str(), ifstream::in);
    if (f.is_open())
    {
        // should be a 1 line file with the string
        getline(f, secret_key);
        f.close();
    }

    ros::ServiceServer authenticationService = node.advertiseService("msg_auth", authenticate);
    ros::ServiceServer generateMACService = node.advertiseService("mac_gen", generate_mac);

    ros::spin();

    return 0;

}