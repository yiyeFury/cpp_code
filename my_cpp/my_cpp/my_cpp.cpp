#include<iostream>
#include"my_cpp.h"
using namespace std;

int leap_year(int year)
{
	// 计算是否为闰年
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
		return 1;
	}
	else {
		return 0;
	}
		
}

//void main() {
//	int yy = 2016;
//	int flag = 0;
//	flag = leap_year(yy);
//	cout << flag <<endl;
//	system("pause");
//}