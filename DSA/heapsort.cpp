//
// Created by xie on 2021/8/25.
//

#include "heapsort.h"
#include "../common.h"


int main()
{
    int arr[5] = {5, 3, 2, 1, 4};
    Heapsort<int, 5> hs;
    hs.Sort(arr, 5);
    PrintArray(arr);


    return 0;
}


