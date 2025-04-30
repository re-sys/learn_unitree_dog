#ifndef CTRLCOMPONENTS_H
#define CTRLCOMPONENTS_H

#include "interface/IOInterface.h"
#include "message/LowlevelState.h"

struct CtrlComponents{
public:
    CtrlComponents(IOInterface *ioInter):ioInter(ioInter){
        lowCmd = new LowlevelCmd();
        lowState = new LowlevelState();
        phase = new Vec4;
    }
    ~CtrlComponents(){
        delete lowCmd;
        delete lowState;
        delete phase;
#ifdef COMPILE_DEBUG
        delete plot;
#endif
    }
    LowlevelCmd *lowCmd;
    LowlevelState *lowState;
    IOInterface *ioInter;
    // WaveGenerator *waveGen;
    // Estimator *estimator;
    // BalanceCtrl *balCtrl;
    Vec4 *phase;
    double dt;
    bool *running;
#ifdef COMPILE_DEBUG
    pyPlot *plot;   
#endif
    void sendRecv(){
        ioInter->sendRecv(lowCmd, lowState);
    }
    void setAllStance(){
        _wave_Status = WaveStatus::STANCE_ALL;
    }
    void setAllSwing(){
        _wave_Status = WaveStatus::SWING_ALL;
    }
    void setAllWave(){
        _wave_Status = WaveStatus::WAVE_ALL;
    }
    void genObj(){
#ifdef COMPILE_DEBUG
       plot = new pyPlot();

#endif
    }

    
private:
    WaveStatus _wave_Status;

};
#endif // CTRLCOMPONENTS_H