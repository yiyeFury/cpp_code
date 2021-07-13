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


#include "DSA/stack.h"

int main()
{
    cout << "Start\n";
    
    Stack<int> sta;
    cout<<sta.top_<<endl;
    cout<<sta.capacity_<<endl;
    
    sta.Push(19);
    sta.Push(20);
    cout<<sta.Pop();
    
    
    cout << "\nend\n" << endl;
    cout << endl;
    // system("pause");
    return 0;
}