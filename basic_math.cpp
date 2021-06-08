//
// Created by admin on 2021/6/8.
//

#include "basic_math.h"

int Factorial(int n)
{
    /*计算阶乘*/
    if (n==0)
        return 1;
    else
        return n*Factorial(n-1);
}