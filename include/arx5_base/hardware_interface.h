#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

#include "arx5_base/can.h"

#include <vector>
#include <string>
#include <thread>
#include <memory>

class HardwareInterface
{
public:
  HardwareInterface(std::string init_hardware_type = "real", std::string init_control_mode = "position", std::string init_can_port="can0");
  ~HardwareInterface() = default;

  // 获取关节角度状态
  std::vector<double> getJointAngles();
  // 获取关节力矩状态
  std::vector<double> getJointTorques();
  // 控制关节角度
  void setODJointAngles(std::vector<double> set_joint_angles);
  // 控制关节力矩
  void setODJointTorques(std::vector<double> set_joint_torques);
  // 控制末端夹爪力矩
  void setGripperTorque(float torque);
  // 标定电机
  void calibrateAll();

private:
  // 硬件类型（fake/real/sim)
  std::string hardware_type;
  // 控制模式（position/torque)
  std::string control_mode;
  // 关节角度状态
  std::vector<double> joint_angle_states = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  // 关节力矩状态
  std::vector<double> joint_torque_states = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  // 关节角度指令
  std::vector<double> joint_angles = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  // 关节力矩指令
  std::vector<double> joint_torques = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
  // Gripper力矩指令
  float _gripper_torque = 0.0;
  // CAN通信接口
  std::shared_ptr<ARX5_CAN> can_interface;
  // 电机ID
  int motor_ids[6] = { 1, 2, 4, 5, 6, 7 };
  // 创建独立线程
  pthread_t thread_1;
  // 线程函数
  void updateHardware();
};

#endif