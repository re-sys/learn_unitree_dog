#include "interface/KeyBoard.h"
#include <iostream>
#include <unistd.h>

int main() {
    // 创建键盘监控实例
    KeyBoard* cmdPanel = new KeyBoard();
    
    // 主循环（1kHz频率）
    while(true) {
        // 打印当前摇杆值
        std::cout << "LX: " << cmdPanel->getUserValue().lx 
                  << " LY: " << cmdPanel->getUserValue().ly
                  << " RX: " << cmdPanel->getUserValue().rx
                  << " RY: " << cmdPanel->getUserValue().ry 
                  << std::endl;
        
        // 检查特殊命令
        if(cmdPanel->getUserCmd() != UserCommand::EXIT) {
            std::cout << "Received Command: " 
                      << static_cast<int>(cmdPanel->getUserCmd())
                      << std::endl;
        }
        
        usleep(1000); // 1ms延迟
    }
    return 0;
}