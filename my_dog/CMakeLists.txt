cmake_minimum_required(VERSION 3.14)
project(keyboard_test)


find_package(Eigen3 REQUIRED)
# 包含路径
include_directories(
    include
    ${PROJECT_SOURCE_DIR}
)

# 源文件
add_executable(keyboard_test 
    src/interface/KeyBoard.cpp
    src/test_keyboard.cpp
)

# 链接选项
target_link_libraries(keyboard_test 
    -pthread 
    Eigen3::Eigen
)

# macOS特殊配置
if(APPLE)
    target_link_options(keyboard_test PRIVATE -framework CoreFoundation)
endif()