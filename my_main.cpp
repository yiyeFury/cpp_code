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
    tuple<size_t, size_t, size_t> three_d{1,2,3};

    tuple<string, int, double> item1("ISBN", 2, 20.00);
    auto item = make_tuple("ISBN", 2, 20.00);

    auto book = get<0>(item);
    auto cnt = get<1>(item);

    typedef decltype(item) trans;
    size_t sz = tuple_size<trans>::value;
    tuple_element<1, trans>::type cnt1 = get<1>(item);

    cout<<endl;
//	system("pause");
    return 0;
}