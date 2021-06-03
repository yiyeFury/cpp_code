#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <math.h>

#include "sort_algorithm.h"
#include "my_date_time.h"
#include "basic_math.h"
#include "common.h"
#include "my_cpp.h"
#include "basic_matrix.h"
#include "solar_position.h"
#include "numerical_analysis.h"

using namespace std;



int main()
{
    int x[] = {11, 12, 13};
    double y[3], dst_y;
    for (int ii=0;ii<3;ii++)
        y[ii] = log(x[ii]);

    PrintArray(y);
    dst_y = LagrangeInterpolation(x, y, 11.5);
    cout<<dst_y<<endl;

    cout<<endl;
//	system("pause");
    return 0;
}