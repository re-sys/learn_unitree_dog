#include "FSM/State_FixedStand.h"

State_FixedStand::State_FixedStand(CtrlComponents *ctrlComp)
:FSMState(ctrlComp, FSMStateName::FIXEDSTAND, "FIXED_STAND"){
    _lowCmd = _ctrlComp->lowCmd;
    _lowState = _ctrlComp->lowState;
}

void State_FixedStand::enter(){
    _lowCmd->setRealStanceGain();
    _lowCmd->setZeroDq();
    _lowCmd->setZeroTau();
    for(int i=0; i<8; i++){
        _lowCmd->motorCmd[i].q = _lowState->motorState[i].q;
        _startPos[i] = _lowState->motorState[i].q;
    }
    _ctrlComp->setAllStance();
}

void State_FixedStand::run(){
    _percent += 1 / _duration;
    _percent = _percent > 1 ? 1 : _percent;
    for(int i=0; i<8; i++){
        _lowCmd->motorCmd[i].q = _startPos[i] + _percent * (_targetPos[i] - _startPos[i]);
    }
}

void State_FixedStand::exit(){
    _percent = 0;
}
FSMStateName State_FixedStand::checkChange(){
    if(_lowState->userCmd == UserCommand::EXIT){
        return FSMStateName::INVALID;
    }
    else if(_lowState->userCmd == UserCommand::FREE){
        return FSMStateName::FREESTAND;
    }
    else if(_lowState->userCmd == UserCommand::TROT){
        return FSMStateName::TROTTING;
    }
    else if(_lowState->userCmd == UserCommand::PASSIVE){
        return FSMStateName::PASSIVE;
    }
    else if(_lowState->userCmd == UserCommand::BALANCE){
        return FSMStateName::BALANCETEST;
    }
    else if(_lowState->userCmd == UserCommand::SWING){
        return FSMStateName::SWINGTEST;
    }
    else{
        return FSMStateName::FIXEDSTAND;
    }
}