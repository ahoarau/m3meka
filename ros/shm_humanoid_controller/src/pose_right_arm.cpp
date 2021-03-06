#include <iostream>

#include <ros/ros.h>

#include "m3ctrl_msgs/M3JointCmd.h"
#include "m3/hardware/joint_mode_ros.pb.h"
#include "m3/robots/chain_name.h"
#include "m3/hardware/smoothing_mode.pb.h"

#define NDOF_ARM 7

class HumanoidDriver
{
private:
  //! The node handle we'll be using
  ros::NodeHandle nh_;
  //! We will be publishing to the "/base_controller/command" topic to issue commands
  ros::Publisher cmd_pub_;

public:
  //! ROS node initialization
  HumanoidDriver(ros::NodeHandle &nh)
  {
    nh_ = nh;
    //set up the publisher for the cmd_vel topic
    cmd_pub_ = nh_.advertise<m3ctrl_msgs::M3JointCmd>("/humanoid_command", 1);
  }

  //! Loop forever while sending drive commands based on keyboard input
  bool driveKeyboard()
  {
    char cmd[50];
     m3ctrl_msgs::M3JointCmd humanoid_cmd;
     
    humanoid_cmd.chain.resize(NDOF_ARM);
    humanoid_cmd.stiffness.resize(NDOF_ARM);
    humanoid_cmd.position.resize(NDOF_ARM);
    humanoid_cmd.velocity.resize(NDOF_ARM);
    humanoid_cmd.effort.resize(NDOF_ARM);
    humanoid_cmd.control_mode.resize(NDOF_ARM);
    humanoid_cmd.smoothing_mode.resize(NDOF_ARM);
    humanoid_cmd.chain_idx.resize(NDOF_ARM);
     
    
    
    double stiffness = 1.0;
    
    
    std::cout << "Posing right arm demo.\n";
    std::cout << "Commanding right arm in mode JOINT_MODE_ROS_POSE.\n";
    std::cout << "Press any key to move to start.\n";
    std::cout << "Stiffness now:" << stiffness << "\n\n";
    
    std::cin.getline(cmd, 50);
    
    
    humanoid_cmd.header.stamp = ros::Time::now();
    humanoid_cmd.header.frame_id = "humanoid_cmd";
    
  
    for (int i = 0; i < NDOF_ARM; i++)
    {
      humanoid_cmd.chain[i] = (unsigned char)RIGHT_ARM; // chain name: RIGHT_ARM, HEAD, RIGHT_HAND, LEFT_ARM, or LEFT_HAND    
      humanoid_cmd.chain_idx[i] = i;
      humanoid_cmd.control_mode[i] = (unsigned char)JOINT_MODE_ROS_POSE; //Compliant position mode      
      humanoid_cmd.smoothing_mode[i] = (unsigned char)SMOOTHING_MODE_SLEW; //Smooth trajectory
      //humanoid_cmd.smoothing_mode[0] = (unsigned char)SMOOTHING_MODE_MIN_JERK; //Use for HEAD
      humanoid_cmd.velocity[i] = 1.0; //Rad/s
      humanoid_cmd.stiffness[i] = stiffness; //0-1.0
      humanoid_cmd.effort[i] = 0.0;
      humanoid_cmd.position[i] = 0.0; //Desired position (Rad)      
    }
    
    cmd_pub_.publish(humanoid_cmd);
  
    
    
    std::cout << "Type a command and then press enter.  "
      "Use '+' to increase stiffness by 0.05, '-' to decrease stiffness by -0.05, or"
      "'.' to exit.\n";

    while(nh_.ok()){

      std::cin.getline(cmd, 50);
      if(cmd[0]!='+' && cmd[0]!='-' && cmd[0]!='z' && cmd[0]!='.')
      {
        std::cout << "unknown command:" << cmd << "\n";
        continue;
      }
      
      double stiffness_delta = 0.05;
      
      //move forward
      if(cmd[0]=='+'){        
	stiffness += stiffness_delta;
      } 
      //turn left (yaw) and drive forward at the same time
      else if(cmd[0]=='-'){        
	stiffness -= stiffness_delta;
      }                         
      //quit
      else if(cmd[0]=='.'){
        break;
      }
      
      if (stiffness > 1.0)
	stiffness = 1.0;
      if (stiffness < 0)
	stiffness = 0.0;
      
      std::cout << "Stiffness now:" << stiffness << "\n\n";
      
      for (int i = 0; i < NDOF_ARM; i++)
      {      
	  humanoid_cmd.stiffness[i] = stiffness; //0-1.0      
      }
            
      humanoid_cmd.header.stamp = ros::Time::now();
      //publish the assembled command
      cmd_pub_.publish(humanoid_cmd);
    }
    return true;
  }

};

int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "robot_driver");
  ros::NodeHandle nh;

  HumanoidDriver driver(nh);
  driver.driveKeyboard();
}
