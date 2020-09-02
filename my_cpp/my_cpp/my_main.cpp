#include<iostream>

#include"date_time.h"
#include"sort_algorithm.h"
#include"common.h"

using namespace std;


void main()
{
	Date d1(2020, 12, 21);
	d1.show_date();
	d1.add_day(365);
	d1.show_date();

	cout << endl;
	system("pause");
}