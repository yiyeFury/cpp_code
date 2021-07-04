//
// Created by xie on 2021/7/2.
//

#ifndef CPP_CODE_MAXIMUM_SUBARRAY_H
#define CPP_CODE_MAXIMUM_SUBARRAY_H

template<typename T>
struct MaxSubArray
{
    int low_idx;  // 数组的首元素下标
    int high_idx;  // 数组的尾元素下标
    T sum;  // 数组元素的和
};


template<typename T, int N>
MaxSubArray<T> FindMaxCrossingMatrix(T (&arr)[N], int low, int mid, int high, const T sentinel)
{
    // 函数功能：找到过中间元素的数组和的最大值。
    // arr -------------------- 数组首元素地址
    // low -------------------- 数组首元素下标
    // high ------------------- 数组尾元素下标
    // min -------------------- 哨兵，小于数组中的最小元素值即可

    // 求取左数组的最大子数组
    int left_sum = sentinel;
    T sum = T(0);
    int max_left_idx;  // 最大子数组 左边下标
    for (int ii = mid; ii >= low; ii--) {
        sum += arr[ii];
        if (sum > left_sum) {
            left_sum = sum;
            max_left_idx = ii;
        }
    }

    // 求取右数组的最大子数组
    int right_sum = sentinel;
    int max_right_idx;
    sum = 0;
    for (int jj = mid + 1; jj <= high; jj++) {
        sum += arr[jj];
        if (sum > right_sum) {
            right_sum = sum;
            max_right_idx = jj;
        }
    }

    // 函数返回值
    MaxSubArray<T> sub_arr;
    sub_arr.low_idx = max_left_idx;
    sub_arr.high_idx = max_right_idx;
    sub_arr.sum = left_sum + right_sum;
    return sub_arr;
}

template<typename T, int N>
MaxSubArray<T> FindMaximumSubArray(T (&arr)[N], int low, int high, const T sentinel)
{
    /*
    功能，找到最大子数组
    参数： arr ------------------ 指向数组的指针
    low ------------------ 数组首元素的下标
    high ----------------- 数组尾元素的下标
    sentinel ------------------ 哨兵，数组元素的最小值
    返回：
    */
    MaxSubArray<T> sub_arr;

    if (high == low) {
        sub_arr.low_idx = low;
        sub_arr.high_idx = high;
        sub_arr.sum = arr[low];  // 终止条件，此时数组中只有一个元素
        return(sub_arr);
    }

    MaxSubArray<T> left_sub_arr, right_sub_arr, cross_sub_arr;
    int mid = (low + high) / 2;
    left_sub_arr = FindMaximumSubArray(arr, low, mid, sentinel);
    right_sub_arr = FindMaximumSubArray(arr, mid + 1, high, sentinel);
    cross_sub_arr = FindMaxCrossingMatrix(arr, low, mid, high, sentinel);

    if (left_sub_arr.sum >= right_sub_arr.sum && left_sub_arr.sum >= cross_sub_arr.sum)
        return(left_sub_arr);
    if (right_sub_arr.sum >= left_sub_arr.sum && right_sub_arr.sum >= cross_sub_arr.sum)
        return(right_sub_arr);
    return(cross_sub_arr);
}

#endif //CPP_CODE_MAXIMUM_SUBARRAY_H
