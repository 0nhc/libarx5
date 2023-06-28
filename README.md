# libarx5

## Warning!!!
Remember to change the 3 file paths in teaching.cpp and kinematics_dynamics.cpp!!!
Remember to change the 3 file paths in teaching.cpp and kinematics_dynamics.cpp!!!
Remember to change the 3 file paths in teaching.cpp and kinematics_dynamics.cpp!!!

## Dependencies

```sh
# Ubuntu 20.04
sudo apt-get install liborocos-kdl1.4 libkdl-parser-dev can-utils net-tools

# Ubuntu 22.04
sudo apt-get install liborocos-kdl-dev libkdl-parser-dev can-utils net-tools
```

## Open USB2CAN

```sh
sudo ip link set can0 type can bitrate 1000000
sudo ifconfig can0 up
```

## Compile This Project
```sh
cd libarx5
mkdir build
cd build
cmake ..
make
```

## Run Demos
```sh
cd libarx5/build
./gravityOff # 重力补偿模式
```

## Software Architecture
![architecture](docs/architecture.png)

## TODO List

* HardwareInterface ✓
* Rate ✓
* JointTrajectories ✓
* Kinematics ✓ Dynamics ✓
* StateEstimation ✓ (不是Control中的状态估计，而是类似“态势评估”的概念。)
* Teaching ✓
* Calibration ✗
* Teleop ✗
* Initialization ✗
* UI ✗
