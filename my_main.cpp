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
    tuple<int, int> tuple2(10, 20);

    auto a = get<0>(tuple2);
    auto b = get<1>(tuple2);

    cout<<setw(10)<<a<<setw(5)<<b<<endl;

    cout<<endl;
//	system("pause");
    return 0;
}