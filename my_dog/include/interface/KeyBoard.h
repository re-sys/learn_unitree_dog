#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdio.h>
#include <interface/CmdPanel.h>
#include <message/LowlevelCmd.h>
#include <message/LowlevelState.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
class KeyBoard : public CmdPanel{
public:
    KeyBoard();
    ~KeyBoard();
    void sendRecv(const LowlevelCmd *cmd, LowlevelState *state);
private:
    static void* runKeyBoard(void *arg);
    void* run(void * arg);
    UserCommand checkCmd();
    void changeValue();

    pthread_t _tid;
    float sensitivityLeft = 0.01;
    float sensitivityRight = 0.01;
    // terminal setting: help change the input setting
    struct termios _oldt, _newt;
    // pair with select system
    // 
    fd_set set;
    int res;
    int ret;
    char _c;
};
#endif