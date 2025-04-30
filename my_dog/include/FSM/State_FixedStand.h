#ifndef FIXEDSTAND_H
#define FIXEDSTAND_H
#include "FSM/FSMState.h"
class State_FixedStand : public FSMState{
public:
    State_FixedStand(CtrlComponents *ctrlComp);
    ~State_FixedStand();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();

private:
    float _targetPos[8] = {0.523,-0.523,0.523,-0.523,0.523,-0.523,0.523,-0.523};
    float _startPos[8];
    float _duration = 1000;   //steps
    float _percent = 0;       //%
};
#endif  // FIXEDSTAND_H