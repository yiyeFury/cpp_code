#include<iostream>
#include<string>
#include <vector>
#include <numeric>
#include <algorithm>
#include "sort_algorithm.h"


using namespace std;


int main()
{
//    vector<int> vec{12, 20, 43, 30};
//    int val = 42;
//    auto result = find(vec.begin(), vec.end(), val);
//
//    cout<<"The value "<<val <<(result==vec.end()? " is not present": " is present")<<endl;
//    if (result != vec.end()) {
//        cout<<*result<<endl;
//    }

    int ia[] = {27, 210, 12, 47, 109, 83};
    int val = 83;
    int *result = find(begin(ia), end(ia), val);


    cout<<*result<<endl;



	system("pause");
    return 0;
}