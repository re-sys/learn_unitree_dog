#ifndef FSM_H
#define FSM_H
#include "FSM/FSMState.h"
#include "FSM/State_Passive.h"
#include "FSM/State_FixedStand.h"

struct FSMStateList{
    FSMState *invalid;
    State_Passive *passive;
    State_FixedStand*fixedStand;


void deletePtr(){
    delete invalid;
    delete passive;
    delete fixedStand;
}

};

class FSM{
public:
    FSM(CtrlComponents *ctrlComp);
    ~FSM();
    void initialize();
    void run();
private:
    FSMState* getNextState(FSMStateName stateName);
    bool checkSafty();
    CtrlComponents *_ctrlComp;
    FSMStateList _stateList;
    FSMState *_currentState;
    FSMState *_nextState;
    FSMStateName _currentStateName;
    FSMStateName _nextStateName;
    FSMMode _mode;
    long long _startTime;
    int count;

};
#endif // FSM_H