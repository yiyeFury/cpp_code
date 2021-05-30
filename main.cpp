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

template<int M>
void Test(const char (&aa)[M])
{
    int cnt = 0;
    for (auto ii=begin(aa);ii!=end(aa); ii++) {
        cnt ++;
        cout<<setw(5)<<*ii;
    }
    cout<<endl<<"number is: "<<cnt<<endl;
}

int main()
{
    char a1[] = {'C', '+', '+'};  // 列表初始化，没有空字符
    char a2[] = {'C', '+', '+', '\0'};  // 列表初始化，含有显式的空字符
    char a3[] = "C++";  // 自动添加表示字符串结束的空字符

    Test(a1);
    Test(a2);
    Test(a3);


//    PrintArray(a1);
//    PrintArray(a2);
//    PrintArray(a3);


    cout<<endl;
//	system("pause");
    return 0;
}