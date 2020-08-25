#include<iostream>

#include"sort_algorithm.h"
#include"common.h"

using namespace std;

void main()
{
	int arr[5] = { 1, 2, 5, 4, 3};
	print_array(arr);

	//insertion_sort(arr, true);
	swap(arr[0], arr[1]);
	print_array(arr);

	cout << endl;
	system("pause");
}