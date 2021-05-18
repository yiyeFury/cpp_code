#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>

//#include "sort_algorithm.h"
//#include "my_date_time.h"
//#include "basic_math.h"
//#include "common.h"
//#include "my_cpp.h"

using namespace std;


int main()
{

    const int M=2, N=3;
    int aa[M][N], bb[M][N], cc[M][N], c=0;
    for (int ii = 0;ii<M;ii++) {
        for(int jj = 0;jj<N;jj++) {
            aa[ii][jj] = c++;
            bb[ii][jj] = 1;
        }
    }



    cout<<endl;
//	system("pause");
    return 0;
}