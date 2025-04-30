#include "interface/KeyBoard.h"
#include <iostream>

KeyBoard::KeyBoard(){
    userCmd = UserCommand::EXIT;
    userValue.setZero();
    // get original termial setting
    // tc: terminal control
    tcgetattr( fileno(stdin), &_oldt);
    _newt = _oldt;
    // close input canonical mode: no enter directly input
    // close echo mode: no echo input
    _newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( fileno(stdin), TCSANOW, &_newt);
    // run funciton and pass this pointer
    pthread_create(&_tid,NULL,runKeyBoard,(void*)this);
}

KeyBoard::~KeyBoard(){
    // send cancel signal to thread
    pthread_cancel(_tid);
    // wait for thread to finish
    pthread_join(_tid,NULL);
    tcsetattr(fileno(stdin),TCSANOW,&_oldt);
}
/*
 EXIT,//exit
    TROT,//trot
    FIXED,//fixed_stand
    PASSIVE,//passive
    FREE,//freeStand
    BALANCE,//Balance_test
    SWING,//Swing_test
    STEP,//step_test
*/
UserCommand KeyBoard::checkCmd(){
    switch(_c){
        case '1':
            return UserCommand::EXIT;
        case '2':
            return UserCommand::TROT;
        case '3':
            return UserCommand::FIXED;
        case '4':
            return UserCommand::PASSIVE;
        case '5':
            return UserCommand::FREE;
        case '6':
            return UserCommand::BALANCE;
        case '7':
            return UserCommand::SWING;
        case '8':
            return UserCommand::STEP;
        default:
            return UserCommand::EXIT;
    }
}

void KeyBoard::changeValue(){
    switch(_c){
    case 'w':case 'W':
        userValue.ly = min<float>(userValue.ly+sensitivityLeft, 1.0);
        break;
    case 's':case 'S':
        userValue.ly = max<float>(userValue.ly-sensitivityLeft, -1.0);
        break;
    case 'd':case 'D':
        userValue.lx = min<float>(userValue.lx+sensitivityLeft, 1.0);
        break;
    case 'a':case 'A':
        userValue.lx = max<float>(userValue.lx-sensitivityLeft, -1.0);
        break;

    case 'i':case 'I':
        userValue.ry = min<float>(userValue.ry+sensitivityRight, 1.0);
        break;
    case 'k':case 'K':
        userValue.ry = max<float>(userValue.ry-sensitivityRight, -1.0);
        break;
    case 'l':case 'L':
        userValue.rx = min<float>(userValue.rx+sensitivityRight, 1.0);
        break;
    case 'j':case 'J':
        userValue.rx = max<float>(userValue.rx-sensitivityRight, -1.0);
        break;
    default:
        break;
    }
}
void* KeyBoard::runKeyBoard(void* arg){
    // static function cannot access non-static member variable
    // so we need to cast it to KeyBoard*
    //pthread need static function
    ((KeyBoard*)arg)->run(NULL);
    return NULL;
}

void* KeyBoard::run(void* arg){
    while(true){
        FD_ZERO(&set);
        FD_SET(fileno(stdin),&set);
        // wait for input
        res = select(fileno(stdin)+1,&set,NULL,NULL,NULL);
        if(res>0){
            ret = read( fileno(stdin), &_c, 1);
            userCmd = checkCmd();
            if (userCmd == UserCommand::EXIT) {
                changeValue();
            }
            _c = '\0';
        }
        usleep(1000);
    }
    return NULL;
}