#include<iostream>
#include<vector>
#include<string>

using namespace std;

void main()
{
	string s("some string");
	if (s.begin() != s.end()) {
		auto it = s.begin();
		*it = towupper(*it);
	}

	for (auto it = s.begin(); it != s.end(); ++it) {
		cout << *it;
	}
	cout << endl;

	system("pause");
}