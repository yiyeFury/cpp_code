#pragma once

#ifndef CPP_CODE_SORT_H
#define CPP_CODE_SORT_H

#include<math.h>

/*
================================================================================
冒泡排序
*/
template<typename T, int num>
void BubbleSort(T (&arr)[num])
{
	int ii, jj;
    for (ii = 0; ii < num; ii++)  // 正向排序
        for (jj = num - 1; jj >ii; jj--)  // 逆向比较大小
            if (arr[jj] < arr[jj - 1])  // 小于则换位置
                swap(arr[jj], arr[jj - 1]);
				
}


/*
================================================================================
插入排序
*/
template<typename T, int NUM>
void InsertionSort(T(&arr)[NUM])
{
    // 升序: 由小到大
	T key;
	int ii, jj;
	
    for (jj = 1; jj < NUM; jj++) {
        key = arr[jj];
        // insert arr[jj] into the sorted sequence arr[0] ~ arr[j-1]
        ii = jj;  // 前一位置
        while (ii > 0 && arr[ii - 1] > key) {
            arr[ii] = arr[ii - 1];  // 位置后移一位
            ii -= 1;
        }
        arr[ii] = key;
    }
}


/* 
================================================================================
快速排序
*/
template<typename T, unsigned num>
int QuickSortPartition(T (&arr)[num], int p, int r, bool is_ascending)
{
	int x, ii;
	x = arr[r];  // 主元
	ii = p;
	if (is_ascending) {  // 递增排序
		for (int jj = p; jj < r; jj++) {  // jj标记当前循环位置
			if (arr[jj] <= x) {  // 寻找小于主元的值
				swap(arr[ii], arr[jj]);  // ii标记待存放小于主元的元素的位置
				ii += 1;
			}
		}
	}
	else {
		for (int jj = p; jj < r; jj++) {
			if (arr[jj] >= x) {
				swap(arr[ii], arr[jj]);
				ii += 1;
			}
		}
	}
	
	swap(arr[ii], arr[r]);  // 将主元放入位置，其左边/右边均为小于等于/大于等于它的值
	return ii;
}

template<typename T, unsigned num>
void QuickSort(T (&arr)[num], int p, int r, bool is_ascending)
{
	int q;
	if (p < r) {
		q = partition(arr, p, r, is_ascending);
		quick_sort(arr, p, q - 1, is_ascending);
		quick_sort(arr, q + 1, r, is_ascending);
	}
}


/*
================================================================================
归并排序
*/
template<typename T, unsigned num>
void merge(T(&arr)[num], int p, int q, int r, bool is_ascending)
{
	int ii = 0, jj = 0, kk = 0;

	int n1 = q - p + 1; // 下标范围 [p, q]
	int n2 = r - q;  // 下标范围 (q, r]
	T *left = new T[n1];
	T *right = new T[n2];

	for (ii = 0; ii < n1; ii++)
		left[ii] = arr[p + ii];

	for (ii = 0; ii < n2; ii++)
		right[ii] = arr[q + ii + 1];

	ii = 0, jj = 0;
	if (is_ascending) {  // 递增排序
		for (kk = p; kk <= r; kk++) {
			if ((ii < n1) && (((jj < n2) && (left[ii] <= right[jj])) || (jj >= n2))) {
				arr[kk] = left[ii];
				ii++;
			}
			else if ((jj < n2) && (((ii < n1) && (right[jj] <= left[ii])) || (ii >= n1))) {
				arr[kk] = right[jj];
				jj++;
			}
		}
	}
	else {
		for (kk = p; kk <= r; kk++) {
			if ((ii < n1) && (((jj < n2) && (left[ii] >= right[jj])) || (jj >= n2))) {
				arr[kk] = left[ii];
				ii++;
			}
			else if ((jj < n2) && (((ii < n1) && (right[jj] >= left[ii])) || (ii >= n1))) {
				arr[kk] = right[jj];
				jj++;
			}
		}
	}
}

template<typename T, unsigned num>
void merge_sort(T(&arr)[num], int p, int r, bool is_ascending)
{
	if (p < r) {
		int q = floor((p + r) / 2);
		merge_sort(arr, p, q, is_ascending);
		merge_sort(arr, q + 1, r, is_ascending);
		merge(arr, p, q, r, is_ascending);
	}
}


#endif // CPP_CODE_SORT_H