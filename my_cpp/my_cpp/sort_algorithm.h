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



/*
================================================================================
快速排序
*/
template<typename T, unsigned num>
int partition(T (&arr)[num], int p, int r, bool is_ascending)
{
	int x, ii;
	x = arr[r];  // 主元
	ii = p;
	if (is_ascending) {
		for (int jj = p; jj < r-1; jj++) {
			if (arr[jj] <= x) {  // 寻找小于主元的值
				swap(arr[ii], arr[jj]);
				ii += 1;
			}
		}
	}
	else {
		for (int jj = p; jj < r-1; jj++) {
			if (arr[jj] >= x) {
				swap(arr[ii], arr[jj]);
				ii += 1;
			}
		}
	}
	
	swap(arr[ii], arr[r]);
	return ii;
}

template<typename T, unsigned num>
void quick_sort(T (&arr)[num], int p, int r, bool is_ascending)
{
	int q;
	if (p < r) {
		q = partition(arr, p, r, is_ascending);
		quick_sort(arr, p, q - 1, is_ascending);
		quick_sort(arr, q + 1, r, is_ascending);
	}
}
