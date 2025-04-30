#ifndef ENUMCLS_H
#define ENUMCLS_H

enum class UserCommand{
    EXIT,//exit
    TROT,//trot
    FIXED,//fixed_stand
    PASSIVE,//passive
    FREE,//freeStand
    BALANCE,//Balance_test
    SWING,//Swing_test
    STEP,//step_test
};
enum class FSMMode{
    NORMAL,
    CHANGE
};
enum class FSMStateName{
    INVALID,//EXIT, correspond to UserCommand::EXIT
    PASSIVE,//PASSIVE
    FIXEDSTAND,//FIXED
    FREESTAND,//FREE
    TROTTING,//TROT
    BALANCETEST,//BALANCE
    SWINGTEST,//SWING
    STEPTEST//STEP
};
enum class WaveStatus{
    STANCE_ALL,//all leg in stance
    SWING_ALL,//all leg in swing
    WAVE_ALL,//all leg in wave
};

#endif // ENUMCLS_H