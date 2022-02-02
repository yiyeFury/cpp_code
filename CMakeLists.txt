cmake_minimum_required(VERSION 3.17)  # CMake 最低版本号要求
project(cpp_code)  # 项目信息
set(CMAKE_CXX_STANDARD 14)  # 指定C++ 版本

aux_source_directory(. DIR_SRCS)  # 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
# aux_source_directory(ML ML_DIR_SRCS)
# aux_source_directory(CV DIP_DIR_SRCS)
aux_source_directory(mathematics MATH_DIR_SRCS)
aux_source_directory(fusion FUSION_DIR_SRCS)
aux_source_directory(CV CV_DIR_SRCS)
aux_source_directory(Geo GEO_DIR_SRCS)
aux_source_directory(SPA SPA_DIR_SRCS)
aux_source_directory(interpolate INTERPOLATE_DIR_SRCS)
aux_source_directory(NOAA_AVHRR NOAA_AVHRR_DIR_SRCS)
#aux_source_directory(SCM SCM_DIR_SRCS)

# 指定生成目标
# 添加 目录
# add_executable(cpp_code ${DIR_SRCS} ${MATH_DIR_SRCS} ${ML_DIR_SRCS} ${OPENCV_NOTE_DIR_SRCS} ${FUSION_DIR_SRCS})
add_executable(cpp_code ${DIR_SRCS} ${CV_DIR_SRCS} ${MATH_DIR_SRCS} ${FUSION_DIR_SRCS} ${GEO_DIR_SRCS} ${SPA_DIR_SRCS} ${INTERPOLATE_DIR_SRCS} ${NOAA_AVHRR_DIR_SRCS})
# 手动添加 文件
# add_executable(cpp_code main.cpp sort_algorithm.h search_algorithm.h)

# 子目录中 添加 CMakeLists.txt ****************************************************
#add_subdirectory(mathematics)  # mathematics 文件夹中有文件使用了 Eigen，不能采用这种方法
#target_link_libraries(cpp_code MATH_LIB)  # 添加链接库

add_subdirectory(DSA)
target_link_libraries(cpp_code DSA_LIB)  # 添加链接库

add_subdirectory(ML)
target_link_libraries(cpp_code ML_LIB)  # 添加链接库



# Eigen，未编译 ******************************************************************
# aux_source_directory("E:/eigen/eigen-3.3.9/Eigen" EIGEN_DIR_SRCS)
# set(EIGEN_DIR_SRCS "E:/eigen/eigen-3.3.9/Eigen")
#aux_source_directory("D:/Program/eigen/eigen-3.3.9/Eigen" EIGEN_DIR_SRCS)
set(EIGEN_DIR_SRCS "D:/Program/eigen/eigen-3.3.9/Eigen")
include_directories(${EIGEN_DIR_SRCS})
target_link_libraries(cpp_code ${EIGEN_DIR_SRCS})

# OpenCV 已编译 *****************************************************************
# D:/Software/opencv/opencv-4.5.2-cmake-mingw64-build/install 编译后的 opencv install路径
set(OpenCV_DIR D:/Software/opencv/opencv-4.5.2-cmake-mingw64-build/install)
FIND_PACKAGE(OpenCV REQUIRED)
TARGET_LINK_LIBRARIES(cpp_code ${OpenCV_LIBS})

# openMP 配置 *******************************************************************
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()



