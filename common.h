#pragma once
#include<iostream>
#include<iomanip>

using namespace std;

/* -----------------------------------------------------------------------------
打印数组
*/
template<typename T, unsigned num>
void PrintArray1D(T(&p)[num])
{
	for (int ii = 0; ii < num; ii++)
		cout <<setw(6)<< p[ii];
	cout << endl << endl;
}

template<typename T, int M, int N>
void PrintArray2D(const T (&arr)[M][N])
{
    for (int ii=0;ii<M;ii++) {
        for(int jj=0;jj<N;jj++) {
            cout<<setw(6)<<arr[ii][jj];
        }
        cout<<endl;
    }
}

