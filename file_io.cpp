//
// Created by xie on 2021/3/6.
//

#include <string>
#include <fstream>
#include <iostream>
#include "file_io.h"

using namespace std;

class TMP
{
public:
    short int num;
    unsigned int len;
};

#define SWAP_4(x) ( ((x) << 24) | \
         (((x) << 8) & 0x00ff0000) | \
         (((x) >> 8) & 0x0000ff00) | \
         ((x) >> 24) )

void ReadBinary(string src_file)
{
    ifstream file_input(src_file, ios::in | ios::binary);

    char a[6];
    char b[4];

    file_input.read((char *) &a, 6);

    file_input.seekg(14);
    file_input.read((char *) &b, 4);

    cout << "start\n";
    cout << a << endl;
    cout << b << endl;
    cout << "end\n";

    SWAP_4(b);

    file_input.close();

    // string out_file = "C:\\Users\\xie\\Desktop\\result.txt";
    // ofstream file_output(out_file, ofstream::out);
    // file_output.write((char* ) &a, 2);
    // file_output.close();

}

int main()
{
    string src_file="C:\\Users\\xie\\Desktop\\NSS.HRPT.NP.D20197.S0346.E0358.B5893131.GC";
    // string src_file = "C:\\Users\\xie\\Desktop\\HS_H08_20200715_0000_B01_FLDK_R10_S0710.DAT";
    ReadBinary(src_file);

    return 0;
}


