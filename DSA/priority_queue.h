//
// Created by xie on 2021/9/4.
//

/*
 * 利用 heap 来实现 优先队列。
 */

#ifndef CPP_CODE_PRIORITY_QUEUE_H
#define CPP_CODE_PRIORITY_QUEUE_H

#include <algorithm>
#include <cmath>

#include "heapsort.h"

template<typename T, int NUM>
T HeapMaximum(const T (&arr)[NUM])
{
    // 返回队列中的最大元素，但不删除该元素
    return arr[0];
}


template<typename T, int NUM>
T HeapExtractMax(T (&arr)[NUM], int &size)
{
    // 返回队列中的最大元素，并将该元素从队列中移除。
    T max = arr[0];  // 此时 首元素为最大元素
    arr[0] = arr[size-1];  // 将尾元素赋值到首元素，假设首元素被剔除
    size--;
    
    Heapsort<T, NUM> heap_obj;
    heap_obj.MaxHeapify(arr, 0, size);  // 将剔除首元素后的堆重排列
    
    return max;
}


template<typename T, int NUM>
void HeapIncreaseKey(T (&arr)[NUM], int idx, T key)
{
    // 队列中增加 元素，idx为指定的下标
    Heapsort<T, NUM> heap_obj;
    
    arr[idx] = key;
    while ((idx > 0) & (arr[heap_obj.Parent(idx)] < arr[idx])) {
        swap(arr[idx], arr[heap_obj.Parent(idx)]);
        idx = heap_obj.Parent(idx);
    }
    
}

template<typename T, int NUM>
void MaxHeapInsert(T (&arr)[NUM], int &size, T key)
{
    size++;
    arr[size] = T(-INFINITY);
    HeapIncreaseKey(arr, size, key);
}

#endif //CPP_CODE_PRIORITY_QUEUE_H
