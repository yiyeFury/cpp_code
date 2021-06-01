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
#include "solar_position.h"

using namespace std;



int main()
{
    int n1, n2;
    n1 = DayOfYear(2020, 3, 1);
    n2 = DayOfYear(2021, 2, 28);

    cout<<n1<<endl<<n2;
    cout<<endl;
//	system("pause");
    return 0;
}