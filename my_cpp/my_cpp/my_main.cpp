#include<iostream>
#include<string>

#include"date_time.h"
#include"sort_algorithm.h"
#include"common.h"

using namespace std;

void main()
{
	string s1("This");
	unsigned ii = s1.size();
	for (int jj=0;jj<ii;jj++)
		s1[jj] = toupper(s1[jj]);
	cout << s1 << endl;

	system("pause");
}