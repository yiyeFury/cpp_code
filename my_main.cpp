#include<iostream>
#include<string>
#include <vector>

#include <numeric>
#include <algorithm>
#include "sort_algorithm.h"
#include "my_date_time.h"
#include "my_mathmatics.h"

using namespace std;


int main()
{
    const int M=2, N=5;
    double val = 0.0;

    double arr[M][N];
    for (int ii=0;ii<M;ii++) {
        for (int jj=0;jj<N;jj++) {
            arr[ii][jj] = val;
            val ++;
        }
    }

    double cov_mat[N][N];
    CovarianceMatrix(arr, cov_mat);
    for (int ii=0;ii<N;ii++) {
        for (int jj=0;jj<N;jj++) {
            cout<<cov_mat[ii][jj]<<"           ";
        }
        cout<<endl;
    }
    cout<<endl;

    for (int ii =0;ii<M;ii++) {
        for (int jj=0;jj<N;jj++) {
            cout<<arr[ii][jj]<<"            ";
        }
        cout<<endl;
    }


    cout<<endl;
//	system("pause");
    return 0;
}