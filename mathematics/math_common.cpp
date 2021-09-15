//
// Created by admin on 2021/6/8.
//

#include "math_common.h"
#include "../DSA/heapsort.h"
#include "../common.h"

int Factorial(int n)
{
    /*计算阶乘*/
    if (n==0)
        return 1;
    else
        return n*Factorial(n-1);
}


// int main()
// {
//     int arr[5] = {5, 3, 2, 1, 4};
//     Heapsort<int, 5> hs;
//     hs.Sort(arr, 5);
//     PrintArray(arr);
//
//     return 0;
// }

