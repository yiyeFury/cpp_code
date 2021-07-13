#include<iostream>
#include<string>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <cmath>  // include <math.h>

#include "DSA/sort.h"
#include "time_conversion.h"
//#include "basic_math.h"
#include "common.h"
#include "my_cpp.h"
//#include "mathematics/matrix_common.h"
#include "solar_position.h"
//#include "mathematics/numerical_analysis.h"
#include "coordinate_conversion.h"
#include "DIP/DIP.h"
#include "ML/linear_regression.h"
#include "DSA/maximum_subarray.h"

//
//#include <opencv2/opencv.hpp>
//

#include <memory>
using namespace std;
//using namespace cv;


#include "DSA/stack.h"

int main()
{
    cout << "Start\n";
    int n = 10;
    allocator<string> alloc;
    auto const p = alloc.allocate(n);  // 分配n个未初始化的string
    
    allocator<int> alloc1;
    allocator<int>::pointer alloc_ptr;
    
    alloc_ptr = alloc1.allocate(10);
    int ii;
    for (ii = 0; ii < 10; ii++) {
        alloc_ptr[ii] = ii;
    }
    
    for (ii = 0; ii < 10; ii++) {
        cout << setw(5) << alloc_ptr[ii];
    }
    
    alloc1.deallocate(alloc_ptr, 10);
    
    cout << "\nend\n" << endl;
    cout << endl;
    // system("pause");
    return 0;
}