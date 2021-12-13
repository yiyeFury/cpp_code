#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>  // include <math.h>
#include <memory>
#include <omp.h>

#include "common.h"
#include "SCM/successive_correction.h"

using namespace std;
//using namespace cv;


//
// int main()
// {
//     cout << "\nStart\n\n";
//
//     int a = 5;
//     const int m = a;
//     int arr[m];
//
//     for (int ii=0;ii<a;ii++) {
//         arr[ii] = ii+1;
//     }
//
//
//
//     // system("pause");
//     return 0;
// }
//
// vector<vector<string>> vec;
// string s1{"line"}, s2{"work"};
// vector<string> vec1{s1, s2};
// vector<string> vec2{s2, s1};
// vec.push_back(vec1);
// vec.push_back(vec2);
//
// for (auto ii=vec.begin(); ii!=vec.end();ii++) {
//     for (auto jj = (*ii).begin(); jj!=(*ii).end(); jj++) {
//         cout<<*jj<<"  ";
//     }
//     cout<<endl;
// }

