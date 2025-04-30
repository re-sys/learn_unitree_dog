#ifndef FSMSTATE_H
#define FSMSTATE_H
#include "control/CtrlComponents.h"
#include "common/enumClass.h"
#include "message/LowlevelCmd.h"
#include "message/LowlevelState.h"
class FSMState{
public:
    FSMState(CtrlComponents *ctrlComp, FSMStateName stateName, std::string stateNameString):
        _ctrlComp(ctrlComp), _stateName(stateName), _stateNameString(stateNameString){
        _lowCmd = _ctrlComp->lowCmd;
        _lowState = _ctrlComp->lowState;
    };
    virtual void enter() = 0;
    virtual void run() = 0;
    virtual void exit() = 0;
    virtual FSMStateName checkTransition() {return FSMStateName::INVALID;}
    
    FSMStateName _stateName;
    std::string _stateNameString;
protected:
    CtrlComponents *_ctrlComp;
    FSMStateName _nextStateName;

    LowlevelCmd *_lowCmd;
    LowlevelState *_lowState;
    UserValue _userValue;
    
};
#endif // FSMSTATE_H