#include<iostream>

#include"sort_algorithm.h"
#include"common.h"

using namespace std;


void main()
{
	int arr[] = { 5, 3, 17, 10, 84, 19, 6, 22, 9};
	print_array(arr);

	// insertion_sort(arr, true);
	// quick_sort(arr, 0, 4, false);
	// merge_sort(arr, 0, 4, true);
	heap_sort(arr);
	print_array(arr);
	// const int t = 3;
	// tmp_test(arr, t);

	cout << endl;
	system("pause");
}