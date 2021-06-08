#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>  // include <math.h>

#include "sort_algorithm.h"
#include "my_date_time.h"
#include "basic_math.h"
#include "common.h"
#include "my_cpp.h"
#include "basic_matrix.h"
#include "solar_position.h"
#include "numerical_analysis.h"
#include "coordinate_conversion.h"

using namespace std;



int main()
{
    SphericalCoordinate s1;
    Cartesian3D c1;
    c1 = s1.SphericalToCartesian(20.0, 100, 20);
    cout<<setw(20)<<c1.x<<setw(20)<<c1.y<<setw(20)<<c1.z<<endl;


    cout<<endl;
//	system("pause");
    return 0;
}