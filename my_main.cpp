#include<iostream>
#include<string>

#include "sort_algorithm.h"


using namespace std;


int main()
{

	cout<<"Hello World!";
    int arr[3]={2, 1,3};
    InsertionSort(arr, false);
    for (auto &ii:arr) cout<<" "<<ii;
    cout<<endl;

	system("pause");
    return 0;
}