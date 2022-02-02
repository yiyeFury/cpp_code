//
// Created by xie on 2021/6/3.
//

#include "../common.h"
#include "numerical_analysis.h"

int main()
{
    float A[4][4] = {{1, 1, 1,1},
                     {1,2,4,8},
                     {1,3,9,27},
                     {1,4,16,64}};
    float b[4] = {3,4,3,-3};
    float x[4];

    GaussElimination(A, b, x);

    PrintArray(A);
    PrintArray(b);
    PrintArray(x);


    return 0;
}