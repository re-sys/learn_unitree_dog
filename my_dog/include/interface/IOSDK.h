/*
This class is for real robot
*/
#ifndef IOSDK_H
#define IOSDK_H
#include "interface/IOInterface.h"
class IOSDK : public IOInterface{
public:
    IOSDK();
    ~IOSDK();
    void sendRecv(const LowlevelCmd *cmd, LowlevelState *state);
private:
    SDK::UDP _udp;
    SDK::LowCmd _lowCmd = {0};//initialize to zero
    SDK::LowState _lowState = {0};
    SDK::safe _safe;//关节保护机制，异常状态监测，安全策略应用。
    
};
#endif  // IOSDK_H