#include<iostream>
using namespace std;

void print_array(int *p, int num)
{
	for (int ii = 0; ii < num; ii++)
		cout << ' ' << p[ii];
	cout << endl<<endl;
}

void swap(int &a, int &b)
{
	// 初步版本，交换两个整数的值
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}