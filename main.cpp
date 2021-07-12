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
using namespace std;
//using namespace cv;


#include "DSA/stack.h"

int main()
{
   cout<<"Start\n";
   
   int p = 10;
   
   using arr = int[10];  // typedef int arr[10];
   int *pia = new arr;
   
   int cnt = 0;
   for (int ii=0;ii<p;ii++)
       *(pia+ii) = cnt++;
    
    for (int ii=0;ii<p;ii++)
        cout<<setw(10)<<*(pia+ii);

   cout<<"\nend\n"<<endl;
   cout<<endl;
	  // system("pause");
   return 0;
}