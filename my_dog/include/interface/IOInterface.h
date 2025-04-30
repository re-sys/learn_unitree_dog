//核心思想使用继承，针对仿真模型和真实机器人有两类接口
//两个派生类IOROS，IOSDK使用不同方法完成相同的任务
//都继承收发函数，sendRecv
#ifndef IOINTERFACE_H
#define IOINTERFACE_H
#include "message/LowlevelCmd.h"
#include "message/LowlevelState.h"
class IOInterface{
public:
    IOInterface(){}
    ~IOInterface(){}
    virtual void sendRecv(const LowlevelCmd *cmd, LowlevelState *state) = 0;
};

#endif  