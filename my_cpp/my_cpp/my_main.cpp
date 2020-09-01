#include<iostream>

#include"sort_algorithm.h"
#include"common.h"

using namespace std;

int (*just_test())[3]
{
	static int b[3] = {1,2,3};
	int (*a)[3] = &b;
	return a;
}

void main()
{
	int(*arr)[3];
	arr = just_test();
	cout << "---------------------" << endl;
	cout << (*arr)[2];
	cout << "-----------------------" << endl;
	cout << (*arr)[0];

	cout << endl;
	system("pause");
}