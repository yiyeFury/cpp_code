#include<iostream>

#include"date_time.h"
#include"sort_algorithm.h"
#include"common.h"

using namespace std;

void main()
{
	DateTime dt1(2020, 9, 8, 23, 59, 42);
	cout << "-----------------------------------------------------------------";
	cout << endl;

	dt1.show_date_time();
	
	cout << endl;
	cout << "-----------------------------------------------------------------";
	cout << endl;

	dt1.add_second(40);
	dt1.show_date();
	cout << endl;
	dt1.show_time();
	cout << endl;
	dt1.show_date_time();

	cout << endl;
	system("pause");
}