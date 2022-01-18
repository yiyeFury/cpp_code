#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>  // include <math.h>
#include <memory>
#include <omp.h>

#include "common.h"
#include "SCM/successive_correction.h"


using namespace std;
//using namespace cv;

const int R = 4;
const int C = 5;


void ArrayAdd2d(int (&ref_arr)[R][C], int ad=1)
{
    for (int ii=0;ii<4;ii++) {
        for (int jj=0;jj<5;jj++) {
            ref_arr[ii][jj] += ad;
        }
    }
}

int main()
{

    int arr[R][C];
    int ii, jj;

    for (ii=0;ii<R;ii++) {
        for (jj = 0;jj<C;jj++) {
            arr[ii][jj] = 1;
        }
    }

    ArrayAdd2d(arr, 10);

    for (ii=0;ii<R;ii++) {
        for (jj = 0;jj<C;jj++) {
            cout<<arr[ii][jj]<<"   ";
        }
        cout<<endl;
    }



    // system("pause");
    return 0;
}





