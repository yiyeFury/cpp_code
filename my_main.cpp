#include<iostream>
#include<string>
#include <vector>

#include <numeric>
#include <algorithm>
#include "sort_algorithm.h"
#include "my_date_time.h"
#include "my_mathmatics.h"

using namespace std;


int main()
{

    int a[5] = {1,2,3,4,5};
    double m, v;
    m = sample_mean(a);
    cout<<"mean: "<<m<<endl;

    v = sample_variance(a);
    cout<<"variance: "<<v<<endl;


    cout<<endl;
//	system("pause");
    return 0;
}