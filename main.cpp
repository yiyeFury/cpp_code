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

using namespace std;



int main()
{
    int a1[5][10];
    int cnt = 0;
    for (auto &row:a1) {
        for (auto &col:row) {
            col = ++cnt;
        }
    }

    for (auto &row:a1) {
        for (auto col:row) {
            cout<<setw(5)<<col;
        }
    }


    cout<<endl;
//	system("pause");
    return 0;
}