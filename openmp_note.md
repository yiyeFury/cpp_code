[TOC]

# [OpenMp](https://www.openmp.org/)  

> OpenMp [Tutorials & Articles](https://www.openmp.org/resources/tutorials-articles/)  

> Microsoft Docs--[OpenMP Library Reference](https://docs.microsoft.com/en-us/cpp/parallel/openmp/reference/openmp-library-reference?view=msvc-160)  
- [A. Examples](https://docs.microsoft.com/en-us/cpp/parallel/openmp/a-examples?view=msvc-160)  

> [CSDN--在C++中使用openmp进行多线程编程](https://blog.csdn.net/acaiwlj/article/details/49818965)  
> [CSDN--openmp在多重循环内的简单使用及其详解](https://blog.csdn.net/allyli0022/article/details/52702466)  
> [知乎--OpenMP并行开发(C++)](https://zhuanlan.zhihu.com/p/51173703)  

- simple test
```c++
#include <omp.h>
int main()
{
    cout << "\nStart\n\n";

    int num_thd = 3;
    #pragma omp parallel for num_threads(num_thd)
    for(int ii=0;ii<20;ii++) {
        int id = omp_get_thread_num();
        cout<<"id= "<<id<<"   ";
        cout<<"ii= "<<ii<<"   ";
        cout<<endl;
    }

    cout << "\n\nend\n" << endl;
    // system("pause");
    return 0;
}
```

### CMakeList.txt
``` CMake
# openMP 配置
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()
```