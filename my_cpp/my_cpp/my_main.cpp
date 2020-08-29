#include<iostream>

#include"sort_algorithm.h"
#include"common.h"

using namespace std;

template<typename T, unsigned num>
void tmp_test(T (&arr)[num], int p)
{
	// const int p = 4;
	T *a1 = new T[p];
	for (int ii = 0; ii < num; ii++) {
		a1[ii] = arr[ii];
		cout << a1[ii] << endl;
	}
		
}


void main()
{
	int arr[5] = { 1, 2, 5, 4, 3};
	print_array(arr);

	// insertion_sort(arr, true);
	// quick_sort(arr, 0, 4, false);
	merge_sort(arr, 0, 4, true);
	print_array(arr);
	// const int t = 3;
	// tmp_test(arr, t);

	cout << endl;
	system("pause");
}