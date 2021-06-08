# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.17)
# 项目信息
project(cpp_code)

set(CMAKE_CXX_STANDARD 14)

# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(cpp_code ${DIR_SRCS} coordinate_conversion.h coordinate_conversion.cpp basic_math.cpp)
#add_executable(cpp_code main.cpp sort_algorithm.h search_algorithm.h)
