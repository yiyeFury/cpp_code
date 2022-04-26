[TOC]  

# GCC
[**GCC, the GNU Compiler Collection**](https://www.gnu.org/software/gcc/)  

- [Installing GCC](https://gcc.gnu.org/install/)  
- [GCC online documentation](https://gcc.gnu.org/onlinedocs/)  

菜鸟教程--[GCC 参数详解](https://www.runoob.com/w3cnote/gcc-parameter-detail.html)  

CSDN--[g++的基本使用](https://blog.csdn.net/chengqiuming/article/details/88410794)  
[Linux编译工具: gcc入门](https://www.cnblogs.com/QG-whz/p/5456720.html)  


## Note  
Ubuntu docker中自带 GCC编译器  

知乎：g++以及gcc的区别
- `gcc`是GCC中的GUN C Compiler（C 编译器）  
- `g++`是GCC中的GUN C++ Compiler（C++编译器）  
- 使用g++编译文件时，g++会自动链接标准库STL，而gcc不会自动链接STL  

## 命令  
- `g++ -v` 查看版本信息  

## Ubuntu  
Ubuntu安装 GCC: `apt install build-essential`  

## MinGW-w64  
https://www.mingw-w64.org/  

SourceForge--[MinGW-w64 - for 32 and 64 bit Windows](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/)  
	wiki-- https://sourceforge.net/p/mingw-w64/wiki2/Home/  

知乎--[MinGW-w64安装教程——著名C/C++编译器GCC的Windows版本](https://zhuanlan.zhihu.com/p/76613134)  
	[MinGW-w64安装教程——著名C/C++编译器GCC的Windows版本](https://www.cnblogs.com/ggg-327931457/p/9694516.html)  

[MinGW-w64 离线安装过程记录](https://zhuanlan.zhihu.com/p/268275871)  



### [MinGW-w64 版本选择方法](https://www.cnblogs.com/yeyuyan/p/14320715.html)  

32位系统选择i686, 64位系统选择x86_64

选择操作系统接口协议：
- 线程模型：win32:没有C++ 11多线程特性；posix:支持C ++ 11多线程特性
- 开发windows程序，需要选择 win32 ，而开发 Linux、Unix、MacOS等其他操作系统下的程序，则需要选择posix。

选择异常处理模型：异常处理模型:32位系统推荐dwarf，64位系统推荐she
- （64位）：两个异常处理模型供你选择，seh 是新发明的，而sjlj则是古老的。seh性能比较好，但不支持 32位。sjlj稳定性好，支持 32位。
- （32位）：选择了32位后，则可以用dwarf和sjlj两种异常处理模型。同样的，dwarf 的性能要优于sjlj，但不支持64位。

Architecture 是指电脑系统是 32位 还是 64位，根据你的电脑系统做出对应选择。

### 安装 MinGW-64
- 直接下载压缩包
	替代方法：可以在SourceForge下载 MinGW-W64 Online Installer（MinGW-W64-install.exe），该exe辅助在线下载。

- 将解压后的的 …/bin文件夹，加入系统变量。

### 命令  
- `gcc -v` 查看版本
- 在Windows下使用`make`命令
	bin路径下的mingw32-make.exe即为make命令的 原始位置（若想直接使用make，需要将bin加入环境变量，并将mingw32-make.exe重命名为make.exe）。