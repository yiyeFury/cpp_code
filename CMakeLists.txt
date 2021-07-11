# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.17)
# 项目信息
project(cpp_code)

set(CMAKE_CXX_STANDARD 14)


aux_source_directory(. DIR_SRCS)  # 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory(ML ML_DIR_SRCS)
aux_source_directory(DIP DIP_DIR_SRCS)
aux_source_directory(mathematics MATH_DIR_SRCS)
aux_source_directory(opencv_note OPENCV_NOTE_DIR_SRCS)
aux_source_directory(DSA DSA_DIR_SRCS)

# 指定生成目标
add_executable(cpp_code ${DIR_SRCS} ${ML_DIR_SRCS} ${DIP_DIR_SRCS} ${MATH_DIR_SRCS} ${OPENCV_NOTE_DIR_SRCS} ${DSA_DIR_SRCS})
#add_executable(cpp_code main.cpp sort_algorithm.h search_algorithm.h)

# D:/Software/opencv/opencv-4.5.2-cmake-mingw64-build/install 编译后的 opencv install路径
set(OpenCV_DIR D:/Software/opencv/opencv-4.5.2-cmake-mingw64-build/install)
FIND_PACKAGE(OpenCV REQUIRED)
TARGET_LINK_LIBRARIES(cpp_code ${OpenCV_LIBS})
