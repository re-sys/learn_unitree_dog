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
};
#endif  // IOSDK_H