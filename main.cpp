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

void print_2d(int *pts, int m, int n)
{
    for (int ii=0;ii<m;ii++) {
        for(int jj=0;jj<n;jj++)
            cout<<"      "<<*(pts+ii*n+jj);
        cout<<endl;
    }
    
}


// int main()
// {
//     cout << "\nStart\n\n";
//
//     int aa[4] = {1,2, 3,4};
//     print_2d(aa, 2, 2);
//
//     cout << "\n\nend\n" << endl;
//     // system("pause");
//     return 0;
// }