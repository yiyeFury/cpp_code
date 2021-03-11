#include<iostream>
#include<string>
#include <vector>
#include <numeric>
#include "sort_algorithm.h"


using namespace std;


int main()
{
    vector<int> vec(10, 1);
    for (auto ii=vec.begin(); ii!= vec.end(); ii++) {
        cout<<"  "<<*ii;
    }
    cout<<endl;

    int tmp_sum = accumulate(vec.begin(), vec.end(), 0);

    cout<<"tmp_sum: "<<tmp_sum<<endl;


	system("pause");
    return 0;
}