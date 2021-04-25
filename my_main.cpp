#include<iostream>
#include<string>
#include <vector>

#include <numeric>
#include <algorithm>
#include "sort_algorithm.h"
#include "my_date_time.h"
#include "my_mathmatics.h"
#include "common.h"

using namespace std;


int main()
{
    const int M=4, N=5;
    double val = 0.0;

    double aa[M][N];
    for (int ii=0;ii<M;ii++) {
        for (int jj=0;jj<N;jj++) {
            val++;
            aa[ii][jj] = val;
        }
    }

    PrintArray2D(aa);

    double bb[3] = {1,2,3};
    PrintArray1D(bb);

    cout<<endl;
//	system("pause");
    return 0;
}