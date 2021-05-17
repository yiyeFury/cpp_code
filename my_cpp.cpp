#define PY_SSIZE_T_CLEAN
#include<iostream>
#include<math.h>
//#include<Python.h>
#include"my_cpp.h"
using namespace std;



void array_cos(double *in_array, double *out_array, int size)
{
	int ii;
	for (ii = 0; ii < size; ii++) {
		out_array[ii] = cos(in_array[ii]);
	}
}






