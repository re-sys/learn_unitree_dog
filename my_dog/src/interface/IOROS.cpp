// 取消注释COMPILE_WITH_ROS宏
// #ifdef COMPILE_WITH_ROS

#include "interface/IOROS.h"
#include "interface/KeyBoard.h"
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <iostream>
#include <unistd.h>
#include <csignal>

// 修改节点声明方式
std::shared_ptr<rclcpp::Node> node;

void RosShutDown(int sig){
    RCLCPP_INFO(node->get_logger(), "ROS interface shutting down!");
    rclcpp::shutdown();
}

IOROS::IOROS():IOInterface(){
    // 初始化ROS2节点
    node = std::make_shared<rclcpp::Node>("unitree_controller");
    std::cout << "The control interface for ROS2 Gazebo simulation" << std::endl;
    
    // 参数获取方式修改
    node->declare_parameter("robot_name", "default");
    _robot_name = node->get_parameter("robot_name").as_string();
    std::cout << "robot_name: " << _robot_name << std::endl;

    // 初始化执行器
    executor = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
    executor->add_node(node);

    // 启动订阅/发布
    initRecv();
    initSend();

    // 信号处理
    signal(SIGINT, RosShutDown);
    cmdPanel = new KeyBoard();
}

// 修改发布者初始化（示例）
void IOROS::initSend(){
    auto qos = rclcpp::QoS(1);
    _servo_pub[0] = node->create_publisher<unitree_legged_msgs::msg::MotorCmd>(
        "/" + _robot_name + "_gazebo/FR_hip_controller/command", qos);
    // 其他发布者类似修改...
}

// 修改订阅者初始化（示例）
void IOROS::initRecv(){
    auto qos = rclcpp::QoS(1);
    _imu_sub = node->create_subscription<sensor_msgs::msg::Imu>(
        "/trunk_imu", qos,
        std::bind(&IOROS::imuCallback, this, std::placeholders::_1));
    // 其他订阅者类似修改...
}

// 修改回调函数参数（示例）
void IOROS::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
    _lowState.imu.quaternion[0] = msg->orientation.w;
    // 其余IMU数据处理保持不变...
}

// 修改消息发布方式
void IOROS::sendCmd(const LowlevelCmd *lowCmd){
    auto motor_cmd = std::make_shared<unitree_legged_msgs::msg::MotorCmd>();
    // 填充消息内容...
    _servo_pub[0]->publish(*motor_cmd);
    executor->spin_some();
}
#endif  // COMPILE_WITH_ROS