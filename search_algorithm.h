#pragma once

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