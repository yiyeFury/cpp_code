[TOC]

## 文件介绍
### 初始文件  
- fusion.cpp  
- fusion.h  
- swig_interface_fusion.i  
- swig_setup_fusion.py  
- [numpy.i](https://github.com/numpy/numpy/tree/main/tools/swig) (使用numpy需要此文件)
### 生成临时文件  
- swig_interface_fusion_wrap.cxx  
- build 文件夹  
### 结果文件
- `_Fusion.cp38-win_amd64.pyd`  
- `Fusion.py`  

## 运行命令  
> swig -c++ -python swig_interface_fusion.i  
> python swig_setup_fusion.py build_ext --inplace  

## 详细步骤

> SWIG-4.0 Documentation  
> from 32.2.1 Running SWIG  

1. 正常编写fusion.cpp, fusion.h;  
	> .cpp在文件头部分加入下面的语句（必需）
        ```
        #define PY_SSIZE_T_CLEAN  
        // #include <Python.h>
        ```
2. 编写swig接口文件**swig_interface_fusion.i**，与fusion.cpp, fusion.h放在同一个文件夹中；  
  - swig_interface_fusion.i 首行 `%module Fusion`, Fusion为**模块**名字  
3. 进入swig_interface_fusion.i所在文件夹中，运行命令`swig -c++ -python swig_interface_fusion.i`生成swig_interface_fusion_wrap.cxx和Fusion.py文件；  
   - 将swig.exe所在文件夹加入到系统变量中，否则需要使用 swig.exe的完整路径
   - swig_interface_fusion_wrap.cxx文件名 与 .i 文件名 相关
   - Fusion.py文件名与**模块名字**相关
4. 编写 **swig_setup_fusion.py**文件，与上一步生成的swig_interface_fusion_wrap.cxx和Fusion.py放在同一个文件夹中；
    - swig_setup_fusion.py 该文件中需要指定**模块名字**、**.i接口文件**名字、**cpp**脚本名字，及其它所需文件路径，如**eigen**路径  
5. 运行命令`python swig_setup_fusion.py build_ext --inplace`生成 ***_Fusion.cp38-win_amd64.pyd***文件和build文件夹；  
    - python swig_setup_fusion.py build_ext --inplace可替换build_ext的其他参数
    - **\_Fusion.cp38-win_amd64.pyd**文件名与**模块名字**相关，为 下划线 + module 名，其余为系统标记（可变化）
    - Linux下为 .so, Windows下为 .pyd
    - build文件夹中为临时文件
6. 将Fusion.py和_Fusion.cp38-win_amd64.pyd文件 加入到python环境路径中，即可作为**模块**导入；  
    - **模块名字**即为.i文件第一行`%module Fusion`中 module 后的名字（如 Fusion）
    - 若报错，尝试将_Fusion.cp38-win_amd64.pyd重命名为_Fusion.pyd；

### python运行脚本
- [run_swig.py](https://github.com/yiyeFury/python_code/blob/master/swig/run_swig.py)