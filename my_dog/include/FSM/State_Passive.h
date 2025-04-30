#ifndef STATE_PASSIVE_H
#define STATE_PASSIVE_H
#include "FSM/FSMState.h"
class State_Passive : public FSMState{
public:
    State_Passive(CtrlComponents *ctrlComp);
    ~State_Passive();
    void enter();
    void run();
    void exit();
    FSMStateName checkChange();

};
#endif // STATE_PASSIVE_H