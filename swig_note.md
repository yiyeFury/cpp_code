[TOC]

# Materials
- [SWIG](http://www.swig.org/index.php)  
> SWIG is a software development tool that simplifies the task of interfacing different languages to **C and C++** programs.

- [numpy.i](https://github.com/numpy/numpy/tree/master/tools/swig)--传递numpy需要使用此文件
	swg的 \*.i 接口文件中需要指定该文件的位置。

- [SWIG-4.0 Documentation](http://www.swig.org/Doc4.0/SWIGDocumentation.pdf)--32.2.1 Running SWIG
- swig-[tutorial](http://www.swig.org/tutorial.html)  

## 常用命令
`swig --help`
`swig -python -help`

## 编写setup
> [CSDN--使用SWIG编写C/C++代码的Python接口并使用distutils进行连接静态库编译](https://blog.csdn.net/hahajinbu/article/details/80819522)
> [SWIG实现python对c++封装](http://www.cppblog.com/wanghaiguang/archive/2016/08/18/214201.html)
> [CSDN--C++ 扩展python （四）传递numpy（使用SWIG）](https://blog.csdn.net/sinat_36215255/article/details/104987976)

## OpenMP并行
> Cython--Using Parallelism--[Compiling](http://docs.cython.org/en/latest/src/userguide/parallelism.html#compiling)


## Ubuntu 安装 swig
> 参考[CSDN--ubuntu下安装swig-3.0.12](https://blog.csdn.net/zhangkzz/article/details/88555830)

- 安装 pcre
`apt install libpcre3 libpcre3-dev`

- 解压 swig压缩包
- 进入加压后的文件夹
```
# 以下操作在 root权限下进行，其他权限未尝试
./configure
make
make install  
# 默认安装到此位置 /usr/local/share/swig/4.0.1
# 4.0.1为版本号
```

- 路径加入 bashrc
> `vim ~/.bashrc`
```
SWIG_PATH=/usr/local/share/swig/4.0.1
PATH=$PATH:$SWIG_PATH
```
> `source ~/.bashrc`

- 测试是否安装成功
`swig -version`

## SWIG and Python  
详细步骤见 [示例](https://github.com/yiyeFury/cpp_code/blob/master/fusion/README_SWIG.md)  
