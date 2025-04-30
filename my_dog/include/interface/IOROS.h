/*
THis class is for simulation
*/
#ifndef IOROS_H
#define IOROS_H
#include "interface/IOInterface.h"
#include "rclcpp.rclcpp.hpp"
#include "unitree_legged_msgs/msg/low_cmd.hpp"
#include "unitree_legged_msgs/msg/low_state.hpp"
#include "unitree_legged_msgs/msg/high_cmd.hpp"
class IOROS : public IOInterface,
public rclcpp::Node{
public:
    IOROS();
    ~IOROS();
    void sendRecv(const LowlevelCmd *cmd, LowlevelState *state);
private:
    void sendCmd(const LowlevelCmd *cmd);
    void recvState(LowlevelState *state);
    rclcpp::executors::MultiThreadedExecutor::SharedPtr executor;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    rclcpp::Publisher<unitree_legged_msgs::msg::MotorCmd>::SharedPtr servo_pub_[12];
    unitree_legged_msgs::LowCmd _lowCmd;
unitree_legged_msgs::LowState _lowState;
std::string _robot_name;

//repeated functions for multi-thread
void initRecv();
void initSend();

//Callback functions for ROS
void imuCallback(const sensor_msgs::Imu & msg);

void FRhipCallback(const unitree_legged_msgs::MotorState& msg);
void FRthighCallback(const unitree_legged_msgs::MotorState& msg);
void FRcalfCallback(const unitree_legged_msgs::MotorState& msg);

void FLhipCallback(const unitree_legged_msgs::MotorState& msg);
void FLthighCallback(const unitree_legged_msgs::MotorState& msg);
void FLcalfCallback(const unitree_legged_msgs::MotorState& msg);

void RRhipCallback(const unitree_legged_msgs::MotorState& msg);
void RRthighCallback(const unitree_legged_msgs::MotorState& msg);
void RRcalfCallback(const unitree_legged_msgs::MotorState& msg);

void RLhipCallback(const unitree_legged_msgs::MotorState& msg);
void RLthighCallback(const unitree_legged_msgs::MotorState& msg);
void RLcalfCallback(const unitree_legged_msgs::MotorState& msg);
};

#endif  // IOROS_H