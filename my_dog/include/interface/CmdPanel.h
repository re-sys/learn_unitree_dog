#ifndef CMDPANEL_H
#define CMDPANEL_H

#include "common/enumClass.h"
#include <pthread.h>

#ifdef COMPILE_WITH_REAL_ROBOT
#include "xiaomiSDK/XiaomiSDK.h"
#endif

struct UserValue{
    float lx;
    float ly;
    float rx;
    float ry;
    float L2;
    UserValue(){
        setZero();
    }
    void setZero(){
        lx = 0;
        ly = 0;
        rx = 0;
        ry = 0;
        L2 = 0;
    }
};
class CmdPanel{
public:
    CmdPanel(){}
    virtual ~CmdPanel(){}
    UserCommand getUserCmd(){return userCmd;}
    UserValue getUserValue(){return userValue;}
    void setPassive(){userCmd = UserCommand::PASSIVE;}
    void setZero(){userValue.setZero();}
    #ifdef COMPILE_WITH_REAL_ROBOT
    virtual void reaceiveHandle(SDK::state *lowstate);
    #endif
    protected:
    virtual void* run(void *arg){return NULL;}
    UserCommand userCmd;
    UserValue userValue;

}

#endif