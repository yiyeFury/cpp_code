#pragma once

int leap_year(int year);
void array_cos(double * in_array, double * out_array, int size);

//template <typename T, int N, int M>
//void ArrayAdd2D(T (&aa)[M][N], T (&bb)[M][N], T(&cc)[M][N])
//{
//	// 2d数组相加
//	for (int ii = 0; ii < M; ii++)
//		for (int jj = 0; jj < N; jj++)
//			cc[ii][jj] = aa[ii][jj] + bb[ii][jj];
//}

template <typename T, int M, int N>
void ArrayAdd2D(T(&aa)[M][N], T(&bb)[M][N], T(&cc)[M][N])
{
	// 2d数组相加
	for (int ii = 0; ii < M; ii++)
		for (int jj = 0; jj < N; jj++)
			cc[ii][jj] = aa[ii][jj] + bb[ii][jj];
}



