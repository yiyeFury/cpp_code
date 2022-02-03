//
// Created by xie on 2022/2/3.
//

#ifndef CPP_CODE_SEARCH_H
#define CPP_CODE_SEARCH_H

#include <iostream>

using namespace std;


/* *****************************************************************************
 * --------------------   二分搜索   --------------------------------------------
 ******************************************************************************/
template<typename T, int M>
int BinarySearch(T(&arr)[M], T dst_val, bool is_ascend=true)
{
    /*
    arr: array，已经排好序
    dst_val: 目标值
    is_ascend： bool；true for ascending， false for descending
    */
    int low = 0, high = M - 1;
    int mid;

    if (is_ascend) { // 递增排序
        while (low <= high) {
            mid = (low + high) / 2;
            if (dst_val == arr[mid]) return mid;
            else if (dst_val < arr[mid]) high = mid - 1;
            else low = mid + 1;
        }
    }else { // 递减排序
        while (low <= high) {
            mid = (low + high) / 2;
            if (dst_val == arr[mid]) return mid;
            else if (arr[mid] > dst_val) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}


/*
 * 对 由小到大排列 的数组进行比较查找，找到第一个大于等于当前值 的位置下标
 */
template<typename T1, typename T2, int num>
int BinarySearchAscendGE(T1 (&arr)[num], T2 dst_val)
{
    /*
     * arr: array，1d-array，由小到大排序
     * dst_val: 目标值
     */
    int low = 0, high = num - 1;
    int mid;

    while (low < high) {
        // cout << "Low: "<<low<<", High: "<<high<<endl;
        if (low == high - 1) {
            return high;
        }

        mid = (low + high) / 2;
        // cout<<"Mid: "<<mid<<", Mid Val: "<<arr[mid]<<endl;
        if (dst_val == arr[mid]) return mid;
        else if (dst_val < arr[mid]) high = mid;
        else low = mid;
    }

    return -1;
}


/*
 * 对 由大到小 排列的数组进行比较查找，找到 第一个 小于等于目标值 的位置下标
 */
template<typename T1, typename T2, int num>
int BinarySearchDescendLE(T1 (&arr)[num], T2 dst_val)
{
    /*
     * arr: array，1d-array，由大到小排序，如纬度 90~-90
     * dst_val: 目标值
     */
    int low = 0, high = num - 1;
    int mid;

    while (low < high) {
        // cout << "Low: "<<low<<", High: "<<high<<endl;
        if (low == high - 1) {
            return high;
        }

        mid = (low + high) / 2;
        if (dst_val == arr[mid]) return mid;
        else if (dst_val > arr[mid]) high = mid;
        else low = mid;
    }

    return -1;
}

#endif //CPP_CODE_SEARCH_H
