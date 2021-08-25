//
// Created by xie on 2021/8/25.
//

#ifndef CPP_CODE_HEAPSORT_H
#define CPP_CODE_HEAPSORT_H

#include <algorithm>

template<typename T, int NUM>
class Heapsort
{
public:
    int capacity_;
    int size_;
public:
    Heapsort();
    ~Heapsort();

public:
    int Parent(int ii);
    int Left(int ii);
    int Right(int ii);
    
    void MaxHeapify(T (&arr)[NUM], int idx);
    void BuildMaxHeap(T (&arr)[NUM]);
    void Sort(T (&arr)[NUM]);
};


template<typename T, int NUM>
void Heapsort<T, NUM>::MaxHeapify(T (&arr)[NUM], int idx)
{
    /* 维护堆的性质，确保父节点大于等于其左右子节点
     * idx 当前根节点的位置
     */
    int ll, rr, large;
    ll = Left(idx);  // 左子树的下标
    rr = Right(idx);  // 右子树的下标
    
    large = idx;  // 假设ii大于其左右子节点
    if (ll < size_ && arr[ll] > arr[large])  // 判断左子树
        large = ll;
    
    if (rr < size_ && arr[rr] > arr[large])  // 右子树
        large = rr;
    
    if (large != idx) {
        // large 表示父节点及左右子节点中的最大值，若不为父节点，交换其与父节点的位置，重排其子树
        swap(arr[idx], arr[large]);
        MaxHeapify(arr, large);
    }
}


template<typename T, int NUM>
void Heapsort<T, NUM>::BuildMaxHeap(T (&arr)[NUM])
{
    /* 建堆
     *
     */
    // 此时 num = heapSize
    // 根据数组中元素的个数，计算最后一个父节点的位置(计算末尾元素的父节点), 即ii+1...num-1全部为叶节点
    int ii = Parent(size_ - 1);
    for (; ii >= 0; --ii)  // 遍历二叉树的所有父节点，保证满足最大堆性质
        MaxHeapify(arr, ii);
}


template<typename T, int NUM>
void Heapsort<T, NUM>::Sort(T (&arr)[NUM])
{
    /*
     * 堆排序算法
     */
    BuildMaxHeap(arr);  // 建立最大堆，首元素为最大元素
    for (int ii = size_ - 1; ii >= 1; --ii) {
        swap(arr[0], arr[ii]);  // 交换待排序序列中首元素与要排序的尾元素的位置
        MaxHeapify(arr, 0, --size_);
    }
}

#endif //CPP_CODE_HEAPSORT_H
