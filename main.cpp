#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>  // include <math.h>

#include "DSA/sort.h"
#include "time_conversion.h"
//#include "basic_math.h"
#include "common.h"
#include "my_cpp.h"
//#include "mathematics/matrix_common.h"
#include "solar_position.h"
//#include "mathematics/numerical_analysis.h"
#include "coordinate_conversion.h"
#include "DIP/DIP.h"
#include "ML/linear_regression.h"
#include "DSA/maximum_subarray.h"

using namespace std;




int main()
{
    int arr[] = {1, -1, 2, 3, 5, -1, 0};
    MaxSubArray<int> max_sub;

    max_sub = FindMaximumSubArray(arr, 0, 6, -2);
    cout<<setw(10)<<max_sub.low_idx<<setw(10)<<max_sub.high_idx<<setw(10)<<max_sub.sum<<endl;
    cout<<setw(10)<<arr[max_sub.low_idx]<<setw(10)<<arr[max_sub.high_idx];

    cout<<endl;
//	system("pause");
    return 0;
}