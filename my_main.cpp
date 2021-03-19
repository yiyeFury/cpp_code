#include<iostream>
#include<string>
#include <vector>
#include <numeric>
#include <algorithm>
#include "sort_algorithm.h"
#include "my_date_time.h"

using namespace std;


int main()
{


    DateTime dt(2020, 12, 31, 23, 59, 55);
    dt.AddSecond(10);
    dt.ShowDateTime();

    cout<<endl;
//	system("pause");
    return 0;
}