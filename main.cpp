#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>  // include <math.h>

#include "sort_algorithm.h"
#include "my_date_time.h"
//#include "basic_math.h"
#include "common.h"
#include "my_cpp.h"
#include "basic_matrix.h"
#include "solar_position.h"
#include "numerical_analysis.h"
#include "coordinate_conversion.h"
#include "DIP.h"

using namespace std;



int main()
{
    const int M=4, N=5;
    int src[M][N], dst[M][N];
    int cnt = 0;
    for (auto &r:src) {
        for (auto &c:r) {
            c=cnt++;
        }
    }

    reflection(src, dst, 0, 1);
    PrintArray(src);
    PrintArray(dst);

    cout<<endl;
//	system("pause");
    return 0;
}