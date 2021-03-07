#pragma once
#include<iomanip>
#include<iostream>
using namespace std;

void array_cos(double * in_array, double * out_array, int size);

template<typename T, int M>
void PrintArray(const T(&arr)[M])
{
	cout << __func__ << endl;
	for (int ii = 0; ii < M; ii++)
		cout << setw(10) << arr[ii];
	cout << endl << endl;
}


template<typename T, int M, int N>
void PrintArray(const T(&arr)[M][N])
{
	cout << __func__ << endl;
	for (int ii = 0; ii < M; ii++) {
		for (int jj = 0; jj < N; jj++)
			cout << setw(10) << arr[ii][jj];
		cout << endl;
	}
	cout << endl;
}

template <typename T, int M, int N>
void ArrayAdd2D(T(&aa)[M][N], T(&bb)[M][N], T(&cc)[M][N])
{
	// 2d数组相加
	for (int ii = 0; ii < M; ii++)
		for (int jj = 0; jj < N; jj++)
			cc[ii][jj] = aa[ii][jj] + bb[ii][jj];
}



