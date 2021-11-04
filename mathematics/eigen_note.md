[TOC]

# [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)

> [Document](https://eigen.tuxfamily.org/dox/)  
> [知乎--Eigen的速度为什么这么快？](https://www.zhihu.com/question/28571059)  
> [CSDN--比较OpenBLAS，Intel MKL和Eigen的矩阵相乘性能](https://blog.csdn.net/AMDS123/article/details/72761039)

## 1. Install
参考解压后的 **INSTALL** 文件

## 2. Configure
- CMakeLists.txt中加入eigen的解压路径  
```Cmake
# Eigen，未编译
set(EIGEN_DIR_SRCS "E:/eigen/eigen-3.3.9/Eigen")
include_directories(${EIGEN_DIR_SRCS})
target_link_libraries(cpp_code ${EIGEN_DIR_SRCS})
```

## 3. 使用Eigen
### [The Matrix class](https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html)

> [博客园--C++矩阵库 Eigen 简介](https://www.cnblogs.com/rainbow70626/p/8819119.html)  

#### Convenience typedefs  
*处定义的形式不全，具体参考构造函数*  
1. Eigen defines the following Matrix typedefs:  
    - MatrixNt for Matrix<type, N, N>. For example, MatrixXi for Matrix<int, Dynamic, Dynamic>.
    - VectorNt for Matrix<type, N, 1>. For example, Vector2f for Matrix<float, 2, 1>.
    - RowVectorNt for Matrix<type, 1, N>. For example, RowVector3d for Matrix<double, 1, 3>.  

	Where:  
    - N can be any one of 2, 3, 4, or X (meaning Dynamic).  
    - t can be any one of `i` (meaning int), `f` (meaning float), `d` (meaning double), `cf` (meaning `complex<float>`), or `cd` (meaning `complex<double>`). The fact that typedefs are only defined for these five types doesn't mean that they are the only supported scalar types. For example, all standard integer types are supported, see Scalar types.

### 求解线性方程组
- [博客园--使用Eigen求解线性方程组](https://www.cnblogs.com/feifanrensheng/articles/8510702.html)  
```c++
// Solve Ax = b. Result stored in x. Matlab: x = A \ b.
x = A.ldlt().solve(b));  // A sym. p.s.d.    #include <Eigen/Cholesky>
x = A.llt().solve(b));  // A sym. p.d.       #include <Eigen/Cholesky>
x = A.lu().solve(b));  // Stable and fast.   #include <Eigen/LU>
x = A.qr().solve(b));  // No pivoting.       #include <Eigen/QR>
x = A.svd().solve(b));  // Stable, slowest.  #include <Eigen/SVD>
```

