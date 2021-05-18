#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>

#include "sort_algorithm.h"
#include "my_date_time.h"
#include "basic_math.h"
#include "common.h"
#include "my_cpp.h"
#include "basic_matrix.h"

using namespace std;


int main()
{

    const int M=3, N=2, K=4;
    float aa[M][N];
    float bb[N][M];
    float c=0;
    for (int ii = 0;ii<M;ii++) {
        for(int jj = 0;jj<N;jj++) {
            aa[ii][jj] = c++;
        }
    }

    MatrixTranspose(aa, bb);

    PrintArray(aa);
    PrintArray(bb);

    cout<<endl;
//	system("pause");
    return 0;
}