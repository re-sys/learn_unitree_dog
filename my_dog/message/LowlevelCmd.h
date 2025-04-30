/*
This is just for lowlevel control data type
*/
#ifndef MotorCommand_H
#define MotorCommand_H

#include "common/mathTypes.h"
#include "common/mathTools.h"

struct MotorCmd{
    unsigned int mode;
    float q;
    float dq;
    float tau;
    float Kp;
    float Kd;

    MotorCmd(){
        mode = 0;
        q = 0;
        dq = 0;
        tau = 0;
        Kp = 0; 
        Kd = 0;
    }
    
};
struct LowlevelCmd{
    MotorCmd motorCmd[8];

    void setQ(Vec8 q){
        for(int i(0); i<8; ++i){
            motorCmd[i].q = q(i);
        }
    }
    void setQ(int legID, Vec2 qi){
        motorCmd[legID * 2].q = qi(0);
        motorCmd[legID * 2 + 1].q = qi(1);
    }
    void setDq(Vec8 dq){
        for(int i(0); i<8; ++i){
            motorCmd[i].dq = dq(i);
        }
    }
    void setDq(int legID, Vec2 dqi){
        motorCmd[legID * 2].dq = dqi(0);    
        motorCmd[legID * 2 + 1].dq = dqi(1);
    }
    void setTau(Vec8 tau, Vec2 torqueLimit = Vec2(-50,50)){
        for(int i(0); i<8; ++i){
            motorCmd[i].tau = saturation(tau(i), torqueLimit);
        }
    }
    void setZeroDq(int legID){
        motorCmd[legID * 2].dq = 0;
        motorCmd[legID * 2 + 1].dq = 0;
    }
    void setZeroTau(int legID){
        motorCmd[legID * 2].tau = 0;
        motorCmd[legID * 2 + 1].tau = 0;
    }
    void setZeroTau(){
        for(int i(0); i<4; ++i){
            setZeroTau(i);
        }
    }
    void setSimStanceGain(int legID){
        motorCmd[legID * 2].mode = 10;
        motorCmd[legID * 2 + 1].mode = 10;
        motorCmd[legID * 2].Kp = 1000;
        motorCmd[legID * 2 + 1].Kp = 1000;
        motorCmd[legID * 2].Kd = 10;
        motorCmd[legID * 2 + 1].Kd = 10;
    }
    void setSimStanceGain(){
        for(int i(0); i<4; ++i){
            setSimStanceGain(i);
        }
    }
    void setRealStanceGain(int legID){
        motorCmd[legID * 2].mode = 10;
        motorCmd[legID * 2 + 1].mode = 10;
        motorCmd[legID * 2].Kp = 500;
        motorCmd[legID * 2 + 1].Kp = 500;
        motorCmd[legID * 2].Kd = 10;
        motorCmd[legID * 2 + 1].Kd = 10;
    }
    void setRealStanceGain(){
        for(int i(0); i<4; ++i){
            setRealStanceGain(i);
        }
    }
    void setZeroGain(int legID){
        motorCmd[legID * 2].mode = 10;
        motorCmd[legID * 2 + 1].mode = 10;
        motorCmd[legID * 2].Kp = 0;
        motorCmd[legID * 2 + 1].Kp = 0;
        motorCmd[legID * 2].Kd = 0;
        motorCmd[legID * 2 + 1].Kd = 0;
    }
    void setZeroGain(){
        for(int i(0); i<4; ++i){
            setZeroGain(i);
        }
    }
    void setSwingGain(int legID){
        motorCmd[legID * 2].mode = 10;
        motorCmd[legID * 2 + 1].mode = 10;
        motorCmd[legID * 2].Kp = 500;
        motorCmd[legID * 2 + 1].Kp = 500;
        motorCmd[legID * 2].Kd = 10;
        motorCmd[legID * 2 + 1].Kd = 10;
    }
    void setStableGain(int legID){
        motorCmd[legID * 2].mode = 10;
        motorCmd[legID * 2 + 1].mode = 10;
        motorCmd[legID * 2].Kp = 500;
        motorCmd[legID * 2 + 1].Kp = 500;
        motorCmd[legID * 2].Kd = 10;
        motorCmd[legID * 2 + 1].Kd = 10;
    }
    void setStableGain(){
        for(int i(0); i<4; ++i){
            setStableGain(i);
        }
    }

};

#endif // MotorCommand_H