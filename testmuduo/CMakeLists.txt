cmake_minimum_required(VERSION 3.0)
project(main)
#配置编译选项
set(CMAKE_CXX_FLGS ${CMAKE_CXX_FLGS} -g)

#配置头文件搜索路径
#include_directories()
#配置库文件搜索路径
#link_directories()

#设置需要编译的源文件列表
set(SRC_LIST muduo.cpp)
#设置可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#把.指定路径下的所有源文件添加到SRC_LIST变量中
#aux_source_directory(. SRC_LIST)
#表示可生成执行文件server ,由SRC_LIST变量指定的源文件编译而成
add_executable(server ${SRC_LIST})
#server这个目标程序需要链接的库文件
target_link_libraries(server muduo_net muduo_base pthread)
