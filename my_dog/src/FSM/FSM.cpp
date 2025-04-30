#include "FSM/FSM.h"
FSM::FSM(CtrlComponents *ctrlComp)
:_ctrlComp(ctrlComp){
    _stateList.invalid = nullptr;
    _stateList.passive = new State_Passive(ctrlComp);
    _stateList.fixedStand = new State_FixedStand(ctrlComp);

    initialize();
}

FSM::~FSM(){
    _stateList.deletePtr();
}

void FSM::initialize(){
    _currentState = _stateList.passive;
    _currentState->enter();
    _nextState = _currentState;
    _mode = FSMMode::NORMAL;
}

void FSM::run(){
    _startTime = getSystemTime();
    _ctrlComp->sendRecv();
    _ctrlComp->runWaveGen();
    _currentState->run();
    if(!checkSafty()){
        _ctrlComp->ioInter->setPassive();
    }
    if(_mode==FSMMode::NORMAL){
        _currentState->run();
        _nextState = _currentState->checkChange();
        if(_nextState!=_currentState){
            _currentState->exit();
            _currentState = _nextState;
            _currentState->enter();
        }
    }
    _nextState = _currentState->checkChange();
}