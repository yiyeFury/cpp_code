#define PY_SSIZE_T_CLEAN
#include<iostream>
#include<math.h>
#include<Python.h>
#include"my_cpp.h"
using namespace std;



void array_cos(double *in_array, double *out_array, int size)
{
	int ii;
	for (ii = 0; ii < size; ii++) {
		out_array[ii] = cos(in_array[ii]);
	}
}




//void main() {
//	/*int yy = 2016;
//	int flag = 0;
//	flag = leap_year(yy);*/
//
//	double aa[3] = { 1.0, 0.0, 3.1415926 }, bb[3];
//	int ss = 3;
//	array_cos(aa, bb, ss);
//
//	for (int ii = 0; ii < ss; ii++) {
//		cout << bb[ii]<<endl;
//	}
//
//	cout <<endl;
//	system("pause");
//}