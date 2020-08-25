#pragma once


/*
============================================================================
冒泡排序
*/
template<typename T, unsigned num>
void bubble_sort(T (&arr)[num], bool is_ascending)
{
	int ii, jj;
	if (is_ascending) {
		for (ii = 0; ii < num; ii++)  // 正向排序
			for (jj = num - 1; jj >ii; jj--)  // 逆向比较大小
				if (arr[jj] < arr[jj - 1])  // 小于则换位置
					swap(arr[jj], arr[jj - 1]);
	}
	else {
		for (ii = 0; ii < num; ii++)
			for (jj = num - 1; jj >ii; jj--)
				if (arr[jj] > arr[jj - 1])  // 大于则换位置
					swap(arr[jj], arr[jj - 1]);
	}


}


/*
================================================================================
插入排序
*/
template<typename T, unsigned num>
void insertion_sort(T(&arr)[num], bool is_ascending)
{

	T key;
	int ii, jj;
	if (is_ascending) {  // 升序
		for (jj = 1; jj < num; jj++) {
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
	else {  // 降序
		for (jj = 1; jj < num; jj++) {
			key = arr[jj];
			// insert arr[jj] into the sorted sequence arr[0] ~ arr[j-1]
			ii = jj - 1;
			while (ii >= 0 && arr[ii] < key) {
				arr[ii + 1] = arr[ii];
				ii -= 1;
			}
			arr[ii + 1] = key;
		}
	}
}
