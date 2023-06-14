#include <arx5_base/hardware_interface.h>
#include <arx5_base/trajectories.h>
#include <arx5_base/kinematics_dynamics.h>
#include <arx5_base/planner.h>
#include <arx5_base/state_estimation.h>

#include <iostream>

int main()
{
  HardwareInterface hardware_interface("fake", "position");
  Trajectories trajectories;
  KinematicsDynamics kinematics_dynamics;
  Planner planner;
  StateEstimation state_estimation;

  std::vector<double> target_pose = { -1.0, 0.0, 0.1, 0.0, 0.0, 0.0 };
  std::vector<double> joint_states = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  std::vector<double> joint_command = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  std::vector<double> temp_joint_command;
  std::vector<double> pose_states = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  trajectories.update(planner.getTraj(target_pose));
  while (trajectories.size() != 1)
  {
    temp_joint_command = trajectories.front(); // 此时储存的是pose
    trajectories.pop();
    temp_joint_command = kinematics_dynamics.solveIK(temp_joint_command); // 此时储存的是关节角度
    if (!state_estimation.ifDanger(temp_joint_command))
    {
      std::cout<<"Valid Command"<<std::endl;
      joint_command = temp_joint_command;
      hardware_interface.setJointAngles(joint_command);
    }
    else
    {
      std::cout<<"Invalid Command"<<std::endl;
      break;
    }

    joint_states = hardware_interface.getJointStates();
    kinematics_dynamics.updateJointStates(joint_states);
    pose_states = kinematics_dynamics.solveFK(joint_states);
    planner.updatePoseStates(pose_states);

    std::cout << "joint_command: " << joint_command[0] << ", " << joint_command[1] << ", " << joint_command[2] << ", "
              << joint_command[3] << ", " << joint_command[4] << ", " << joint_command[5] << std::endl;
    std::cout << "pose_states: " << pose_states[0] << ", " << pose_states[1] << ", " << pose_states[2] << ", "
              << pose_states[3] << ", " << pose_states[4] << ", " << pose_states[5] << std::endl;
    std::cout<<std::endl;
  }

  return 0;
}