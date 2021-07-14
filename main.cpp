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
#include "DSA/queue.h"




int main()
{
    cout << "Start\n";
    
    Queue<int> q;
    q.Enqueue(10);
    q.Enqueue(20);
    int a = q.Dequeue();

    cout<<a<<endl;
    
    // for (int ii=0;ii<q.size_;ii++) {
    //     cout<<setw(5)<<q.data_[ii];
    // }
    
    
    cout << "\nend\n" << endl;
    cout << endl;
    // system("pause");
    return 0;
}