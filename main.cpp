#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>  // include <math.h>
#include <memory>

#include "common.h"


using namespace std;
//using namespace cv;


// #include "ML/linear_regression.h"
// #include "ML/logistic_regression.h"
#include "DSA/linked_list.h"


int main()
{
    cout << "Start\n";
    
    int *p(new int (42));
    auto q=p;  // p和q指向相同的内存
    delete p;
    p= nullptr;
    
    cout << "\nend\n" << endl;
    cout << endl;
    // system("pause");
    return 0;
}