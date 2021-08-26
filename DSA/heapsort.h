//
// Created by xie on 2021/8/25.
//

#ifndef CPP_CODE_HEAPSORT_H
#define CPP_CODE_HEAPSORT_H

#include <algorithm>
using namespace std;

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
    
    void MaxHeapify(T (&arr)[NUM], int idx, int size);
    void BuildMaxHeap(T (&arr)[NUM], int size);
    void Sort(T (&arr)[NUM], int size);
};


template<typename T, int NUM>
Heapsort<T, NUM>::Heapsort() {}


template<typename T, int NUM>
Heapsort<T, NUM>::~Heapsort() {}


template<typename T, int NUM>
int Heapsort<T, NUM>::Parent(int ii)
{
    // ii >= 1
    int idx_parent(0);  // 树的根节点是A[0]
    if (ii > 0) idx_parent = (++ii) / 2 - 1;
    return idx_parent;
}


template<typename T, int NUM>
int Heapsort<T, NUM>::Left(int ii)
{
    // 计算左子树的下标
    return 2 * ii + 1;
}


template<typename T, int NUM>
int Heapsort<T, NUM>::Right(int ii)
{
    // 计算右子树的下标
    return 2 * ii + 2;
}


template<typename T, int NUM>
void Heapsort<T, NUM>::MaxHeapify(T (&arr)[NUM], int idx, int size)
{
    /* 在当前子树，堆已经正确建立的基础上（满足堆的性质），当其中某个节点变动时，维护堆的性质，确保父节点大于等于其左右子节点
     * idx 当前子树根节点的位置
     * size 当前子树中节点的个数
     */
    int ll, rr, large;
    ll = Left(idx);  // 左子的下标
    rr = Right(idx);  // 右子的下标
    
    large = idx;  // 假设ii大于其左右子节点
    if (ll < size && arr[ll] > arr[large])  // 判断左子树
        large = ll;
    
    if (rr < size && arr[rr] > arr[large])  // 右子树
        large = rr;
    
    if (large != idx) {
        // large 表示父节点及左右子节点中的最大值，若不为父节点，交换其与父节点的位置，重排其子树
        swap(arr[idx], arr[large]);
        MaxHeapify(arr, large, size);
    }
}


template<typename T, int NUM>
void Heapsort<T, NUM>::BuildMaxHeap(T (&arr)[NUM], int size)
{
    /* 建堆
     *
     */
    // 此时 num = heapSize
    // 根据数组中元素的个数，计算最后一个父节点的位置(计算末尾元素的父节点), 即ii+1...num-1全部为叶节点
    int ii = Parent(size - 1);
    for (; ii >= 0; --ii)  // 遍历二叉树的所有父节点，保证满足最大堆性质（自底部向上遍历父节点）
        MaxHeapify(arr, ii, size);
}


template<typename T, int NUM>
void Heapsort<T, NUM>::Sort(T (&arr)[NUM], int size)
{
    /*
     * 堆排序算法
     */
    BuildMaxHeap(arr, NUM);  // 建立最大堆，首元素为最大元素
    for (int ii = size - 1; ii >= 1; --ii) {
        swap(arr[0], arr[ii]);  // 交换待排序序列中首元素与要排序的尾元素的位置
        // 当前树的根节点已经被替换，其余部分满足堆的性质，进行维护
        MaxHeapify(arr, 0, --size);
    }
}


#endif //CPP_CODE_HEAPSORT_H
