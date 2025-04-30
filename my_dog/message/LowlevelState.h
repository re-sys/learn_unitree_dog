#ifndef MotorState_H
#define MotorState_H

#include "common/mathTypes.h"
#include "common/mathTools.h"
#include "common/enumClass.h"
#include "interface/CmdPanel.h"

struct MotorState{
    unsigned int mode;
    float q;
    float dq;
    float ddq;
    float tauEst;

    MotorState(){
        mode = 0;
        q = 0.0;
        dq = 0.0;
        ddq = 0.0;
        tauEst = 0.0;
    }
};
// IMU is not used now
struct IMU
{
    float quaternion[4];    // w, x, y, z
    float gyroscope[3];
    float accelerometer[3];

    IMU(){
        for(int i = 0; i < 3; i++){
            quaternion[i] = 0;
            gyroscope[i] = 0;
            accelerometer[i] = 0;
        }
        quaternion[3] = 0;
    }

    RotMat getRotMat(){
        Quat quat;
        quat << quaternion[0], quaternion[1], quaternion[2], quaternion[3];
        return quatToRotMat(quat);
    }

    Vec3 getAcc(){
        Vec3 acc;
        acc << accelerometer[0], accelerometer[1], accelerometer[2];
        return acc;
    }

    Vec3 getGyro(){
        Vec3 gyro;
        gyro << gyroscope[0], gyroscope[1], gyroscope[2];
        return gyro;
    }

    Quat getQuat(){
        Quat q;
        q << quaternion[0], quaternion[1], quaternion[2], quaternion[3];
        return q;
    }
};
struct LowlevelState{
    IMU imu;
    MotorState motorState[8];
    UserCommand userCmd;//stop, trot, etc
    UserValue userValue;//real penal in the stick

    Vec24 getQd(){
        Vec24 qdLegs;
        for(int i(0); i < 4; ++i){
            qdLegs.col(i)(0) = motorState[2 * i].q;
            qdLegs.col(i)(1) = motorState[2 * i + 1].q;
        }
        return qdLegs;
    }
    RotMat getRotMat(){
        return imu.getRotMat();
    }

    Vec3 getAcc(){
        return imu.getAcc();
    }

    Vec3 getGyro(){
        return imu.getGyro();
    }

    Vec3 getAccGlobal(){
        return getRotMat() * getAcc();
    }

    Vec3 getGyroGlobal(){
        return getRotMat() * getGyro();
    }

    double getYaw(){
        return rotMatToRPY(getRotMat())(2);
    }

    double getDYaw(){
        return getGyroGlobal()(2);
    }
    void setQ(Vec12 q){
        for(int i(0); i<12; ++i){
            motorState[i].q = q(i);
        }
    }

};

#endif // MotorState_H