/*
THis class is for simulation
*/
#ifndef IOROS_H
#define IOROS_H
#include "interface/IOInterface.h"

class IOROS : public IOInterface{
public:
    IOROS();
    ~IOROS();
    void sendRecv(const LowlevelCmd *cmd, LowlevelState *state);
private:
    void sendCmd(const LowlevelCmd *cmd);
    void recvState(LowlevelState *state);
};

#endif  // IOROS_H