//
// Created by xie on 2021/3/6.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void ReadTxt(string txt_file)
{
    ifstream fin(txt_file, ifstream::in);
    string tmp;
    while (getline(fin,tmp)) {
        cout << tmp;
        cout<<endl;
    }
    fin.close();
    cout << endl;
}


