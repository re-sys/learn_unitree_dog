
#include "interface/IOInterface.h"
int main(int argc, char *argv[]){
    IOInterface *ioInter;
    #ifdef COMPILE_WITH_ROS
        ioInter = new IOROS();
    #endif
    #ifdef COMPILE_WITH_REAL_ROBOT
        ioInter = new IOSDK();
    #endif
    return 0;
}